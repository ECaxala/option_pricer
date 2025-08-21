#include "BlackScholesPricer.hpp"
#include <cmath>

double BlackScholesPricer::calculateCallPrice(const Option& option) const
{
    // Implement the Black-Scholes formula for call options
    return 0.0;
}

double BlackScholesPricer::calculatePutPrice(const Option& option) const
{
    // Implement the Black-Scholes formula for put options
    return 0.0;
}

std::string BlackScholesPricer::getName() const
{
    return "Black-Scholes Pricer\n - Exact Solutions of One-Factor Plain Options ";
}

std::pair<double, double> BlackScholesPricer::calculateD1D2(const Option& option) const
{
    // Calculate d1 and d2 for the Black-Scholes formula
    double tmp = option.Volatility() * std::sqrt(option.ExerciseDate());
    
    double d1 = (std::log(option.AssetPrice() / option.StrikePrice()) + 
                 (option.RiskFreeRate() + 0.5 * std::pow(option.Volatility(), 2)) * option.ExerciseDate()) / tmp;
    
    double d2 = d1 - tmp;
    
    return {d1, d2};
}

