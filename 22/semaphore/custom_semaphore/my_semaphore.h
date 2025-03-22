// my_semaphore.h
#ifndef MY_SEMAPHORE_H
#define MY_SEMAPHORE_H

#include <chrono>
#include <mutex>
#include <condition_variable>
#include <atomic>

template <typename T>
class my_semaphore {
public:
    // Constructor to initialize the semaphore with a specific initial count
    explicit my_semaphore(T initial_count);

    // Destructor (no specific cleanup needed here)
    ~my_semaphore();

    // Release function - increment the counter and unblock a thread if needed
    void release();

    // Acquire function - decrement the counter or block until it can
    void acquire();

    // try_acquire function - attempts to acquire without blocking
    bool try_acquire();

    // try_acquire_for function - attempts to acquire, blocking for a specified duration
    bool try_acquire_for(std::chrono::milliseconds duration);

    // try_acquire_until function - attempts to acquire until a specific time point
    bool try_acquire_until(std::chrono::steady_clock::time_point time_point);

    // Static method to return the maximum possible count
    static T max();

private:
    T counter;  // The internal counter representing the available permits (resources)
    std::mutex mtx;  // Mutex to protect the counter
    std::condition_variable cv;  // Condition variable for thread synchronization
};

#endif // MY_SEMAPHORE_H
