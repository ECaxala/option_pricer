#ifndef MATRIX_PRINT_UTILS_HPP
#define MATRIX_PRINT_UTILS_HPP

#include <iostream>
#include <vector>
#include <iomanip>

/**
 * @brief Utility function to print a matrix with row and column labels
 *
 * This function prints a matrix in a formatted table with:
 * - Row labels on the left
 * - Column labels on the top
 * - Tab-separated values for alignment
 *
 * @param rowLabels Vector of numeric labels for rows (e.g., expiry times, volatilities, strikes)
 * @param colLabels Vector of numeric labels for columns (e.g., spot prices)
 * @param matrix 2D vector containing the matrix values to print
 * @param rowHeader Header text for the row label column (e.g., "T\\S", "Vol\\S", "K\\S")
 * @param precision Number of decimal places for all values (default: 6)
 */
inline void printMatrix(const std::vector<double>& rowLabels,
                       const std::vector<double>& colLabels,
                       const std::vector<std::vector<double>>& matrix,
                       const std::string& rowHeader,
                       int precision = 6)
{
    // Set precision for output
    std::cout << std::fixed << std::setprecision(precision);
    
    // Print header row
    std::cout << rowHeader << "\t\t";
    for (const auto& colLabel : colLabels) {
        std::cout << colLabel << "\t";
    }
    std::cout << std::endl;
    
    // Print matrix rows with row labels
    for (size_t i = 0; i < rowLabels.size() && i < matrix.size(); ++i) {
        std::cout << rowLabels[i] << "\t";
        for (size_t j = 0; j < colLabels.size() && j < matrix[i].size(); ++j) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    
    // Reset to default precision
    std::cout << std::defaultfloat;
}

#endif // MATRIX_PRINT_UTILS_HPh