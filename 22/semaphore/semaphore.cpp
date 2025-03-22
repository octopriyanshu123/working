// #include <iostream>
// #include <memory>
// #include <thread>
// #include <chrono>
// #include <semaphore>

// // Shared structure containing the data
// struct {
//     int data = 0;
// } my_data;

// template <typename T>
// class ThreadTask
// {
// public:
//     ThreadTask() {
//         std::cout << "ThreadTask created." << std::endl;
//     }

//     ~ThreadTask() {
//         std::cout << "ThreadTask destroyed." << std::endl;
//     }

//     // Define the thread function that will be executed by the thread
//     void threadFunction(int id) {
//         std::cout << "Thread executing on thread " << id << std::endl;

//         for (int i = 0; i < 100; ++i) {
//             // Acquire the semaphore before modifying shared data
//             semaPrint.acquire();
            
//             // Critical section: modify shared data
//             my_data.data++;
//             std::cout << "The thread id is: " << id << " my_data.data: " << my_data.data << std::endl;


//             // Sleep for a bit to allow other threads to do work
//             std::this_thread::sleep_for(std::chrono::milliseconds(100)); 

//             // Release the semaphore after modifying shared data
//             semaPrint.release();
//         }
//     }

// private:
//     std::binary_semaphore semaPrint{1}; // Semaphore with initial value 1 (binary semaphore)
// };

// int main(int argc, char **argv)
// {
//     // Create shared pointers for each thread task
//     std::shared_ptr<ThreadTask<int>> uiThreadPtr = std::make_shared<ThreadTask<int>>();
//     std::shared_ptr<ThreadTask<int>> rosThreadPtr = std::make_shared<ThreadTask<int>>();
//     std::shared_ptr<ThreadTask<int>> connectionThreadPtr = std::make_shared<ThreadTask<int>>();

//     // Create and start the threads
//     std::thread threadUi(&ThreadTask<int>::threadFunction, uiThreadPtr, 1);
//     std::thread threadRos(&ThreadTask<int>::threadFunction, rosThreadPtr, 2);
//     std::thread threadConnection(&ThreadTask<int>::threadFunction, connectionThreadPtr, 3);

//     // Wait for all threads to finish
//     threadUi.join();
//     threadRos.join();
//     threadConnection.join();

//     return 0;
// }


// #include <iostream>
// #include <memory>
// #include <thread>
// #include <chrono>
// #include <vector>

// // Shared structure containing the data
// struct {
//     int data = 0;
// } my_data;

// template <typename T>
// class ThreadTask
// {
// public:
//     ThreadTask() {
//         std::cout << "ThreadTask created." << std::endl;
//     }

//     ~ThreadTask() {
//         std::cout << "ThreadTask destroyed." << std::endl;
//     }

//     // Define the thread function that will be executed by the thread
//     void threadFunction(int id) {
//         std::cout << "Thread executing on thread " << id << std::endl;

//         for (int i = 0; i < 100; ++i) {
//             // Critical section: modify shared data without synchronization (failure point)
//             my_data.data++; // This operation is not atomic
//             std::cout << "Thread id: " << id << " my_data.data: " << my_data.data << std::endl;

//             // Sleep for a bit to allow other threads to do work
//             std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
//         }
//     }

// private:
// };

// int main(int argc, char **argv)
// {
//     const int numThreads = 10; // Set the number of threads
//     std::vector<std::shared_ptr<ThreadTask<int>>> threadPtrs(numThreads);

//     // Create shared pointers for each thread task
//     for (int i = 0; i < numThreads; ++i) {
//         threadPtrs[i] = std::make_shared<ThreadTask<int>>();
//     }

//     // Create a vector to hold the thread objects
//     std::vector<std::thread> threads;

//     // Create and start the threads
//     for (int i = 0; i < numThreads; ++i) {
//         threads.push_back(std::thread(&ThreadTask<int>::threadFunction, threadPtrs[i], i + 1));
//     }

//     // Wait for all threads to finish
//     for (auto& t : threads) {
//         t.join();
//     }

//     // Display the final value of my_data.data
//     std::cout << "Final value of my_data.data: " << my_data.data << std::endl;

//     return 0;
// }


#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <vector>
#include <semaphore>  // For std::counting_semaphore

// Shared structure containing the data and a semaphore to protect access to data
struct {
    int data = 0;
    std::counting_semaphore<1> sem{1};  // Semaphore with count 1 (binary semaphore)
} my_data;

template <typename T>
class ThreadTask
{
public:
    ThreadTask() {
        std::cout << "ThreadTask created." << std::endl;
    }

    ~ThreadTask() {
        std::cout << "ThreadTask destroyed." << std::endl;
    }

    // Define the thread function that will be executed by the thread
    void threadFunction(int id) {
        std::cout << "Thread executing on thread " << id << std::endl;

        for (int i = 0; i < 100; ++i) {
            // Acquire the semaphore before entering the critical section
            my_data.sem.try_acquire() ;// Acquire the semaphore (lock)

            // Critical section: modify shared data with synchronization using semaphore
            my_data.data++;  // This operation is now protected by the semaphore
            std::cout << "Thread id: " << id << " my_data.data: " << my_data.data << std::endl;

            // Release the semaphore after the critical section is done
            my_data.sem.release();  // Release the semaphore (unlock)

            // Sleep for a bit to allow other threads to do work
            std::this_thread::sleep_for(std::chrono::milliseconds(1000)); 
        }
    }

private:
};

int main(int argc, char **argv)
{
    const int numThreads = 10; // Set the number of threads
    std::vector<std::shared_ptr<ThreadTask<int>>> threadPtrs(numThreads);

    // Create shared pointers for each thread task
    for (int i = 0; i < numThreads; ++i) {
        threadPtrs[i] = std::make_shared<ThreadTask<int>>();
    }

    // Create a vector to hold the thread objects
    std::vector<std::thread> threads;

    // Create and start the threads
    for (int i = 0; i < numThreads; ++i) {
        threads.push_back(std::thread(&ThreadTask<int>::threadFunction, threadPtrs[i], i + 1));
    }

    // Wait for all threads to finish
    for (auto& t : threads) {
        t.join();
    }

    // Display the final value of my_data.data
    std::cout << "Final value of my_data.data: " << my_data.data << std::endl;

    return 0;
}
