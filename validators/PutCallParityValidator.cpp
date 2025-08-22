#include "PutCallParityValidator.hpp"
#include <cmath>

bool PutCallParityValidator::validateParity(const Option& option, double callPrice, 
                                           double putPrice, double tolerance) const
{
    double parityDifference = std::abs(calculateParityDifference(option, callPrice, putPrice));
    return parityDifference <= tolerance;
}

double PutCallParityValidator::callFromPut(const Option& option, double putPrice) const
{
    // Put-Call Parity: C - P = S - K * e^(-r*T)
    // Therefore: C = P + S - K * e^(-r*T)
    double presentValueOfStrike = calculatePresentValueOfStrike(option);
    return putPrice + option.AssetPrice() - presentValueOfStrike;
}

double PutCallParityValidator::putFromCall(const Option& option, double callPrice) const
{
    // Put-Call Parity: C - P = S - K * e^(-r*T)
    // Therefore: P = C - S + K * e^(-r*T)
    double presentValueOfStrike = calculatePresentValueOfStrike(option);
    return callPrice - option.AssetPrice() + presentValueOfStrike;
}

double PutCallParityValidator::calculateParityDifference(const Option& option, 
                                                       double callPrice, double putPrice) const
{
    // Put-Call Parity: C - P = S - K * e^(-r*T)
    // Difference = (C - P) - (S - K * e^(-r*T))
    double leftSide = callPrice - putPrice;
    double rightSide = option.AssetPrice() - calculatePresentValueOfStrike(option);
    
    return leftSide - rightSide;
}

double PutCallParityValidator::calculatePresentValueOfStrike(const Option& option) const
{
    // Present value of strike: K * e^(-r*T)
    return option.StrikePrice() * std::exp(-option.RiskFreeRate() * option.ExerciseDate());
}
