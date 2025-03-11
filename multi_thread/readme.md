Certainly! Here's a sample `.md` file containing notes on how to retrieve the **PID** and **TID** for both the main thread and a new thread in a C++ program, as well as how to inspect these from the terminal.

### `notes.md`

```markdown
# C++ Program: Retrieving Process and Thread IDs (PID & TID)

## Overview
In this guide, we will:
1. Write a C++ program that creates a new thread.
2. Retrieve and print the **PID** of the main process and **TID** of the main thread and the new thread.
3. Show how to retrieve these IDs from the terminal.

## C++ Code to Get PID and TID

### Example Code: `main.cpp`

```cpp
#include <iostream>
#include <thread>
#include <chrono>
#include <unistd.h>  // For getpid() on Unix systems
#include <sys/types.h>  // For pid_t on Unix systems

// Define the class that will run on a new thread
class MyClassThread {
public:
    // A simple method to be executed in a separate thread
    void run() {
        std::cout << "New thread starting with ID: " << std::this_thread::get_id() << "\n";
        // Simulate some work with a sleep
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "New thread finished after 2 seconds with ID: " << std::this_thread::get_id() << "\n";
    }
};

int main() {
    // Print the process ID of the main program
    pid_t pid = getpid();
    std::cout << "Main process ID: " << pid << "\n";
    
    // Print the main thread ID
    std::cout << "Main thread ID: " << std::this_thread::get_id() << "\n";
    
    // Create an object of MyClassThread
    MyClassThread myClassThread;

    // Create a new thread that runs the `run` method of `MyClassThread`
    std::thread t(&MyClassThread::run, &myClassThread);

    // Wait for the thread to finish execution
    t.join();

    // End of the main program
    std::cout << "Main thread ends with ID: " << std::this_thread::get_id() << "\n";
    
    return 0;
}
```

### Explanation:
- **PID (Process ID)**: The `getpid()` function retrieves the process ID of the main program.
- **TID (Thread ID)**: `std::this_thread::get_id()` gives the unique thread ID for both the main thread and the new thread.

---

## Retrieving PID and TID from the Terminal

After running your C++ program, you can retrieve both the **PID** (Process ID) of the main program and the **TID** (Thread IDs) from the terminal.

### 1. Get the Process ID (PID) of the Main Program

Use the `ps` command to find the **PID** of your running program:

```bash
ps aux | grep <your_program_name>
```

Example output:
```
user     12345  0.0  0.1  123456  1234 pts/0    S+   12:34   0:00 ./my_program
```

- **PID**: The number `12345` represents the **PID** of your main program.

### 2. Get the Thread IDs (TID)

Since threads are treated as lightweight processes (LWP) in Linux, you can retrieve the thread IDs with the `ps` command as well.

```bash
ps -T -p <PID>
```

Example output:
```
PID   SPID TTY          TIME     CMD
12345 12346 pts/0    00:00:00 my_program
12345 12347 pts/0    00:00:00 my_program
```

- **Main thread (TID)**: `12346`
- **New thread (TID)**: `12347`

### 3. Using `top` to View Threads

1. Run `top`:
   ```bash
   top
   ```

2. Press `H` to toggle the thread view. This will display the threads under your process, each with a unique **TID**.

### 4. Using `pstree` for a Hierarchical View

The `pstree` command can show the process tree and thread hierarchy:

```bash
pstree -p <PID>
```

Example output:
```
my_program(12345)─┬─my_program(12346)
                  └─my_program(12347)
```

- **12346** and **12347** are the **TIDs** for the main thread and the new thread.

---

## Summary

- **PID (Process ID)** can be retrieved using `getpid()` in your C++ code or using terminal commands like `ps aux`.
- **TID (Thread ID)** can be retrieved using `std::this_thread::get_id()` in your C++ code or using terminal commands like `ps -T -p <PID>` to show the thread IDs.
- Use `top` or `pstree` for viewing thread information interactively in the terminal.

---

## References:
- [C++ Threading](https://en.cppreference.com/w/cpp/thread)
- [ps command documentation](https://man7.org/linux/man-pages/man1/ps.1.html)


---
# operator()()

In this code, you're using `operator()` inside the `Counter` class to make instances of `Counter` callable like functions. This is known as making a class "callable" or creating a functor. Here's how it works and why `operator()` is used:

### `operator()()` Explained:

1. **Functors in C++**: 
   - A functor is simply a class that overloads the `operator()`. This allows an instance of the class to be used as if it were a function.
   - By defining the `operator()`, the class `Counter` becomes callable like a regular function.

2. **The `operator()()`** is a special member function:
   - `operator()` is a member function of `Counter`. It defines what happens when an object of type `Counter` is called using the syntax `counter()`.
   - In this code, `operator()()` contains the logic to print the counter's value for each iteration.

### Why Use `operator()()`?

- **Threading with Callable Objects**: 
   - In the `main()` function, you're passing `Counter` objects to `std::thread`. The `std::thread` constructor expects a callable object (such as a function pointer, function object, or lambda). Since `Counter` objects are callable via `operator()`, they can be passed directly to `std::thread`.
   - When you create a thread with a `Counter` object, it essentially calls `operator()()` on that object in a separate thread.

### Why `operator()()` and Not Just `operator()`?

The reason for the `operator()`() definition (with two parentheses) is that it’s defining the **call operator** function within the class. The parentheses `()` signify that this is an **overloaded function** that can be invoked with the same syntax as calling a regular function.

Here’s a breakdown:

```cpp
void operator()() const
{
    for (int i = 0; i < mNumIterations; ++i) {
        cout << "Counter " << mId << " has value " << i << endl;
    }
}
```

This function will be invoked when an object of `Counter` is called like a function.

### How it works with threads:

When you pass `Counter{1, 20}` to `std::thread`, the thread calls the `operator()()` on the `Counter` object. The thread will then run the loop inside `operator()()` concurrently.

### Example:
```cpp
Counter c(2, 12);
std::thread t2(c);  // This creates a thread that will run the operator() function of c
```

In the line above, `c()` is equivalent to `c.operator()()`. It tells the `std::thread` to call `operator()()` in the new thread.

### Summary:

- `operator()()` allows an object of `Counter` to be called as a function.
- This is especially useful for passing objects to `std::thread`, which requires a callable to run in a separate thread.
- The extra `()` represents the call operator, which is what makes instances of the class callable like functions.