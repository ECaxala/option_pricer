#include "Option.hpp" 

Option::Option(double T, double K, double sig, double r, double S)
    : T(T), K(K), sig(sig), r(r), S(S)
{
}

Option::Option(const Option& other)
    : T(other.T), K(other.K), sig(other.sig), r(other.r), S(other.S)
{
}

Option::~Option()
{
}

Option& Option::operator = (const Option& other)
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

bool Option::operator == (const Option& other) const
{
    return (T == other.T && K == other.K && sig == other.sig && r == other.r && S == other.S);
}

bool Option::operator != (const Option& other) const
{
    return !(*this == other);
}

std::string Option::toString() const
{
    std::string out;
    out += "Expiry time (T): " + std::to_string(T) + "\n";
    out += "Strike price (K): " + std::to_string(K) + "\n";
    out += "Volatility (sig): " + std::to_string(sig) + "\n";
    out += "Interest rate (r): " + std::to_string(r) + "\n";
    out += "Underlying price (S): " + std::to_string(S) + "\n";
    return out;
}
