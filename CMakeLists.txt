# Set CMake policy to use modern Boost targets
cmake_policy(SET CMP0167 NEW)

# Find Boost using modern approach
find_package(Boost REQUIRED COMPONENTS system filesystem random)

add_executable(comp_finance_app
    main.cpp
    plain_option/EuropeanOption.cpp
)

target_include_directories(comp_finance_app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Use modern Boost targets instead of legacy variables
target_link_libraries(comp_finance_app
    Boost::system
    Boost::filesystem
    Boost::random
)