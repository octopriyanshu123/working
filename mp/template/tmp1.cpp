#include <cstdio>

template<typename T>
T abs(T x) {
    return (x >= 0) ? x : -x;
}

int main() {
    // Function pointer to abs with integer template specialization
    int (*foo)(int) = abs<int>; 
     // Use abs with int return type
    
    double (*kill)(double) = abs<double>;
    // Printing the absolute value of -42 as an int
    printf("%d\n", abs<int>(-42));  // Correctly prints abs for int
    
    // If you want to use the function pointer (foo), you can call:
    printf("%d\n", foo(-42));  // This will also call abs<int>(-42)
    printf("%f\n", kill(-4.2));

    
    return 0;
}
