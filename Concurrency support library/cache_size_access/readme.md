In C++17, the language introduced a way to query the **cache size** of a processor, specifically through the use of the **`std::hardware_destructive_interference_size`** and **`std::hardware_constructive_interference_size`** constants. These constants, part of the `<new>` header, provide insights into cache line sizes and help optimize memory accesses.

However, it's important to note that the actual **cache size access** feature in C++17, in terms of directly querying the size of the cache (like L1, L2, or L3 caches), is **not natively provided by C++17**. Instead, C++17 provides a few constants that can help optimize memory usage with respect to the processor's cache architecture.

### Key Concepts Introduced in C++17 Related to Cache

#### 1. **Cache Line Size and Interference Sizes**

**`std::hardware_destructive_interference_size`** and **`std::hardware_constructive_interference_size`** are constants that provide information related to cache line sizes and memory access interference. 

- **`std::hardware_destructive_interference_size`**: This constant gives the size of a cache line, in bytes, that should be avoided when writing data that could be accessed concurrently by different processors or threads. The idea here is that accesses to adjacent memory locations within this size could interfere with each other, which can reduce performance.
  
- **`std::hardware_constructive_interference_size`**: This constant provides the size of a cache line that can be safely accessed by multiple threads without introducing too much destructive interference (i.e., performance degradation due to cache contention).

These constants are designed to optimize the performance of multithreaded applications, allowing developers to align data structures properly and avoid excessive contention between threads that might access the same cache line.

Here is an example of how these constants might be used:

```cpp
#include <iostream>
#include <new> // For hardware cache-related constants

int main() {
    // Get the size of the destructive interference size (cache line size)
    std::cout << "Cache line size (destructive interference): "
              << std::hardware_destructive_interference_size << " bytes" << std::endl;

    // Get the size of the constructive interference size
    std::cout << "Cache line size (constructive interference): "
              << std::hardware_constructive_interference_size << " bytes" << std::endl;

    return 0;
}
```

### How Cache Size Access Relates to C++17:

While C++17 introduces these constants, the **direct access to the actual cache sizes (L1, L2, L3 cache)**, like how much memory is allocated to each level of cache, is **not part of the C++ standard**. Accessing this kind of detailed hardware-specific information typically requires:

- **Platform-specific libraries** or **APIs**. For example, on Linux, you might use `sysctl` or `procfs` to gather cache information, or on Windows, the Windows Management Instrumentation (WMI) API might be used to query the CPU's cache levels.
- **Third-party libraries** like [hwloc](https://www.open-mpi.org/projects/hwloc/) (Hardware Locality) that provide portable mechanisms to gather detailed information about the system’s hardware topology, including cache sizes and other hardware details.

### Example (Linux):

On Linux, for example, you could access cache information by reading from `/sys/devices/system/cpu/cpu0/cache` directories. Here’s a shell command example for obtaining cache details:

```bash
cat /sys/devices/system/cpu/cpu0/cache/index0/size  # L1 cache size
cat /sys/devices/system/cpu/cpu0/cache/index1/size  # L2 cache size
cat /sys/devices/system/cpu/cpu0/cache/index2/size  # L3 cache size
```

### Example (Windows):

On Windows, you might use the WMI API to query CPU information and cache sizes. Here's a basic example using PowerShell:

```powershell
Get-WmiObject Win32_Processor | Select-Object Name, L2CacheSize, L3CacheSize
```

### Summary

In C++17, while you can use the constants `std::hardware_destructive_interference_size` and `std::hardware_constructive_interference_size` to optimize memory access and avoid cache line conflicts, **directly querying cache sizes** (such as L1, L2, and L3) is not natively provided in the C++17 standard. For more detailed cache-related information, you would typically rely on platform-specific methods or third-party libraries. The introduction of these constants, however, does allow for some level of optimization of memory usage and cache efficiency in multithreaded applications.