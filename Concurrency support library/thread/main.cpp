#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <vector>

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
        std::cout << "Thread " << id << " is running. Thread ID: " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Simulate work
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
        std::cout << "after joining, joinable: " << t.joinable() << '\n';
        t.join();
        std::cout << "after joining, joinable: " << t.joinable() << '\n';

        std::cout << "t's id after join: " << t.get_id() << '\n';
    }

    std::cout << "All threads have finished." << std::endl;

    return 0;
}
