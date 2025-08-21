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

    // Getters
    double ExerciseDate() const { return T_; };
    double StrikePrice() const { return K_; };
    double Volatility() const { return sig_; };
    double RiskFreeRate() const { return r_; };
    double AssetPrice() const { return S_; };

    // Setters
    void ExerciseDate(double T) { T_ = T; };
    void StrikePrice(double K) { K_ = K; };
    void Volatility(double sig) { sig_ = sig; };
    void RiskFreeRate(double r) { r_ = r; };
    void AssetPrice(double S) { S_ = S; };

    // Utility function
    std::string toString() const;

private:

    double T_;     // Exercise date
    double K_;     // Strike price
    double sig_;   // Constant Volatility
    double r_;     // Risk-free interest rate
    double S_;     // Underlying asset price
};
#endif // OPTION_HPP