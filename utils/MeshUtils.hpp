#ifndef MESH_UTILS_HPP
#define MESH_UTILS_HPP

#include <vector>
#include <stdexcept>
#include <cmath>

/**
 * @brief Global mesh function 
 *
 * Creates an array of doubles separated by a mesh size h.
 * Example: meshArray(10.0, 50.0, 1.0) creates [10, 11, 12, ..., 50]
 *
 * @param start Start value (e.g. 10.0)
 * @param end End value (e.g. 50.0)
 * @param meshSize Step size h (e.g. 1.0)
 * @return std::vector<double> Array of values
 */
inline std::vector<double> meshArray(double start, double end, double meshSize)
{
    // Parameter validation
    if (meshSize <= 0.0) {
        throw std::invalid_argument("Mesh size must be positive");
    }
    
    if (start >= end) {
        throw std::invalid_argument("Start must be less than end");
    }
    
    std::vector<double> result;
    
    // Calculate number of steps
    int numSteps = static_cast<int>(std::ceil((end - start) / meshSize));
    
    // Reserve memory for better performance
    result.reserve(numSteps + 1);
    
    // Create monotonically increasing range
    for (int i = 0; i <= numSteps; ++i) {
        double value = start + i * meshSize;
        if (value <= end) {
            result.push_back(value);
        }
    }
    
    return result;
}

#endif // MESH_UTILS_HPP