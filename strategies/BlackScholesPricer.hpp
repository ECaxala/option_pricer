#ifndef BLACKSCHOLESPRICER_HPP
#define BLACKSCHOLESPRICER_HPP

#include <utility>
// #include <Boost/math/distributions/normal.hpp>
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
};


#endif // BLACKSCHOLESPRICER_HPP