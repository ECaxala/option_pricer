/**
 * @brief Context class that manages option pricing strategies using the Strategy pattern.
 * 
 * This class serves as a context in the Strategy design pattern, allowing clients to
 * use different option pricing algorithms (strategies) interchangeably without being
 * tightly coupled to specific implementations. The main advantage of this approach is
 * that it provides flexibility to switch between different pricing models (e.g., 
 * Black-Scholes, Binomial, Monte Carlo) at runtime while maintaining a consistent
 * interface for option pricing operations.
 * 
 * The Strategy pattern benefit here includes:
 * - Elimination of conditional statements for strategy selection
 * - Easy addition of new pricing strategies without modifying existing code
 * - Runtime strategy switching capability
 * - Improved testability and maintainability
 */
#ifndef OPTIONCONTEXT_HPP
#define OPTIONCONTEXT_HPP

#include "IPricingStrategy.hpp"
#include "Option.hpp"



class OptionContext
{
public:

    OptionContext();
    OptionContext(std::unique_ptr<IPricingStrategy> strategy);
    ~OptionContext();

    // Strategy management
    void setPricingStrategy(std::unique_ptr<IPricingStrategy> strategy);    

    // Single option pricing
    double calculateCallPrice(const Option& option) const;
    double calculatePutPrice(const Option& option) const;

    // Utility functions
    std::string getCurrentStrategyName() const;

private:

    std::unique_ptr<IPricingStrategy> pricingStrategy_; // Strategy for pricing options

    // Validation function to ensure the strategy is set
    void validateStrategy() const;
};

#endif // OPTIONCONTEXT_HPP