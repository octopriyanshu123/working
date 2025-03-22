#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

std::atomic<bool> cancelFlag(false);

void task() {
    for (int i = 0; i < 10; ++i) {
        if (cancelFlag.load()) {
            std::cout << "Task was cancelled before completion.\n";
            return; // Gracefully stop the task
        }
        std::cout << "Task is running: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simulate work
    }
    std::cout << "Task completed successfully.\n";
}

int main() {
    std::thread t(task);

    // Simulate some condition that leads to cancellation
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    cancelFlag.store(true);  // Signal cancellation

    t.join();  // Wait for the task to finish
    return 0;
}