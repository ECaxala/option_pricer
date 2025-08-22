#include "OptionContext.hpp"

OptionContext::OptionContext() : pricingStrategy_(nullptr)
{
}

OptionContext::OptionContext(std::unique_ptr<IPricingStrategy> strategy) : pricingStrategy_(std::move(strategy))
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
