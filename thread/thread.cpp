// #include <iostream>
// #include <thread>
// #include <chrono>
// using namespace std::chrono_literals;
// class thread1 {
// public:
//     thread1() {
//         std::cout << "Constructed thread 1" << std::endl;
//     }

//     void operator() () {
//         std::cout << "Running thread 1" << std::endl;
//         this->doWork(); 
//     }

//     void doWork() {
//         while (count--) {
//             std::cout << "I am thread 1" << std::endl;
//             std::this_thread::sleep_for(2000ms);  
//         }
//     }

// private:
//     int count = 5;
// };

// class thread2 {
// public:
//     thread2() {
//         std::cout << "Constructed thread 2" << std::endl;
//     }

//     void operator() () {
//         std::cout << "Running thread 2" << std::endl;
//         this->doWork();  
//     }

//     void doWork() {
//         while (count--) {
//             std::cout << "I am thread 2" << std::endl;
//             std::this_thread::sleep_for(2000ms); 
//         }
//     }
// private:
//     int count = 10;
// };

// int main(int argc, char** argv) {
//     thread1 t1;
//     thread2 t2;

//     std::thread thread1Obj(t1);  
//     std::thread thread2Obj(t2);  

//     thread1Obj.join();
//     thread2Obj.join();

//     return 0;
// }


// C++ Program to illustrate the use of counting_semaphore 
// #include <iostream> 
// #include <semaphore> 
// #include <thread> 
// using namespace std; 

// // Initialize semaphore with a count of 3 
// counting_semaphore<10> semaphore(3); 

// void worker(int id) 
// { 
// 	// aquiring 
// 	semaphore.acquire(); 

// 	// doing some work 
// 	cout << "Thread " << id << " acquired the semaphore."
// 		<< endl; 

// 	// releasing 
// 	semaphore.release(); 
// 	cout << "Thread " << id << " released the semaphore."
// 		<< endl; 
// } 

// // driver code 
// int main() 
// { 
// 	thread t1(worker, 1); 
// 	thread t2(worker, 2); 
// 	thread t3(worker, 3); 
// 	t1.join(); 
// 	t2.join(); 
// 	t3.join(); 
// 	return 0; 
// }



#include <iostream>
#include <thread>
#include <chrono>

class thread1 {
public:
    thread1() {
        std::cout << "Constructed thread 1" << std::endl;
    }

    void operator() () {
        std::cout << "Running thread 1" << std::endl;
        this->doWork(); 
    }

    void doWork() {
        while (count--) {
            std::cout << "I am thread 1" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));  // Explicit chrono literal
        }
    }

private:
    int count = 5;
};

class thread2 {
public:
    thread2() {
        std::cout << "Constructed thread 2" << std::endl;
    }

    void operator() () {
        std::cout << "Running thread 2" << std::endl;
        this->doWork();  
    }

    void doWork() {
        while (count--) {
            std::cout << "I am thread 2" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));  // Explicit chrono literal
        }
    }

private:
    int count = 10;
};

int main(int argc, char** argv) {
    thread1 t1;
    thread2 t2;

    std::thread thread1Obj(t1);  
    std::thread thread2Obj(t2);  

    thread1Obj.join();
    thread2Obj.join();

    return 0;
}
