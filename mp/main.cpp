#include <iostream>

// Template to calculate factorial at compile-time
template <int N>
struct Factorial {
    static const int value = N * Factorial<N - 1>::value;
};

// Specialization for N=0 to end recursion
template <>
struct Factorial<0> {
    static const int value = 1;  // base case: factorial of 0 is 1
};

int main() {
    // Print factorial of 5 at compile-time
    std::cout << "Factorial of 5: " << Factorial<5>::value << std::endl;
    return 0;
}

