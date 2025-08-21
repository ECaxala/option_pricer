#ifndef OPTION_HPP
#define OPTION_HPP

#include <string>

/*
    @brief Option data model
    Encapsulates parameters for option pricing
*/
class Option
{
public:
    Option() = delete; // Delete default Constructor
    Option(double T, double K, double sig, double r, double S); // Parameterized Constructor
    Option(const Option& other); // Copy Constructor
    ~Option(); // Destructor

    // Operators
    Option& operator = (const Option& other); // Copy Assignment Operator
    bool operator == (const Option& other) const; // Equality Operator
    bool operator != (const Option& other) const; // Inequality Operator

    // Utility function
    std::string toString() const;

private:
    double T;     // Time to maturity
    double K;     // Strike price
    double sig;   // Volatility
    double r;     // Risk-free interest rate
    double S;     // Underlying asset price
};
#endif // OPTION_HPP