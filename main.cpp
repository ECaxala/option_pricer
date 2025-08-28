// STL
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
// Boost
#include <boost/random.hpp>
#include <boost/math/distributions/normal.hpp>

#include "OptionContext.hpp"
#include "BlackScholesPricer.hpp"
#include "PutCallParityValidator.hpp"
#include "Option.hpp"
#include "utils/MeshUtils.hpp"
#include "utils/MatrixPrintUtils.hpp"

// Simple struct to hold test batch data
struct TestBatch
{
    std::string name;
    Option option;
    double expectedCallPrice;
    double expectedPutPrice;
};
    

int main(void)
{    
    // Create test batches
    TestBatch Batch_1 = {"BATCH 1", Option(0.25, 65.0, 0.30, 0.08, 60.0), 2.13337, 5.84628};
    TestBatch Batch_2 = {"BATCH 2", Option(1.0, 100.0, 0.2, 0.0, 100.0), 7.96557, 7.96557};
    TestBatch Batch_3 = {"BATCH 3", Option(1.0, 10.0, 0.50, 0.12, 5.0), 0.204058, 4.07326};
    TestBatch Batch_4 = {"BATCH 4", Option(30.0, 100.0, 0.30, 0.08, 100.0), 92.17570, 1.24750};

    // Create a vector of test batches
    std::vector<TestBatch> batches = {Batch_1, Batch_2, Batch_3, Batch_4};

    // Setup black scholes strategy
    auto blackScholesStrategy = std::make_unique<BlackScholesPricer>();

    // Init context with strategy
    OptionContext context(std::move(blackScholesStrategy));

    // Test Section A, a): Calculate exact plain option price 
    for (const auto& batch : batches)
    {
        std::cout << "=== " << batch.name << " ===" << std::endl;
        std::cout << "Parameters: " << batch.option.toString() << std::endl;

        // Calculate prices
        double callPrice = context.calculateCallPrice(batch.option);
        double putPrice = context.calculatePutPrice(batch.option);

        std::cout << "Call Price: " << callPrice << " (Expected: " << batch.expectedCallPrice << ")" << std::endl;
        std::cout << "Put Price: " << putPrice << " (Expected: " << batch.expectedPutPrice << ")" << std::endl;
        std::cout << std::endl;

        // Assert using precision 1e-5 since only five decimal places are provided
        assert(std::abs(callPrice - batch.expectedCallPrice) < 1e-5);
        assert(std::abs(putPrice - batch.expectedPutPrice) < 1e-5);
    }

    std::cout << "\n=== PUT-CALL PARITY TESTING (part b) ===" << std::endl;
    
    // Setup parity validator
    auto parityValidator = std::make_unique<PutCallParityValidator>();
    
    // Set the parity validator in the existing context
    context.setParityValidator(std::move(parityValidator));
    
    // Test Put-Call Parity for each batch
    for (const auto& batch : batches)
    {
        std::cout << "\n--- " << batch.name << " Parity Test ---" << std::endl;
        
        // Calculate direct prices
        double directCall = context.calculateCallPrice(batch.option);
        double directPut = context.calculatePutPrice(batch.option);
        
        // Test parity validation
        bool parityValid = context.verifyParity(batch.option, 1e-6);
        
        // Test parity-based calculations
        double parityCall = context.callFromPutParity(batch.option, directPut);
        double parityPut = context.putFromCallParity(batch.option, directCall);
        
        std::cout << "Direct Call: " << directCall << ", Parity Call: " << parityCall << std::endl;
        std::cout << "Direct Put: " << directPut << ", Parity Put: " << parityPut << std::endl;
        std::cout << "Parity Valid: " << (parityValid ? "YES" : "NO") << std::endl;
        
        // Assert parity relationships hold
        assert(parityValid);
        assert(std::abs(directCall - parityCall) < 1e-6);
        assert(std::abs(directPut - parityPut) < 1e-6);
    }
    
    std::cout << "\n=== VECTOR PRICING TEST (part c) ===" << std::endl;
    
    // Test global meshArray function and vector pricing
    auto spotPrices = meshArray(60.0, 80.0, 1.0);  // 10, 11, 12, ..., 50
    
    // Create vector of options with varying spot prices
    std::vector<Option> optionVector;
    for (double S : spotPrices) {
        Option option = Batch_1.option;
        option.AssetPrice(S);
        optionVector.push_back(option);
    }
    
    // Vector pricing
    auto callPrices = context.calculateCallVector(optionVector);
    auto putPrices = context.calculatePutVector(optionVector);
    
    std::cout << "Generated " << spotPrices.size() << " spot prices" << std::endl;
    std::cout << "First few results:" << std::endl;
    for (size_t i = 0; i < 20; ++i) {
        std::cout << "S=" << spotPrices[i] << ", Call=" << callPrices[i]
                  << ", Put=" << putPrices[i] << std::endl;
    }
    
    std::cout << "\n=== MATRIX PRICING TEST (part d) ===" << std::endl;
    
    // i) Matrix pricing as function of Expiry Time
    std::cout << "\ni) Expiry Time Matrix:" << std::endl;
    auto expiryTimes = meshArray(0.1, 1.0, 0.2);  // 0.1, 0.3, 0.5, 0.7, 0.9
    auto spotPricesMatrix = meshArray(50.0, 70.0, 5.0);  // 50, 55, 60, 65, 70
    
    std::vector<std::vector<Option>> expiryMatrix;
    for (double T : expiryTimes) {
        std::vector<Option> row;
        for (double S : spotPricesMatrix) {
            Option option = Batch_1.option;
            option.ExerciseDate(T);
            option.AssetPrice(S);
            row.push_back(option);
        }
        expiryMatrix.push_back(row);
    }
    
    auto expiryCallMatrix = context.calculateCallMatrix(expiryMatrix);
    printMatrix(expiryTimes, spotPricesMatrix, expiryCallMatrix, "T\\S");
    
    // ii) Matrix pricing as function of Volatility
    std::cout << "\nii) Volatility Matrix:" << std::endl;
    auto volatilities = meshArray(0.1, 0.5, 0.1);  // 0.1, 0.2, 0.3, 0.4, 0.5
    
    std::vector<std::vector<Option>> volMatrix;
    for (double vol : volatilities) {
        std::vector<Option> row;
        for (double S : spotPricesMatrix) {
            Option option = Batch_1.option;
            option.Volatility(vol);
            option.AssetPrice(S);
            row.push_back(option);
        }
        volMatrix.push_back(row);
    }
    
    auto volCallMatrix = context.calculateCallMatrix(volMatrix);
    printMatrix(volatilities, spotPricesMatrix, volCallMatrix, "Vol\\S");
    
    // iii) Matrix pricing with any parameter combination (Strike vs Spot)
    std::cout << "\niii) Strike-Spot Matrix:" << std::endl;
    auto strikes = meshArray(60.0, 80.0, 5.0);  // 60, 65, 70, 75, 80
    
    std::vector<std::vector<Option>> strikeMatrix;
    for (double K : strikes) {
        std::vector<Option> row;
        for (double S : spotPricesMatrix) {
            Option option = Batch_1.option;
            option.StrikePrice(K);
            option.AssetPrice(S);
            row.push_back(option);
        }
        strikeMatrix.push_back(row);
    }
    
    auto strikeCallMatrix = context.calculateCallMatrix(strikeMatrix);
    printMatrix(strikes, spotPricesMatrix, strikeCallMatrix, "K\\S");

    // Test Section: Gamma calculation with provided test batch
    std::cout << "\n=== GAMMA CALCULATION TEST ===" << std::endl;
    
    // Test data from the problem: K = 100, S = 105, T = 0.5, r = 0.1, b = 0, sig = 0.36
    // Expected delta call = 0.5946, delta put = -0.3566
    Option gammaTestOption(0.5, 100.0, 0.36, 0.1, 105.0, 0.0); // b = 0 for future options
    
    std::cout << "--- Gamma Test Parameters ---" << std::endl;
    std::cout << "Parameters: " << gammaTestOption.toString() << std::endl;
    
    // Calculate gamma (same for both calls and puts)
    double gamma = context.calculateGamma(gammaTestOption);
    
    std::cout << "Calculated Gamma: " << gamma << std::endl;
    
    // Calculate deltas
    double callDelta = context.calculateCallDelta(gammaTestOption);
    double putDelta = context.calculatePutDelta(gammaTestOption);
    
    std::cout << "Calculated Call Delta: " << callDelta << " (Expected: 0.5946)" << std::endl;
    std::cout << "Calculated Put Delta: " << putDelta << " (Expected: -0.3566)" << std::endl;
    
    // Validation
    double callDeltaError = std::abs(callDelta - 0.5946);
    double putDeltaError = std::abs(putDelta - (-0.3566));
    
    std::cout << "Call Delta Error: " << callDeltaError << std::endl;
    std::cout << "Put Delta Error: " << putDeltaError << std::endl;
    
    if (callDeltaError < 0.001 && putDeltaError < 0.001)
    {
        std::cout << "Delta Validation: PASSED" << std::endl;
    }
    else
    {
        std::cout << "Delta Validation: FAILED" << std::endl;
    }
    
    std::cout << "Greeks Test Complete" << std::endl;
    
    std::cout << "\n=== DELTA VECTOR CALCULATION TEST (part b) ===" << std::endl;
    
    // Generate monotonic range of underlying values as requested: 10, 11, 12, ..., 50
    auto underlyingValues = meshArray(10.0, 50.0, 1.0);
    
    // Create vector of options with varying underlying asset prices
    std::vector<Option> deltaTestOptions;
    for (double S : underlyingValues)
    {
        Option option = gammaTestOption;  // Use same base parameters as gamma test
        option.AssetPrice(S);
        deltaTestOptions.push_back(option);
    }
    
    // Calculate call delta vector for monotonic range
    auto callDeltaVector = context.calculateCallDeltaVector(deltaTestOptions);
    auto putDeltaVector = context.calculatePutDeltaVector(deltaTestOptions);
    
    std::cout << "Generated " << underlyingValues.size() << " underlying values from 10 to 50" << std::endl;
    std::cout << "First few call delta results:" << std::endl;
    for (size_t i = 0; i < 10; ++i)
    {
        std::cout << "S=" << underlyingValues[i] << ", Call Delta=" << callDeltaVector[i]
                  << ", Put Delta=" << putDeltaVector[i] << std::endl;
    }
    
    std::cout << "\nLast few call delta results:" << std::endl;
    for (size_t i = 0; i < underlyingValues.size(); ++i)
    {
        std::cout << "S=" << underlyingValues[i] << ", Call Delta=" << callDeltaVector[i]
                  << ", Put Delta=" << putDeltaVector[i] << std::endl;
    }
    
    std::cout << "Vector Delta Test Complete" << std::endl;
    
    std::cout << "\n=== ALL TESTS PASSED ===" << std::endl;
}
