#include <iostream>
#include <memory>

// A simple function that takes a shared pointer to an integer
void printValue(std::shared_ptr<int> ptr) {
    std::cout << "Value (shared_ptr): " << *ptr << std::endl;
}

// Define a simple class
class MyClass {
public:
    MyClass(int value) : value(value) {
        std::cout << "MyClass constructor called. Value: " << value << std::endl;
    }

    ~MyClass() {
        std::cout << "MyClass destructor called. Value: " << value << std::endl;
    }

    void printValue() {
        std::cout << "Value in MyClass: " << value << std::endl;
    }

private:
    int value;
};

// Function that takes a shared pointer to a MyClass object
void processObject(std::shared_ptr<MyClass> ptr) {
    std::cout << "Processing MyClass object..." << std::endl;
    ptr->printValue();
}

// Function that takes a unique pointer
void processUniqueObject(std::unique_ptr<MyClass> ptr) {
    std::cout << "Processing MyClass object with unique_ptr..." << std::endl;
    ptr->printValue();
}

// Function that takes a weak pointer
void processWeakObject(std::weak_ptr<MyClass> weakPtr) {
    // Check if the object still exists
    if (auto sharedPtr = weakPtr.lock()) {
        std::cout << "Processing MyClass object with weak_ptr..." << std::endl;
        sharedPtr->printValue();
    } else {
        std::cout << "Object no longer exists (expired weak_ptr)." << std::endl;
    }
}

int main() {
    // Create a shared pointer for an integer
    std::shared_ptr<int> ptr = std::make_shared<int>(10);
    std::unique_ptr<char> char_ptr = std::make_unique<char>('a');  // Unique pointer to char

    // Output the character
    std::cout << "Character: " << *char_ptr << std::endl;

    // Pass the shared pointer to the printValue function
    printValue(ptr);

    // Create a shared pointer for MyClass
    std::shared_ptr<MyClass> myClassPtr = std::make_shared<MyClass>(20);

    // Pass the shared pointer to processObject
    processObject(myClassPtr);

    // Call the printValue method of MyClass using the shared pointer
    myClassPtr->printValue();

    // Create a unique pointer for MyClass
    std::unique_ptr<MyClass> uniquePtr = std::make_unique<MyClass>(30);

    // Pass the unique pointer to processUniqueObject
    processUniqueObject(std::move(uniquePtr));  // Move ownership to the function

    // Check if uniquePtr is null after moving it
    if (!uniquePtr) {
        std::cout << "uniquePtr is now null after being moved." << std::endl;
    }

    // Create a weak pointer from a shared pointer for MyClass
    std::weak_ptr<MyClass> weakPtr = myClassPtr;

    // Pass the weak pointer to processWeakObject
    processWeakObject(weakPtr);

    // Reset the shared pointer to see weak pointer behavior when the object is destroyed
    myClassPtr.reset();
    processWeakObject(weakPtr);  // Should show expired weak_ptr message

    return 0;
}