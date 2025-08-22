// STL
#include <iostream>
#include <vector>
#include <cassert>
// Boost
#include <boost/random.hpp>
#include <boost/math/distributions/normal.hpp>

#include "OptionContext.hpp"
#include "BlackScholesPricer.hpp"
#include "PutCallParityValidator.hpp"
#include "Option.hpp"

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

    std::cout << "\n=== PUT-CALL PARITY TESTING (Teil b) ===" << std::endl;
    
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
    
    std::cout << "\n=== ALL TESTS PASSED ===" << std::endl;
}
