# Set CMake policy to use modern Boost targets
cmake_policy(SET CMP0167 NEW)

# Find Boost using modern approach
find_package(Boost REQUIRED COMPONENTS system filesystem random math)

add_executable(comp_finance_app
    main.cpp
    interfaces/IPricingStrategy.hpp
    interfaces/IParityValidator.hpp

    data/Option.cpp

    strategies/BlackScholesPricer.cpp

    context/OptionContext.cpp
    
    validators/PutCallParityValidator.cpp
)

target_include_directories(comp_finance_app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/data
    ${CMAKE_CURRENT_SOURCE_DIR}/interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/strategies
    ${CMAKE_CURRENT_SOURCE_DIR}/plain_option
    ${CMAKE_CURRENT_SOURCE_DIR}/context
    ${CMAKE_CURRENT_SOURCE_DIR}/validators
)

# Use modern Boost targets instead of legacy variables
target_link_libraries(comp_finance_app
    Boost::system
    Boost::filesystem
    Boost::random
    Boost::math
)