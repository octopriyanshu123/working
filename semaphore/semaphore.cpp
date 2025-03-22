// #include <iostream>
// #include <memory>
// #include <thread>
// #include <chrono>
// // #include semaphore.h

// std::binary_semaphore semaPrint{1}; 

// // Define uiThread class
// class uiThread
// {
// public:
//     uiThread() {
//         std::cout << "uiThread created." << std::endl;
//     }
//     ~uiThread() {
//         std::cout << "uiThread destroyed." << std::endl;
//     }

//     // Define the thread function that will be executed by the thread
//     void threadFunction(int id) {
//         std::cout << "uiThread executing on thread " << id << std::endl;

//         for (int i = 0; i < 10; ++i) {
//             data++;
//             semaPrint.acquire();
//             std::cout << "The thread id is: " << id << " " << data << std::endl;
//             semaPrint.release();
//                         std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Sleep for 100ms to allow the main thread to do work
//         }

//     }

//     private:
//     int data = 0;
// };

// // Define rosThread class
// class rosThread
// {
// public:
//     rosThread() {
//         std::cout << "rosThread created." << std::endl;
//     }
//     ~rosThread() {
//         std::cout << "rosThread destroyed." << std::endl;
//     }

//     // Define the thread function
//     void threadFunction(int id) {
//         std::cout << "rosThread executing on thread " << id << std::endl;
//         for (int i = 0; i < 10; ++i) {
//             data++;
//             semaPrint.acquire();
//             std::cout << "The thread id is: " << id << " " << data << std::endl;
//             semaPrint.release();
//                         std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Sleep for 100ms to allow the main thread to do work
//         }
//     }

//     private:
//     int data =  0;
// };

// // Define connectionThread class
// class connectionThread
// {
// public:
//     connectionThread() {
//         std::cout << "connectionThread created." << std::endl;
//     }
//     ~connectionThread() {
//         std::cout << "connectionThread destroyed." << std::endl;
//     }

//     // Define the thread function
//     void threadFunction(int id) {
//         std::cout << "connectionThread executing on thread " << id << std::endl;
        
//         // Run the loop for a fixed number of iterations instead of indefinitely
//         for (int i = 0; i < 10; ++i) {
//             data++;
//             semaPrint.acquire();
//             std::cout << "The thread id is: " << id << " " << data << std::endl;
//             semaPrint.release();
//             std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Sleep for 100ms to allow the main thread to do work
//         }
//     }

// private:
//     int data =  0;
// };

// int main(int argc, char **argv)
// {
    
//     // Create shared pointers for each class
//     std::shared_ptr<uiThread> uiThreadPtr = std::make_shared<uiThread>();
//     std::shared_ptr<rosThread> rosThreadPtr = std::make_shared<rosThread>();
//     std::shared_ptr<connectionThread> connectionThreadPtr = std::make_shared<connectionThread>();

//     // Create and start the threads
//     std::thread threadUi(&uiThread::threadFunction, uiThreadPtr, 1);
//     std::thread threadRos(&rosThread::threadFunction, rosThreadPtr, 2);
//     std::thread threadConnection(&connectionThread::threadFunction, connectionThreadPtr, 3);

//     // Wait for all threads to finish
//     threadUi.join();
//     threadRos.join();
//     threadConnection.join();

//     return 0;
// }


#include <bits/semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;
{
    
}


int main() {
    sem_t *semaphore;

    semaphore = sem_open("my_semaphore", O_CREAT | O_EXCL, 0666, 1);

    if (semaphore == SEM_FAILED) {
        perror("sem_open");
        return 1;
    }

    sem_post(semaphore); 
    sem_wait(semaphore);

    sem_close(semaphore);
    sem_unlink("my_semaphore");
    return 0;
}