#ifndef PUTCALLPARITYVALIDATOR_HPP
#define PUTCALLPARITYVALIDATOR_HPP

#include "../interfaces/IParityValidator.hpp"
#include <cmath>

/**
 * @brief Concrete implementation of Put-Call Parity validator
 * 
 * Implements the Put-Call Parity relationship: C - P = S - K * e^(-r*T)
 */
class PutCallParityValidator : public IParityValidator
{
public:
    // IParityValidator implementation
    bool validateParity(const Option& option, double callPrice, 
                       double putPrice, double tolerance = 1e-6) const override;
    
    double callFromPut(const Option& option, double putPrice) const override;
    double putFromCall(const Option& option, double callPrice) const override;
    
    double calculateParityDifference(const Option& option, 
                                   double callPrice, double putPrice) const override;

private:
    // Helper function to calculate present value of strike price
    double calculatePresentValueOfStrike(const Option& option) const;
};

#endif // PUTCALLPARITYVALIDATOR_HPP