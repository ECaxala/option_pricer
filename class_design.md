# Header File Design für Black-Scholes Option Pricing

## Dateistruktur

```
src/level_9/
├── plain_option/
│   ├── EuropeanOption.hpp
│   ├── EuropeanOption.cpp
│   ├── BlackScholesPricer.hpp
│   └── BlackScholesPricer.cpp
├── main.cpp
└── CMakeLists.txt
```

## 1. EuropeanOption.hpp (Erweitert)

```cpp
#ifndef EUROPEAN_OPTION_HPP
#define EUROPEAN_OPTION_HPP

#include <string>

/**
 * @brief European Option data model class
 * 
 * This class represents a European option with all necessary parameters
 * for Black-Scholes pricing. It serves as a data container and does not
 * perform pricing calculations itself.
 */
class EuropeanOption
{
public:
    // Constructors
    EuropeanOption();  // Default constructor
    EuropeanOption(double T, double K, double sig, double r, double S);
    EuropeanOption(const EuropeanOption& other);  // Copy constructor
    
    // Assignment operator
    EuropeanOption& operator=(const EuropeanOption& other);
    
    // Destructor
    ~EuropeanOption();

    // Getter methods for parameters
    double getTimeToMaturity() const { return T; }
    double getStrike() const { return K; }
    double getVolatility() const { return sig; }
    double getRiskFreeRate() const { return r; }
    double getSpotPrice() const { return S; }
    
    // Setter methods for parameter updates (useful for matrix pricing)
    void setTimeToMaturity(double newT);
    void setStrike(double newK);
    void setVolatility(double newSig);
    void setRiskFreeRate(double newR);
    void setSpotPrice(double newS);
    
    // Utility methods
    void updateAllParameters(double T, double K, double sig, double r, double S);
    std::string toString() const;  // For debugging/output
    
    // Validation
    bool isValid() const;  // Check if parameters are valid

private:
    double T;     // Time to maturity
    double K;     // Strike price
    double sig;   // Volatility
    double r;     // Risk-free interest rate
    double S;     // Underlying asset price
    
    // Helper method for validation
    void validateParameters() const;
};

#endif // EUROPEAN_OPTION_HPP
```

## 2. BlackScholesPricer.hpp (Neue Utility-Klasse)

```cpp
#ifndef BLACK_SCHOLES_PRICER_HPP
#define BLACK_SCHOLES_PRICER_HPP

#include "EuropeanOption.hpp"
#include <vector>

/**
 * @brief Black-Scholes pricing utility class
 * 
 * This class provides static methods for calculating European option prices
 * using the Black-Scholes formula. It separates pricing logic from data model.
 */
class BlackScholesPricer
{
public:
    // Main pricing methods
    static double calculateCallPrice(const EuropeanOption& option);
    static double calculatePutPrice(const EuropeanOption& option);
    
    // Put-Call Parity methods (for part b of homework)
    static double callFromPutParity(const EuropeanOption& option, double putPrice);
    static double putFromCallParity(const EuropeanOption& option, double callPrice);
    static bool verifyPutCallParity(const EuropeanOption& option, 
                                   double callPrice, double putPrice, 
                                   double tolerance = 1e-6);
    
    // Vector pricing methods (for part c of homework)
    static std::vector<double> calculateCallPrices(const std::vector<EuropeanOption>& options);
    static std::vector<double> calculatePutPrices(const std::vector<EuropeanOption>& options);
    
    // Matrix pricing methods (for part d of homework)
    static std::vector<std::vector<double>> calculateCallPriceMatrix(
        const std::vector<std::vector<EuropeanOption>>& optionMatrix);
    static std::vector<std::vector<double>> calculatePutPriceMatrix(
        const std::vector<std::vector<EuropeanOption>>& optionMatrix);

private:
    // Helper methods for Black-Scholes calculations
    static double calculateD1(const EuropeanOption& option);
    static double calculateD2(const EuropeanOption& option);
    
    // Statistical functions (using Boost)
    static double normalCDF(double x);      // Cumulative normal distribution N(x)
    static double normalPDF(double x);      // Probability density function n(x)
    
    // Utility methods
    static void validateOption(const EuropeanOption& option);
    
    // Constants
    static const double PI;
    static const double SQRT_2_PI;
};

#endif // BLACK_SCHOLES_PRICER_HPP
```

## 3. CMakeLists.txt (Erweitert)

```cmake
# Set CMake policy to use modern Boost targets
cmake_policy(SET CMP0167 NEW)

# Find Boost using modern approach - add math component
find_package(Boost REQUIRED COMPONENTS system filesystem random math)

# Add all source files
add_executable(comp_finance_app
    main.cpp
    plain_option/EuropeanOption.cpp
    plain_option/BlackScholesPricer.cpp
)

target_include_directories(comp_finance_app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/plain_option
)

# Use modern Boost targets
target_link_libraries(comp_finance_app
    Boost::system
    Boost::filesystem
    Boost::random
    Boost::math
)

# Set C++ standard
set_property(TARGET comp_finance_app PROPERTY CXX_STANDARD 17)
set_property(TARGET comp_finance_app PROPERTY CXX_STANDARD_REQUIRED ON)
```

## 4. Verwendungsbeispiel in main.cpp

```cpp
#include "plain_option/EuropeanOption.hpp"
#include "plain_option/BlackScholesPricer.hpp"
#include <iostream>
#include <iomanip>
#include <vector>

int main() {
    std::cout << std::fixed << std::setprecision(5);
    
    // Test Batch 1: T=0.25, K=65, sig=0.30, r=0.08, S=60
    EuropeanOption batch1(0.25, 65.0, 0.30, 0.08, 60.0);
    std::cout << "\n=== Batch 1 ===" << std::endl;
    std::cout << "Parameters: T=" << batch1.getTimeToMaturity()
              << ", K=" << batch1.getStrike()
              << ", sig=" << batch1.getVolatility()
              << ", r=" << batch1.getRiskFreeRate()
              << ", S=" << batch1.getSpotPrice() << std::endl;
    
    double call1 = BlackScholesPricer::calculateCallPrice(batch1);
    double put1 = BlackScholesPricer::calculatePutPrice(batch1);
    
    std::cout << "Calculated Call: " << call1 << " (Expected: 2.13337)" << std::endl;
    std::cout << "Calculated Put:  " << put1 << " (Expected: 5.84628)" << std::endl;
    
    // Test Put-Call Parity
    bool parity1 = BlackScholesPricer::verifyPutCallParity(batch1, call1, put1);
    std::cout << "Put-Call Parity: " << (parity1 ? "VALID" : "INVALID") << std::endl;
    
    // Test Batch 2: T=1.0, K=100, sig=0.2, r=0.0, S=100
    EuropeanOption batch2(1.0, 100.0, 0.2, 0.0, 100.0);
    std::cout << "\n=== Batch 2 ===" << std::endl;
    
    double call2 = BlackScholesPricer::calculateCallPrice(batch2);
    double put2 = BlackScholesPricer::calculatePutPrice(batch2);
    
    std::cout << "Calculated Call: " << call2 << " (Expected: 7.96557)" << std::endl;
    std::cout << "Calculated Put:  " << put2 << " (Expected: 7.96557)" << std::endl;
    
    // Test Batch 3: T=1.0, K=10, sig=0.50, r=0.12, S=5
    EuropeanOption batch3(1.0, 10.0, 0.50, 0.12, 5.0);
    std::cout << "\n=== Batch 3 ===" << std::endl;
    
    double call3 = BlackScholesPricer::calculateCallPrice(batch3);
    double put3 = BlackScholesPricer::calculatePutPrice(batch3);
    
    std::cout << "Calculated Call: " << call3 << " (Expected: 0.204058)" << std::endl;
    std::cout << "Calculated Put:  " << put3 << " (Expected: 4.07326)" << std::endl;
    
    // Test Batch 4: T=30.0, K=100.0, sig=0.30, r=0.08, S=100.0
    EuropeanOption batch4(30.0, 100.0, 0.30, 0.08, 100.0);
    std::cout << "\n=== Batch 4 ===" << std::endl;
    
    double call4 = BlackScholesPricer::calculateCallPrice(batch4);
    double put4 = BlackScholesPricer::calculatePutPrice(batch4);
    
    std::cout << "Calculated Call: " << call4 << " (Expected: 92.17570)" << std::endl;
    std::cout << "Calculated Put:  " << put4 << " (Expected: 1.24750)" << std::endl;
    
    return 0;
}
```

## Vorteile dieser Architektur:

1. **Klare Trennung**: Daten (EuropeanOption) vs. Berechnungen (BlackScholesPricer)
2. **Erweiterbar**: Einfach neue Pricer-Klassen hinzufügbar (Monte Carlo, FDM)
3. **Testfreundlich**: Separate TestData-Klasse für alle Homework-Batches
4. **Wiederverwendbar**: Pricer kann für verschiedene Option-Typen genutzt werden
5. **Zukunftssicher**: Vorbereitet für Greeks, Matrix-Pricing, etc.

Gefällt Ihnen diese Header-Struktur?