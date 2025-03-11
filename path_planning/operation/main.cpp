#include <iostream>
#include "ArithmeticLib.h"

int main() {
    double a = 10.5, b = 2.5;
    
    // Perform arithmetic operations using the library
    std::cout << "Addition: " << ArithmeticLib::add(a, b) << std::endl;
    std::cout << "Subtraction: " << ArithmeticLib::subtract(a, b) << std::endl;
    std::cout << "Multiplication: " << ArithmeticLib::multiply(a, b) << std::endl;
    
    try {
        std::cout << "Division: " << ArithmeticLib::divide(a, b) << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
