#include "OptionContext.hpp"
#include <stdexcept>

OptionContext::OptionContext() : pricingStrategy_(nullptr), parityValidator_(nullptr)
{
}

OptionContext::OptionContext(std::unique_ptr<IPricingStrategy> strategy)
    : pricingStrategy_(std::move(strategy)), parityValidator_(nullptr)
{
}

OptionContext::~OptionContext()
{
    // No explicit cleanup needed, unique_ptr will handle it
}

void OptionContext::setPricingStrategy(std::unique_ptr<IPricingStrategy> strategy)
{
    if (!strategy)
    {
        throw std::invalid_argument("Cannot set a null pricing strategy.");
    }
    pricingStrategy_ = std::move(strategy);
}

void OptionContext::setParityValidator(std::unique_ptr<IParityValidator> validator)
{
    if (!validator)
    {
        throw std::invalid_argument("Cannot set a null parity validator.");
    }
    parityValidator_ = std::move(validator);
}

double OptionContext::calculateCallPrice(const Option& option) const
{
    validateStrategy();
    if (!option.isValid())
    {
        throw std::invalid_argument("Invalid option parameters.");
    }

    return pricingStrategy_->calculateCallPrice(option);
}

double OptionContext::calculatePutPrice(const Option& option) const
{
    validateStrategy();
    if (!option.isValid())
    {
        throw std::invalid_argument("Invalid option parameters.");
    }

    return pricingStrategy_->calculatePutPrice(option);
}

double OptionContext::calculateGamma(const Option& option) const
{
    validateStrategy();
    if (!option.isValid())
    {
        throw std::invalid_argument("Invalid option parameters.");
    }

    return pricingStrategy_->calculateGamma(option);
}

double OptionContext::calculateCallDelta(const Option& option) const
{
    validateStrategy();
    if (!option.isValid())
    {
        throw std::invalid_argument("Invalid option parameters.");
    }

    return pricingStrategy_->calculateCallDelta(option);
}

double OptionContext::calculatePutDelta(const Option& option) const
{
    validateStrategy();
    if (!option.isValid())
    {
        throw std::invalid_argument("Invalid option parameters.");
    }

    return pricingStrategy_->calculatePutDelta(option);
}

std::vector<double> OptionContext::calculateCallVector(const std::vector<Option>& options) const
{
    validateStrategy();
    return pricingStrategy_->calculateCallVector(options);
}

std::vector<double> OptionContext::calculatePutVector(const std::vector<Option>& options) const
{
    validateStrategy();
    return pricingStrategy_->calculatePutVector(options);
}

std::vector<std::vector<double>> OptionContext::calculateCallMatrix(
    const std::vector<std::vector<Option>>& optionMatrix) const
{
    validateStrategy();
    return pricingStrategy_->calculateCallMatrix(optionMatrix);
}

std::vector<std::vector<double>> OptionContext::calculatePutMatrix(
    const std::vector<std::vector<Option>>& optionMatrix) const
{
    validateStrategy();
    return pricingStrategy_->calculatePutMatrix(optionMatrix);
}

bool OptionContext::verifyParity(const Option& option, double tolerance) const
{
    validateStrategy();
    validateParityValidator();
    
    if (!option.isValid())
    {
        throw std::invalid_argument("Invalid option parameters.");
    }

    double callPrice = calculateCallPrice(option);
    double putPrice = calculatePutPrice(option);

    return parityValidator_->validateParity(option, callPrice, putPrice, tolerance);
}

double OptionContext::callFromPutParity(const Option& option, double putPrice) const
{
    validateParityValidator();
    
    if (!option.isValid())
    {
        throw std::invalid_argument("Invalid option parameters.");
    }

    return parityValidator_->callFromPut(option, putPrice);
}

double OptionContext::putFromCallParity(const Option& option, double callPrice) const
{
    validateParityValidator();
    
    if (!option.isValid())
    {
        throw std::invalid_argument("Invalid option parameters.");
    }

    return parityValidator_->putFromCall(option, callPrice);
}

std::string OptionContext::getCurrentStrategyName() const
{
    return pricingStrategy_ ? pricingStrategy_->getName() : "No Strategy set";
}

void OptionContext::validateStrategy() const
{
    if (!pricingStrategy_)
    {
        throw std::runtime_error("No pricing strategy set. Call setPricingStrategy() first.");
    }
}

void OptionContext::validateParityValidator() const
{
    if (!parityValidator_)
    {
        throw std::runtime_error("No parity validator set. Call setParityValidator() first.");
    }
}
