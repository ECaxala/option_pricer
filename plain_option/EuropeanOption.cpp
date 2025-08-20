#include "EuropeanOption.hpp"
#include <sstream>

EuropeanOption::EuropeanOption(double T, double K, double sig, double r, double S)
    : T(T), K(K), sig(sig), r(r), S(S) 
{
}

EuropeanOption::~EuropeanOption()
{
}

EuropeanOption::EuropeanOption(const EuropeanOption& other)
    : T(other.T), K(other.K), sig(other.sig), r(other.r), S(other.S) 
{
}

EuropeanOption& EuropeanOption::operator = (const EuropeanOption& other)
{
    if (this != &other)
    {
        T = other.T;
        K = other.K;
        sig = other.sig;
        r = other.r;
        S = other.S;
    }
    return *this;
}

std::string EuropeanOption::ToString() const
{
    std::ostringstream optionStream;
    optionStream << "European Option: \n"
        << "  Maturity: " << T << "\n"
        << "  Strike: " << K << "\n"
        << "  Volatility: " << sig << "\n"
        << "  Risk-free rate: " << r << "\n"
        << "  Underlying price: " << S << "\n";
    return optionStream.str();
}
