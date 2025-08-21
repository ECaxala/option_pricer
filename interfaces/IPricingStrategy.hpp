#ifndef IPRICINGSTRATEGY_HPP
#define IPRICINGSTRATEGY_HPP

#include <string>
#include "Option.hpp"

/**
 * @brief Common interface class for option pricing strategies:
 * - Black-Scholes (exact solution)
 * - ...tbd
 */
class IPricingStrategy
{
public: 
    virtual ~IPricingStrategy() = default;

    virtual double calculateCallPrice(const Option& option) const = 0;
    virtual double calculatePutPrice(const Option& option) const = 0;

    // Utility function
    virtual std::string getName() const = 0;
};

#endif // IPRICINGSTRATEGY_HPP