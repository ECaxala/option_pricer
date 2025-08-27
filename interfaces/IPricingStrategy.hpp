#ifndef IPRICINGSTRATEGY_HPP
#define IPRICINGSTRATEGY_HPP

#include <string>
#include <vector>
#include "Option.hpp"

/**
 * @brief Interface for option pricing strategies
 */
class IPricingStrategy
{
public:
    virtual ~IPricingStrategy() = default;

    // Single option pricing
    virtual double calculateCallPrice(const Option& option) const = 0;
    virtual double calculatePutPrice(const Option& option) const = 0;

    // Vector pricing for monotonic ranges
    virtual std::vector<double> calculateCallVector(const std::vector<Option>& options) const = 0;
    virtual std::vector<double> calculatePutVector(const std::vector<Option>& options) const = 0;

    // Matrix pricing for parameter variations
    virtual std::vector<std::vector<double>> calculateCallMatrix(
        const std::vector<std::vector<Option>>& optionMatrix) const = 0;
    virtual std::vector<std::vector<double>> calculatePutMatrix(
        const std::vector<std::vector<Option>>& optionMatrix) const = 0;

    // Utility functions
    virtual std::string getName() const = 0;
    virtual bool supportsGreeks() const = 0;
};

#endif // IPRICINGSTRATEGY_HPP