#ifndef BLACKSCHOLESPRICER_HPP
#define BLACKSCHOLESPRICER_HPP

#include <utility>
#include <boost/math/distributions/normal.hpp>
#include "IPricingStrategy.hpp"
#include "Option.hpp"

class BlackScholesPricer : public IPricingStrategy
{
public:

    double calculateCallPrice(const Option& option) const override;
    double calculatePutPrice(const Option& option) const override;

    std::string getName() const override;

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