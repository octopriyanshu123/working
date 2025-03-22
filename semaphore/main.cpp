#include <iostream>
#include <thread>

std::binary_semaphore semSignalMainToThread(0), semSignalThreadToMain(0); // Semaphores to signal between main and thread

// Thread function
void ThreadFunction(){
    // Wait for a signal from the main thread
    // The thread will attempt to acquire the semaphore, blocking until it's released by the main thread
    semSignalMainToThread.acquire();

    std::cout << "[thread] Got the signal\n";  // Indicating the signal was received

    // Simulating some work in the thread by sleeping for 2 milliseconds
    std::this_thread::sleep_for(std::chrono::milliseconds(2));

    // After completing the work, signal the main thread by releasing the semaphore
    semSignalThreadToMain.release();
}

int main(){
    // Start the worker thread
    std::thread thread_worker(ThreadFunction);

    // Signal the thread to start by releasing the semaphore
    std::cout << "[main] Send the signal\n";
    semSignalMainToThread.release();

    // Wait for the worker thread to finish its work
    // The main thread will block until the worker thread signals it's done
    semSignalThreadToMain.acquire();

    // After receiving the signal, the main thread prints this message
    std::cout << "[main] Got the signal\n"; // response message from the worker thread
    
    // Join the thread to ensure it finishes before main exits
    thread_worker.join();

    return 0;
}
