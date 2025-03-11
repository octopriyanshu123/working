#include <iostream>

// Use preprocessor macros defined during compilation
#ifndef NUM1
#define NUM1 0  // Default value if not defined during compilation
#endif
#ifndef NUM2
#define NUM2 0  // Default value if not defined during compilation
#endif

// Template for addition
template <int A, int B>
struct Add {
    static const int value = A + B;
};

// Template for subtraction
template <int A, int B>
struct Subtract {
    static const int value = A - B;
};

// Template for multiplication
template <int A, int B>
struct Multiply {
    static const int value = A * B;
};

// Template for division
template <int A, int B>
struct Divide {
    static const int value = (B != 0) ? A / B : 0;  // Division by zero handling
};

int main() {
    // Perform the arithmetic operations using template values (passing the constants directly to the templates)
    std::cout << "Addition of " << NUM1 << " and " << NUM2 << ": " << Add<NUM1, NUM2>::value << std::endl;
    std::cout << "Subtraction of " << NUM1 << " and " << NUM2 << ": " << Subtract<NUM1, NUM2>::value << std::endl;
    std::cout << "Multiplication of " << NUM1 << " and " << NUM2 << ": " << Multiply<NUM1, NUM2>::value << std::endl;
    std::cout << "Division of " << NUM1 << " and " << NUM2 << ": " << Divide<NUM1, NUM2>::value << std::endl;

    return 0;
}
