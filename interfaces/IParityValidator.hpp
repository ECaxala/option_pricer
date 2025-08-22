#ifndef IPARITYVALIDATOR_HPP
#define IPARITYVALIDATOR_HPP

#include "../data/Option.hpp"

/**
 * @brief Interface for Put-Call Parity validation and calculations
 *
 * Implements the Put-Call Parity relationship for part b) of the homework.
 */
class IParityValidator
{
public:
    virtual ~IParityValidator() = default;
    
    // Put-Call Parity validation
    virtual bool validateParity(const Option& option, double callPrice,
                               double putPrice, double tolerance = 1e-6) const = 0;
    
    // Parity-based price calculation
    virtual double callFromPut(const Option& option, double putPrice) const = 0;
    virtual double putFromCall(const Option& option, double callPrice) const = 0;
    
    // Utility
    virtual double calculateParityDifference(const Option& option,
                                           double callPrice, double putPrice) const = 0;
};

#endif // IPARITYVALIDATOR_HPP