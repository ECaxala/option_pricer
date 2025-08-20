#ifndef EUROPEAN_OPTION_HPP
#define EUROPEAN_OPTION_HPP

#include <string>

class EuropeanOption
{
public:

    explicit EuropeanOption(double T, double K, double sig, double r, double S); // Constructor
    EuropeanOption() = delete;                                          // Delete default constructor
    EuropeanOption(const EuropeanOption& other);                        // Copy Constructor
    ~EuropeanOption();                                                  // Destructor
    EuropeanOption& operator = (const EuropeanOption& other);           // Assignment Operator

    std::string ToString() const;                                       // String representation of the option 

private:

    double T;     // Time to maturity
    double K;     // Strike price
    double sig;   // Volatility
    double r;     // Risk-free interest rate
    double S;     // Underlying asset price
};

#endif // EUROPEAN_OPTION_HPP