# Option Pricer - Strategy Pattern Implementation

A professional C++ option pricing library demonstrating advanced software engineering principles through the Strategy Pattern. This project showcases clean architecture, mathematical finance knowledge, and modern C++ development practices.

## 🎯 Project Overview

This project implements a flexible option pricing framework using the **Strategy Pattern**, allowing for easy extension with different pricing models. Currently features the Black-Scholes model with Put-Call Parity validation, built with modern C++20 and industry-standard practices.

### Key Features

- **Strategy Pattern Architecture** - Modular design for easy extension with new pricing models
- **Black-Scholes Implementation** - Exact analytical solution for European options
- **Put-Call Parity Validation** - Mathematical relationship verification between call and put options
- **Comprehensive Testing** - Automated test batches with precision validation
- **Modern C++20** - Leveraging latest language features and best practices
- **High-Performance Libraries** - Boost and STL integration for performance and security
- **Professional Build System** - CMake configuration with comprehensive dependency management

## 🏗️ Architecture

The project follows a clean, layered architecture implementing the Strategy Pattern:

```
┌─────────────────────────────────────────────────────────────────┐
│                        STRATEGY PATTERN                         │
└─────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────┐
│                       CONTEXT LAYER                             │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  ┌─────────────────────┐    ┌─────────────────────────────────┐  │
│  │   OptionContext     │    │   PutCallParityValidator        │  │
│  │                     │    │                                 │  │
│  │ - option: Option    │    │ + validateParity()              │  │
│  │ - pricer: IPricer*  │    │ + callFromPut()                 │  │
│  │                     │    │ + putFromCall()                 │  │
│  │ + setStrategy()     │    │                                 │  │
│  │ + calculatePrice()  │    │                                 │  │
│  │ + verifyParity()    │    │                                 │  │
│  └─────────────────────┘    └─────────────────────────────────┘  │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
                                │
                                │ implements
                                ▼
┌─────────────────────────────────────────────────────────────────┐
│                    STRATEGY INTERFACE                           │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  ┌─────────────────────────────────────────────────────────────┐  │
│  │              IPricingStrategy                               │  │
│  │                                                             │  │
│  │ + calculateCallPrice(option) : double                       │  │
│  │ + calculatePutPrice(option) : double                        │  │
│  │ + getName() : string                                        │  │
│  └─────────────────────────────────────────────────────────────┘  │
│                                ▲                               │
└─────────────────────────────────────────────────────────────────┘
                                │
                                │ implements
                                ▼
┌─────────────────────────────────────────────────────────────────┐
│                  CONCRETE STRATEGIES                            │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  ┌─────────────────────────────────────────────────────────────┐  │
│  │            BlackScholesPricer                               │  │
│  │                                                             │  │
│  │ + calculateCallPrice() : double                             │  │
│  │ + calculatePutPrice() : double                              │  │
│  │ - calculateD1() : double                                    │  │
│  │ - calculateD2() : double                                    │  │
│  │ - normalCDF() : double                                      │  │
│  └─────────────────────────────────────────────────────────────┘  │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
                                │
                                │ uses
                                ▼
┌─────────────────────────────────────────────────────────────────┐
│                      DATA MODEL                                 │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  ┌─────────────────────────────────────────────────────────────┐  │
│  │                    Option                                   │  │
│  │                                                             │  │
│  │ - T: double        (Exercise Date)                          │  │
│  │ - K: double        (Strike Price)                           │  │
│  │ - sig: double      (Volatility)                             │  │
│  │ - r: double        (Risk-free Rate)                         │  │
│  │ - S: double        (Asset Price)                            │  │
│  │                                                             │  │
│  │ + toString() : string                                       │  │
│  │ + isValid() : bool                                          │  │
│  └─────────────────────────────────────────────────────────────┘  │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

## 🚀 Quick Start

### Prerequisites

- **C++20** compatible compiler (GCC 10+, Clang 10+, MSVC 2019+)
- **CMake 3.24+**
- **Boost Libraries** (system, filesystem, random, math)

### Building the Project

```bash
# Clone the repository
git clone <repository-url>
cd option_pricer

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build the project
make

# Run the application
./option_pricer
```

### Expected Output

The application runs comprehensive tests demonstrating:

1. **Black-Scholes Pricing** - Calculates call and put option prices
2. **Put-Call Parity Validation** - Verifies mathematical relationships
3. **Precision Testing** - Validates results against expected values

```
=== BATCH 1 ===
Parameters: T=0.25, K=65, σ=0.3, r=0.08, S=60
Call Price: 2.13337 (Expected: 2.13337)
Put Price: 5.84628 (Expected: 5.84628)

=== PUT-CALL PARITY TESTING ===
--- BATCH 1 Parity Test ---
Direct Call: 2.13337, Parity Call: 2.13337
Direct Put: 5.84628, Parity Put: 5.84628
Parity Valid: YES

=== ALL TESTS PASSED ===
```

## 🔧 Technical Implementation

### Core Components

- **[`Option`](data/Option.hpp)** - Encapsulates option parameters with validation
- **[`IPricingStrategy`](interfaces/IPricingStrategy.hpp)** - Strategy interface for pricing models
- **[`BlackScholesPricer`](strategies/BlackScholesPricer.hpp)** - Analytical Black-Scholes implementation
- **[`OptionContext`](context/OptionContext.hpp)** - Context class managing strategy execution
- **[`PutCallParityValidator`](validators/PutCallParityValidator.hpp)** - Mathematical relationship validation

### Design Patterns

- **Strategy Pattern** - Enables runtime algorithm selection and easy extension
- **RAII** - Automatic resource management with smart pointers
- **Interface Segregation** - Clean separation of concerns through focused interfaces

### Mathematical Models

- **Black-Scholes Formula** - Exact analytical solution for European options
- **Put-Call Parity** - C + Ke^(-rT) = P + S relationship validation
- **Normal Distribution** - Boost.Math integration for statistical functions

### Performance & Security

- **Boost Libraries** - Industry-standard C++ libraries for enhanced performance and reliability
  - `Boost.Math` - High-precision mathematical functions and distributions
  - `Boost.Random` - Cryptographically secure random number generation
  - `Boost.System` - Cross-platform system error handling
- **STL Integration** - Leveraging Standard Template Library for optimal performance
  - Smart pointers for memory safety and automatic resource management
  - Standard containers for efficient data structures
  - Algorithm library for optimized mathematical operations

## 📊 Test Results

The project includes comprehensive test batches validating pricing accuracy:

| Test Batch | Parameters | Call Price | Put Price | Parity Valid |
|------------|------------|------------|-----------|--------------|
| Batch 1 | T=0.25, K=65, σ=0.30, r=0.08, S=60 | 2.13337 | 5.84628 | ✅ |
| Batch 2 | T=1.0, K=100, σ=0.20, r=0.0, S=100 | 7.96557 | 7.96557 | ✅ |
| Batch 3 | T=1.0, K=10, σ=0.50, r=0.12, S=5 | 0.204058 | 4.07326 | ✅ |
| Batch 4 | T=30.0, K=100, σ=0.30, r=0.08, S=100 | 92.17570 | 1.24750 | ✅ |

## 🎯 Professional Highlights

### Software Engineering Excellence
- **Clean Architecture** - Modular design following SOLID principles
- **Modern C++** - Leveraging C++20 features and best practices
- **Memory Safety** - Smart pointers and RAII patterns for automatic resource management
- **Performance Optimization** - Boost and STL integration for maximum efficiency
- **Security Focus** - Industry-standard libraries for secure mathematical computations
- **Comprehensive Testing** - Automated validation with precision checks

### Financial Mathematics Expertise
- **Black-Scholes Model** - Industry-standard option pricing implementation
- **Put-Call Parity** - Deep understanding of option relationships
- **Numerical Precision** - Careful handling of floating-point calculations
- **Mathematical Validation** - Rigorous testing against known results

### Development Best Practices
- **Version Control Ready** - Professional Git repository structure
- **Build System** - Modern CMake configuration with dependency management
- **Library Integration** - Strategic use of Boost and STL for performance and security
- **Documentation** - Clear code comments and architectural documentation
- **Extensibility** - Strategy pattern enables easy model additions

## 🔮 Future Extensions

The architecture supports easy addition of:

- **Monte Carlo Pricing** - Simulation-based option valuation
- **Finite Difference Methods** - Numerical PDE solutions
- **American Options** - Early exercise capability
- **Greeks Calculation** - Risk sensitivities (Delta, Gamma, Vega, Theta)
- **Exotic Options** - Barrier, Asian, and other complex instruments

## 📝 License

This project demonstrates professional software development practices and mathematical finance implementation for educational and portfolio purposes.

---

*This project showcases advanced C++ development, mathematical finance knowledge, and software architecture skills suitable for quantitative finance, fintech, and high-performance computing roles.*