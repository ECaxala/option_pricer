// STL
#include <iostream>
#include <vector>
// Boost
#include <boost/random.hpp>

#include "plain_option/EuropeanOption.hpp"

int main(void)
{
    // Create a EuropeanOption instance
    EuropeanOption option(1.0, 100.0, 0.2, 0.05, 100.0);

    // Print the option details
    std::cout << option.ToString() << std::endl;

    return 0;
}