In C++, cooperative cancellation refers to a pattern where a task or operation can voluntarily stop or "cancel" itself when requested, rather than being forcefully terminated by an external process. The task or thread periodically checks for cancellation signals and decides when it is safe to stop based on that signal. This is often done in multi-threaded or asynchronous programming scenarios where you want tasks to have a chance to clean up resources, complete operations safely, and exit gracefully.

### Key Concepts of Cooperative Cancellation in C++:

1. **Cancellation Request**: A cancellation request typically comes from another thread or component of the program, often through the use of a shared flag, condition variable, or some other signaling mechanism.

2. **Periodic Checks**: The task or thread being canceled periodically checks if it has received a cancellation signal. It does not stop immediately, but instead cooperates with the cancellation request by periodically looking for it in its execution flow. For example, it could check a boolean flag or a condition variable.

3. **Graceful Cleanup**: When the task detects the cancellation signal, it should perform any necessary cleanup operations, like releasing resources, closing file handles, or saving intermediate state, before exiting.

4. **Non-Forceful**: Unlike abortive cancellation methods (like forcibly terminating a thread), cooperative cancellation allows the task to decide when it is safe to cancel itself and prevent any dangerous side effects from abrupt termination.

### Example: Cooperative Cancellation in C++

Here’s a simple example that demonstrates cooperative cancellation using a cancellation flag:

```cpp
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
```

### Explanation:
1. **Atomic Flag**: We use `std::atomic<bool> cancelFlag` to safely communicate the cancellation request between threads. `std::atomic` ensures that the cancellation flag is updated and read in a thread-safe manner.
   
2. **Cancellation Check**: Inside the `task` function, the thread regularly checks the `cancelFlag`. If the flag is set to `true`, the task cancels itself by returning early and printing a cancellation message.
   
3. **Sleep and Simulate Work**: The task simulates some work by sleeping for 500 milliseconds between each iteration. During this time, the main thread can signal cancellation by setting the flag after some delay.

4. **Graceful Stop**: The task stops gracefully when it detects the cancellation signal, rather than continuing to run or being forcefully terminated.

### Benefits of Cooperative Cancellation:
- **Graceful Shutdown**: The task has the opportunity to release resources and clean up before terminating.
- **Predictability**: Tasks can decide for themselves when and how to cancel, making the program flow more predictable and easier to manage.
- **Safety**: Unlike brute-force cancellation (e.g., terminating a thread immediately), cooperative cancellation avoids issues like data corruption, resource leaks, or inconsistent states.

### Common Use Cases:
- **Multithreading**: In multi-threaded programs, cooperative cancellation is useful for stopping threads gracefully.
- **Asynchronous Programming**: In asynchronous systems, tasks might need to periodically check for cancellation signals without abruptly terminating, which can help avoid race conditions or incomplete operations.

Cooperative cancellation is an effective way to handle cancellations safely and predictably in C++ programs, especially when managing complex tasks or multi-threaded environments.


The features you're referring to are part of the C++20 and C++26 standards, specifically focusing on the modern features for managing cancellation and stop mechanisms in multi-threaded programming using `std::jthread` and related types like `stop_token`, `stop_source`, and `stop_callback`. Let's go through these concepts and types one by one with an illustrative example and comments.

### 1. **Stop Token Types**

#### 1.1. `stop_token` (C++20)
- **Description**: A `stop_token` provides an interface to query if a cancellation request has been made, typically used with `std::jthread`. It's associated with a `std::stop_source`, which can request the cancellation of one or more threads.

```cpp
#include <iostream>
#include <thread>
#include <stop_token>

void task(std::stop_token stopToken) {
    for (int i = 0; i < 10; ++i) {
        if (stopToken.stop_requested()) {
            std::cout << "Cancellation requested. Stopping task.\n";
            return; // Graceful cancellation when the stop token signals cancellation
        }
        std::cout << "Working on iteration: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simulate work
    }
}

int main() {
    std::stop_source stopSource;
    std::jthread t(task, stopSource.get_token());

    std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // Let the task run for a while
    stopSource.request_stop();  // Request cancellation

    t.join(); // Wait for thread to finish
    return 0;
}
```

#### 1.2. `never_stop_token` (C++26)
- **Description**: `never_stop_token` is a stop token where cancellation is not possible. It's a token that always returns `false` for `stop_requested()`, meaning the task can't be canceled.

```cpp
#include <iostream>
#include <thread>
#include <stop_token>

void task(std::stop_token stopToken) {
    while (true) {
        if (stopToken.stop_requested()) {
            std::cout << "Cancellation requested. Stopping task.\n";
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simulate work
    }
}

int main() {
    std::jthread t(task, std::never_stop_token{});
    t.join(); // Task runs indefinitely, can't be canceled by stop token
    return 0;
}
```

#### 1.3. `inplace_stop_token` (C++26)
- **Description**: `inplace_stop_token` is a stop token that directly references the stop state of an associated `std::inplace_stop_source`. This allows finer-grained control of stop state in a multithreaded environment.

```cpp
#include <iostream>
#include <thread>
#include <stop_token>

void task(std::inplace_stop_token stopToken) {
    for (int i = 0; i < 10; ++i) {
        if (stopToken.stop_requested()) {
            std::cout << "Cancellation requested. Stopping task.\n";
            return;
        }
        std::cout << "Working on iteration: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    std::inplace_stop_source stopSource;
    std::jthread t(task, stopSource.get_token());

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    stopSource.request_stop(); // Request cancellation via the stop source

    t.join();
    return 0;
}
```

### 2. **Stop Source Types**

#### 2.1. `stop_source` (C++20)
- **Description**: A `stop_source` is responsible for requesting cancellation of one or more threads. It provides a stop token that can be passed to threads.

```cpp
#include <iostream>
#include <thread>
#include <stop_token>

void task(std::stop_token stopToken) {
    for (int i = 0; i < 10; ++i) {
        if (stopToken.stop_requested()) {
            std::cout << "Cancellation requested. Stopping task.\n";
            return;
        }
        std::cout << "Working on iteration: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    std::stop_source stopSource;  // Create stop source
    std::jthread t(task, stopSource.get_token()); // Pass stop token to task

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    stopSource.request_stop(); // Request cancellation

    t.join(); // Wait for thread to finish
    return 0;
}
```

#### 2.2. `inplace_stop_source` (C++26)
- **Description**: `inplace_stop_source` is a stoppable source that owns the stop state. It provides more control over when and how cancellation is requested.

```cpp
#include <iostream>
#include <thread>
#include <stop_token>

void task(std::inplace_stop_token stopToken) {
    for (int i = 0; i < 10; ++i) {
        if (stopToken.stop_requested()) {
            std::cout << "Cancellation requested. Stopping task.\n";
            return;
        }
        std::cout << "Working on iteration: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    std::inplace_stop_source stopSource;
    std::jthread t(task, stopSource.get_token());

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    stopSource.request_stop();  // Request cancellation via stop source

    t.join();
    return 0;
}
```

### 3. **Stop Callback Types**

#### 3.1. `stop_callback` (C++20)
- **Description**: A `stop_callback` is used to register a callback that will be invoked when a stop request is made. It helps to clean up resources when cancellation occurs.

```cpp
#include <iostream>
#include <thread>
#include <stop_token>

void cleanup() {
    std::cout << "Cleanup after cancellation.\n";
}

void task(std::stop_token stopToken) {
    stopToken.stop_callback(cleanup);  // Register callback to cleanup on stop
    for (int i = 0; i < 10; ++i) {
        if (stopToken.stop_requested()) {
            std::cout << "Cancellation requested. Stopping task.\n";
            return;
        }
        std::cout << "Working on iteration: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    std::stop_source stopSource;
    std::jthread t(task, stopSource.get_token());

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    stopSource.request_stop(); // Request cancellation

    t.join();
    return 0;
}
```

#### 3.2. `inplace_stop_callback` (C++26)
- **Description**: Similar to `stop_callback`, but specific to `std::inplace_stop_token` where the callback is registered directly with the `inplace_stop_token`.

```cpp
#include <iostream>
#include <thread>
#include <stop_token>

void cleanup() {
    std::cout << "Cleanup after cancellation.\n";
}

void task(std::inplace_stop_token stopToken) {
    stopToken.stop_callback(cleanup);  // Register callback to cleanup on stop
    for (int i = 0; i < 10; ++i) {
        if (stopToken.stop_requested()) {
            std::cout << "Cancellation requested. Stopping task.\n";
            return;
        }
        std::cout << "Working on iteration: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    std::inplace_stop_source stopSource;
    std::jthread t(task, stopSource.get_token());

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    stopSource.request_stop();  // Request cancellation

    t.join();
    return 0;
}
```

### 4. **Concepts (C++26)**

#### 4.1. `stoppable_token` (C++26)
- **Description**: Specifies the basic interface of stop tokens that allow queries for stop requests and whether the stop request is possible.

```cpp
#include <stop_token>
#include <concepts>

void task(std::stoppable_token stopToken) {
    if (stopToken.stop_requested()) {
        // Handle cancellation logic
    }
    // Work logic
}
```

#### 4.2. `unstoppable_token` (C++26)
- **Description**: Specifies a stop token that does not allow stopping. For example, the `never_stop_token` is a type of `unstoppable_token`.

#### 4.3. `stoppable-source` (C++26)
- **Description**: Specifies that a type is a factory for associated stop tokens, and a stop request can be made upon it.

### Conclusion

This set of types and features provides flexible and modern ways to manage task cancellation in multi-threaded environments in C++. The various stop tokens, sources, and callback mechanisms give fine-grained control over task management, making cancellation predictable, safe, and cooperative. The example code above demonstrates these concepts in action, with comments explaining each part of the cancellation flow.