C++ includes built-in support for threads, atomic operations, mutual exclusion, condition variables, and futures.

Threads allow programs to execute multiple tasks concurrently, which can be especially beneficial when running on multi-core processors. A processor core can execute only one thread at a time, but by having multiple threads in a program, the system can take advantage of all the cores available to improve overall performance.

Here's how it works:

1. **Single-core Processors**: On a single-core processor, only one task can be executed at a time. If a program is multi-threaded, the operating system rapidly switches between the threads to give the illusion of parallelism, but in reality, the processor is handling one thread at a time.

2. **Multi-core Processors**: On a multi-core processor, each core can handle a separate thread simultaneously. So, if a program has multiple threads, each one can run on a different core, allowing the program to execute more tasks at once. This is real parallelism and can lead to significant performance improvements.

3. **Parallel Execution**: By using threads, a program can break down its tasks into smaller, independent chunks. These chunks can then be executed simultaneously (or in parallel) across multiple cores, reducing the overall time to complete the program's execution.

4. **Efficiency**: Threads allow programs to utilize the full processing power of a multi-core system. For example, a program designed to process data, render graphics, or handle multiple network requests simultaneously can perform those tasks more efficiently by distributing them across multiple cores.

In summary, threads enable a program to split its work into smaller, parallel tasks, and these tasks can run simultaneously across multiple cores, making the program run faster and more efficiently on modern multi-core processors.







Question in my Mind

1. How the lock can block the code thread , process the line of execution 


2. Use of Move Constructor
3. Lambdas 
4. Condition Variable
5. Cooperative cancellation
6. [What is a semaphore? How do they work? (Example in C)](https://youtu.be/ukM_zzrIeXs?si=JDEP_WZ4tWF_pzIA)

7. [Making variables atomic in C](https://youtu.be/_xX25ThomIo?si=N5jc5X1fwTkxfaNW)

8. std::memory_order

9. [int foo(void) vs int foo()](https://youtu.be/VsRs0H4hXEE?si=dnpn-LLHM98RDVEx)
10. [ravalue vs lvalue](https://youtu.be/fbYknr-HPYE?si=PbzAQQBtWOOJbtN2)
11. Socket DDS Data Distibution Server















