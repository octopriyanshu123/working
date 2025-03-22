#include <pthread.h>
#include <iostream>
void* threadFunction(void* arg) {
    // Thread logic here
    return nullptr;
}



// Thread function returning a pointer to an integer
void* threadFunction2(void* arg) {
    // Thread logic here
    std::cout << "Jhi from the thread!" << std::endl;

    // Create a dynamically allocated integer to return
    int* result = new int(42);  // Allocating memory and initializing with 42

    // Return the pointer to the integer
    return static_cast<void*>(result); // cast to void* because pthread requires void* return type
}

int main() {
    pthread_t thread;
    
    // Create a new thread that runs threadFunction2
    pthread_create(&thread, nullptr, threadFunction2, nullptr);

    // Variable to store the thread's return value
    void* result;
    
    // Wait for the thread to finish and get the return value
    pthread_join(thread, &result);

    // Convert the void* result back to the original type (int*)
    int* returnedValue = static_cast<int*>(result);
    
    // Print the returned value from the thread
    std::cout << "Returned value from thread: " << *returnedValue << std::endl;

    // Don't forget to delete the allocated memory to avoid memory leak
    delete returnedValue;

    return 0;
}
