cmake_minimum_required(VERSION 3.24)
project(option_pricer LANGUAGES C CXX)


# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Sets the compiler flags for C++ source code.
# - `-std=c++20`: Enables the C++20 standard for the compiler.
# - `-pedantic`: Enforces strict compliance with the C++ standard and issues warnings for non-standard code constructs.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -pedantic")

# Set CMake policy to use modern Boost targets
cmake_policy(SET CMP0167 NEW)

# Find Boost using modern approach
find_package(Boost REQUIRED COMPONENTS system filesystem random math)

add_executable(option_pricer
    main.cpp
    interfaces/IPricingStrategy.hpp
    interfaces/IParityValidator.hpp

    data/Option.cpp

    strategies/BlackScholesPricer.cpp

    context/OptionContext.cpp
    
    validators/PutCallParityValidator.cpp
)

target_include_directories(option_pricer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/data
    ${CMAKE_CURRENT_SOURCE_DIR}/interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/strategies
    ${CMAKE_CURRENT_SOURCE_DIR}/plain_option
    ${CMAKE_CURRENT_SOURCE_DIR}/context
    ${CMAKE_CURRENT_SOURCE_DIR}/validators
)

# Use modern Boost targets instead of legacy variables
target_link_libraries(option_pricer
    Boost::system
    Boost::filesystem
    Boost::random
    Boost::math
)