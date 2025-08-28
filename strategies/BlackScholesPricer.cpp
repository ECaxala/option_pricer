#include "BlackScholesPricer.hpp"
#include <cmath>
#include <boost/math/distributions/normal.hpp>

double BlackScholesPricer::calculateCallPrice(const Option& option) const
{
    // receive d1 and d2 use structure binding syntax
    auto [d1, d2] = calculateD1D2(option);
    
    // Black-Scholes call formula: C = S*N(d1) - K*e^(-r*T)*N(d2)
    // For stock options without dividends, no dividend adjustment needed
    return (option.AssetPrice() * N(d1)) -
           (option.StrikePrice() * std::exp(-option.RiskFreeRate() * option.ExerciseDate()) * N(d2));
}

double BlackScholesPricer::calculatePutPrice(const Option& option) const
{
    // receive d1 and d2 use structure binding syntax
    auto [d1, d2] = calculateD1D2(option);
    
    // Black-Scholes put formula: P = K*e^(-r*T)*N(-d2) - S*e^(-q*T)*N(-d1)
    // For stock options without dividends, q = 0, so e^(-q*T) = 1
    return (option.StrikePrice() * std::exp(-option.RiskFreeRate() * option.ExerciseDate()) * N(-d2)) -
           (option.AssetPrice() * N(-d1));
}

std::string BlackScholesPricer::getName() const
{
    return "Black-Scholes Pricer\n - Exact Solutions of One-Factor Plain Options ";
}

std::vector<double> BlackScholesPricer::calculateCallVector(const std::vector<Option>& options) const
{
    std::vector<double> callPrices;
    callPrices.reserve(options.size());
    
    for (const auto& option : options) {
        callPrices.push_back(calculateCallPrice(option));
    }
    
    return callPrices;
}

std::vector<double> BlackScholesPricer::calculatePutVector(const std::vector<Option>& options) const
{
    std::vector<double> putPrices;
    putPrices.reserve(options.size());
    
    for (const auto& option : options) {
        putPrices.push_back(calculatePutPrice(option));
    }
    
    return putPrices;
}

std::vector<std::vector<double>> BlackScholesPricer::calculateCallMatrix(
    const std::vector<std::vector<Option>>& optionMatrix) const
{
    std::vector<std::vector<double>> callMatrix;
    callMatrix.reserve(optionMatrix.size());
    
    for (const auto& optionRow : optionMatrix) {
        callMatrix.push_back(calculateCallVector(optionRow));
    }
    
    return callMatrix;
}

std::vector<std::vector<double>> BlackScholesPricer::calculatePutMatrix(
    const std::vector<std::vector<Option>>& optionMatrix) const
{
    std::vector<std::vector<double>> putMatrix;
    putMatrix.reserve(optionMatrix.size());
    
    for (const auto& optionRow : optionMatrix) {
        putMatrix.push_back(calculatePutVector(optionRow));
    }
    
    return putMatrix;
}

bool BlackScholesPricer::supportsGreeks() const
{
    return true;
}

double BlackScholesPricer::calculateGamma(const Option& option) const
{
    // Gamma formula: Γ = n(d1) / (S * σ * √T)
    // Gamma is the same for both calls and puts
    auto [d1, d2] = calculateD1D2(option);
    
    double denominator = option.AssetPrice() * option.Volatility() * std::sqrt(option.ExerciseDate());
    
    return n(d1) / denominator;
}

double BlackScholesPricer::calculateCallDelta(const Option& option) const
{
    // Call Delta: Δ_call = e^((b-r)*T) * N(d1)
    auto [d1, d2] = calculateD1D2(option);
    
    double b = option.CostOfCarry();
    return std::exp((b - option.RiskFreeRate()) * option.ExerciseDate()) * N(d1);
}

double BlackScholesPricer::calculatePutDelta(const Option& option) const
{
    // Put Delta: Δ_put = e^((b-r)*T) * (N(d1) - 1)
    auto [d1, d2] = calculateD1D2(option);
    
    double b = option.CostOfCarry();
    return std::exp((b - option.RiskFreeRate()) * option.ExerciseDate()) * (N(d1) - 1.0);
}

std::pair<double, double> BlackScholesPricer::calculateD1D2(const Option& option) const
{
    // Calculate d1 and d2 for the Black-Scholes formula
    // Use cost-of-carry parameter from Option
    double tmp = option.Volatility() * std::sqrt(option.ExerciseDate());
    
    double b = option.CostOfCarry(); // Use cost-of-carry parameter from Option
    double d1 = (std::log(option.AssetPrice() / option.StrikePrice()) + 
                 (b + 0.5 * std::pow(option.Volatility(), 2)) * option.ExerciseDate()) / tmp;
    
    double d2 = d1 - tmp;
    
    return {d1, d2};
}

double BlackScholesPricer::N(double x) const
{
    // Use Boost's normal distribution to calculate the cumulative distribution function
    return boost::math::cdf(NormDist_, x);
}

double BlackScholesPricer::n(double x) const
{
    // Use Boost's normal distribution to calculate the probability density function
    return boost::math::pdf(NormDist_, x);
}
