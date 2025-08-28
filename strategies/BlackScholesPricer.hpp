#ifndef BLACKSCHOLESPRICER_HPP
#define BLACKSCHOLESPRICER_HPP

#include <utility>
#include <boost/math/distributions/normal.hpp>
#include "IPricingStrategy.hpp"
#include "Option.hpp"

class BlackScholesPricer : public IPricingStrategy
{
public:

    // Single option pricing
    double calculateCallPrice(const Option& option) const override;
    double calculatePutPrice(const Option& option) const override;

    // Vector pricing
    std::vector<double> calculateCallVector(const std::vector<Option>& options) const override;
    std::vector<double> calculatePutVector(const std::vector<Option>& options) const override;

    // Matrix pricing
    std::vector<std::vector<double>> calculateCallMatrix(
        const std::vector<std::vector<Option>>& optionMatrix) const override;
    std::vector<std::vector<double>> calculatePutMatrix(
        const std::vector<std::vector<Option>>& optionMatrix) const override;

    // Greeks calculation
    double calculateGamma(const Option& option) const override;
    double calculateCallDelta(const Option& option) const override;
    double calculatePutDelta(const Option& option) const override;

    // Vector Greeks calculation for monotonic ranges
    std::vector<double> calculateCallDeltaVector(const std::vector<Option>& options) const override;
    std::vector<double> calculatePutDeltaVector(const std::vector<Option>& options) const override;
    std::vector<double> calculateGammaVector(const std::vector<Option>& options) const override;

    // Utility functions
    std::string getName() const override;
    bool supportsGreeks() const override;

private:
    // Helper functions for Black-Scholes calculations
    std::pair<double, double> calculateD1D2(const Option& option) const;

    // Gaussian standard normal cumulative distribution function (CDF)
    double N(double x) const;
    // Gaussian standard normal probability density function (PDF)
    double n(double x) const;

    // Standard normal distribution by Boost
    inline static const boost::math::normal_distribution<double> NormDist_{0.0, 1.0};

};


#endif // BLACKSCHOLESPRICER_HPP