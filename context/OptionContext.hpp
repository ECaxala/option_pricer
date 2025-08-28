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
#include "IParityValidator.hpp"
#include "Option.hpp"
#include <memory>

class OptionContext
{
public:

    OptionContext();
    OptionContext(std::unique_ptr<IPricingStrategy> strategy);
    ~OptionContext();

    // Strategy management
    void setPricingStrategy(std::unique_ptr<IPricingStrategy> strategy);
    void setParityValidator(std::unique_ptr<IParityValidator> validator);

    // Single option pricing
    double calculateCallPrice(const Option& option) const;
    double calculatePutPrice(const Option& option) const;

    // Greeks calculation
    double calculateGamma(const Option& option) const;
    double calculateCallDelta(const Option& option) const;
    double calculatePutDelta(const Option& option) const;

    // Vector Greeks calculation for monotonic ranges
    std::vector<double> calculateCallDeltaVector(const std::vector<Option>& options) const;
    std::vector<double> calculatePutDeltaVector(const std::vector<Option>& options) const;
    std::vector<double> calculateGammaVector(const std::vector<Option>& options) const;

    // Matrix Greeks calculation for parameter variations
    std::vector<std::vector<double>> calculateCallDeltaMatrix(
        const std::vector<std::vector<Option>>& optionMatrix) const;
    std::vector<std::vector<double>> calculatePutDeltaMatrix(
        const std::vector<std::vector<Option>>& optionMatrix) const;
    std::vector<std::vector<double>> calculateGammaMatrix(
        const std::vector<std::vector<Option>>& optionMatrix) const;

    // Vector pricing for monotonic ranges
    std::vector<double> calculateCallVector(const std::vector<Option>& options) const;
    std::vector<double> calculatePutVector(const std::vector<Option>& options) const;

    // Matrix pricing for parameter variations
    std::vector<std::vector<double>> calculateCallMatrix(
        const std::vector<std::vector<Option>>& optionMatrix) const;
    std::vector<std::vector<double>> calculatePutMatrix(
        const std::vector<std::vector<Option>>& optionMatrix) const;

    // Put-Call Parity
    bool verifyParity(const Option& option, double tolerance = 1e-6) const;
    double callFromPutParity(const Option& option, double putPrice) const;
    double putFromCallParity(const Option& option, double callPrice) const;

    // Utility functions
    std::string getCurrentStrategyName() const;

private:

    std::unique_ptr<IPricingStrategy> pricingStrategy_; // Strategy for pricing options
    std::unique_ptr<IParityValidator> parityValidator_; // Validator for put-call parity

    // Validation functions
    void validateStrategy() const;
    void validateParityValidator() const;
};

#endif // OPTIONCONTEXT_HPP