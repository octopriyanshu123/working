#include <iostream>
#include <mutex>
#include <thread>

std::mutex data_mutex;  // Mutex to protect shared data
int my_data = 0;        // Shared data

void increment_data_unique_lock(int id) {
    // Create a unique_lock and lock the mutex
    std::unique_lock<std::mutex> lock(data_mutex);

    // Critical section: modify the shared data
    my_data++;
    std::cout << "Thread " << id << " incremented my_data to " << my_data << std::endl;

    // You can manually unlock the mutex here if needed
    lock.unlock();
    std::cout << "Thread " << id << " manually unlocked the mutex." << std::endl;

    // You can lock it again if necessary
    lock.lock();
    my_data++;
    std::cout << "Thread " << id << " incremented my_data again to " << my_data << std::endl;

    // The lock will be automatically released when lock goes out of scope
}

int main() {
    std::thread t1(increment_data_unique_lock, 1);
    std::thread t2(increment_data_unique_lock, 2);

    t1.join();
    t2.join();

    std::cout << "Final value of my_data: " << my_data << std::endl;

    return 0;
}
