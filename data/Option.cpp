#include "Option.hpp" 

Option::Option(double T, double K, double sig, double r, double S)
    : T_(T), K_(K), sig_(sig), r_(r), S_(S)
{
}

Option::Option(const Option& other)
    : T_(other.T_), K_(other.K_), sig_(other.sig_), r_(other.r_), S_(other.S_)
{
}

Option::~Option()
{
}

Option& Option::operator = (const Option& other)
{
    if (this != &other)
    {
        T_ = other.T_;
        K_ = other.K_;
        sig_ = other.sig_;
        r_ = other.r_;
        S_ = other.S_;
    }
    return *this;
}

bool Option::operator == (const Option& other) const
{
    return (T_ == other.T_ && K_ == other.K_ && sig_ == other.sig_ && r_ == other.r_ && S_ == other.S_);
}

bool Option::operator != (const Option& other) const
{
    return !(*this == other);
}

std::string Option::toString() const
{
    std::string out;
    out += "Expiry time (T): " + std::to_string(T_) + "\n";
    out += "Strike price (K): " + std::to_string(K_) + "\n";
    out += "Volatility (sig): " + std::to_string(sig_) + "\n";
    out += "Interest rate (r): " + std::to_string(r_) + "\n";
    out += "Underlying price (S): " + std::to_string(S_) + "\n";
    return out;
}

bool Option::isValid() const
{
    // Financial constrains: All parameters expect r must be positive
    return (T_ > 0 && K_ > 0 && sig_ > 0 && S_ > 0);
}
