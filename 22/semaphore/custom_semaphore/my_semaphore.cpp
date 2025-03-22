// my_semaphore.cpp
#include "my_semaphore.h"
#include <iostream>
#include <condition_variable>
#include <chrono>

template <typename T>
my_semaphore<T>::my_semaphore(T initial_count)
    : counter(initial_count) {}

template <typename T>
my_semaphore<T>::~my_semaphore() {}

template <typename T>
void my_semaphore<T>::release() {
    std::lock_guard<std::mutex> lock(mtx);
    ++counter;  // Increment counter (signal that resource is available)
    if (counter <= 0) {
        cv.notify_one();  // Notify one waiting thread if there are any
    }
}

template <typename T>
void my_semaphore<T>::acquire() {
    std::unique_lock<std::mutex> lock(mtx);
    while (counter <= 0) {
        cv.wait(lock);  // Block the thread if no resource is available
    }
    --counter;  // Decrement counter (take the resource)
}

template <typename T>
bool my_semaphore<T>::try_acquire() {
    std::lock_guard<std::mutex> lock(mtx);
    if (counter > 0) {
        --counter;  // Acquire resource
        return true;
    }
    return false;  // Cannot acquire, as counter is zero
}

template <typename T>
bool my_semaphore<T>::try_acquire_for(std::chrono::milliseconds duration) {
    std::unique_lock<std::mutex> lock(mtx);
    if (cv.wait_for(lock, duration, [this]() { return counter > 0; })) {
        --counter;  // Acquire resource
        return true;
    }
    return false;  // Could not acquire within the specified duration
}

template <typename T>
bool my_semaphore<T>::try_acquire_until(std::chrono::steady_clock::time_point time_point) {
    std::unique_lock<std::mutex> lock(mtx);
    if (cv.wait_until(lock, time_point, [this]() { return counter > 0; })) {
        --counter;  // Acquire resource
        return true;
    }
    return false;  // Could not acquire before the time point
}

template <typename T>
T my_semaphore<T>::max() {
    return std::numeric_limits<T>::max();  // Return the maximum possible value for T
}

// Explicit instantiation for common types (int)
template class my_semaphore<int>;
