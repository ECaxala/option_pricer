// STL
#include <iostream>
#include <vector>
#include <cassert>
// Boost
#include <boost/random.hpp>
#include <boost/math/distributions/normal.hpp>

#include "OptionContext.hpp"
#include "BlackScholesPricer.hpp"
#include "Option.hpp"

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

}
