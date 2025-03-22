#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>

// Shared structure containing the data
struct {
    int data = 0;
} my_data;

std::mutex data_mutex; // Mutex to protect shared data

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
    void threadFunctionLock(int id) {
        std::cout << "Thread executing on thread " << id << std::endl;

        for (int i = 0; i < 100; ++i) {
            // Lock using std::lock_guard
            std::lock_guard<std::mutex> lock(data_mutex); // This ensures exclusive access to my_data
            my_data.data++; // This operation is now thread-safe
            std::cout << "Thread id: " << id << " my_data.data: " << my_data.data << std::endl;

            // Sleep for a bit to allow other threads to do work
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
        }
    }

    void threadFunctionTryLock(int id) {
        std::cout << "Thread executing on thread " << id << std::endl;

        for (int i = 0; i < 100; ++i) {
            // Try to lock using try_lock
            if (data_mutex.try_lock()) {
                // If the lock is acquired, modify the shared data
                my_data.data++;
                std::cout << "Thread id: " << id << " my_data.data: " << my_data.data << std::endl;
                data_mutex.unlock(); // Unlock the mutex when done

            } else {
                std::cout << "Thread id: " << id << " could not acquire lock, retrying...\n";
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
        }
    }

private:
};

int main(int argc, char **argv)
{
    const int numThreads = 10; 
    std::vector<std::shared_ptr<ThreadTask<int>>> threadPtrs(numThreads);

    for (int i = 0; i < numThreads; ++i) {
        threadPtrs[i] = std::make_shared<ThreadTask<int>>();
    }

    std::vector<std::thread> threads;

    std::cout << "\nUsing std::lock_guard:" << std::endl;
    for (int i = 0; i < numThreads; ++i) {
        threads.push_back(std::thread(&ThreadTask<int>::threadFunctionLock, threadPtrs[i], i + 1));
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Final value of my_data.data after using std::lock_guard: " << my_data.data << std::endl;

    my_data.data = 0;
    threads.clear();

    std::cout << "\nUsing std::mutex::try_lock:" << std::endl;
    for (int i = 0; i < numThreads; ++i) {
        threads.push_back(std::thread(&ThreadTask<int>::threadFunctionTryLock, threadPtrs[i], i + 1));
    }
    for (auto& t : threads) {
        t.join();
    }
    std::cout << "Final value of my_data.data after using std::mutex::try_lock: " << my_data.data << std::endl;

    return 0;
}
