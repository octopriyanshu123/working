// #include <iostream>

// int main() {
//     #if defined(__arm__) || defined(__ARM__) || defined(__aarch32__) // 32-bit ARM
//         std::cout << "32-bit ARM architecture\n";
//     #elif defined(__aarch64__) // 64-bit ARM
//         std::cout << "64-bit ARM architecture\n";
//     #elif defined(__x86_64__) || defined(_M_X64) // AMD64 or x86-64
//         std::cout << "64-bit AMD64/x86-64 architecture\n";
//     #elif defined(__i386__) || defined(_M_IX86) // 32-bit x86
//         std::cout << "32-bit x86 architecture\n";
//     #else
//         std::cout << "Unknown architecture\n";
//     #endif

//     return 0;
// }

#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
    #include <Windows.h>
    #include <sysinfoapi.h>
    #include <memoryapi.h>
#elif defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    #include <sys/utsname.h>
    #include <unistd.h>
    #include <sys/sysctl.h>  // Add this include for sysctl
    #include <sys/types.h>
#endif

void printSystemInfo() {
    // Print OS details
    #if defined(_WIN32) || defined(_WIN64)
        SYSTEM_INFO sysInfo;
        GetSystemInfo(&sysInfo);

        // Processor Architecture
        switch (sysInfo.wProcessorArchitecture) {
            case PROCESSOR_ARCHITECTURE_AMD64:
                std::cout << "Processor Architecture: x64 (AMD or Intel)\n";
                break;
            case PROCESSOR_ARCHITECTURE_ARM:
                std::cout << "Processor Architecture: ARM\n";
                break;
            case PROCESSOR_ARCHITECTURE_ARM64:
                std::cout << "Processor Architecture: ARM64\n";
                break;
            case PROCESSOR_ARCHITECTURE_INTEL:
                std::cout << "Processor Architecture: x86 (Intel)\n";
                break;
            default:
                std::cout << "Processor Architecture: Unknown\n";
                break;
        }

        // Number of logical processors
        std::cout << "Number of logical processors: " << sysInfo.dwNumberOfProcessors << "\n";

        // OS version
        OSVERSIONINFO osInfo;
        osInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
        if (GetVersionEx(&osInfo)) {
            std::cout << "OS Version: " << osInfo.dwMajorVersion << "." << osInfo.dwMinorVersion << "\n";
        }

        // Memory info
        MEMORYSTATUSEX memInfo;
        memInfo.dwLength = sizeof(MEMORYSTATUSEX);
        GlobalMemoryStatusEx(&memInfo);
        std::cout << "Total physical memory: " << memInfo.ullTotalPhys / (1024 * 1024) << " MB\n";
        std::cout << "Available physical memory: " << memInfo.ullAvailPhys / (1024 * 1024) << " MB\n";

    #elif defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        struct utsname sysInfo;
        if (uname(&sysInfo) == 0) {
            std::cout << "System Name: " << sysInfo.sysname << "\n";
            std::cout << "Node Name: " << sysInfo.nodename << "\n";
            std::cout << "Release: " << sysInfo.release << "\n";
            std::cout << "Version: " << sysInfo.version << "\n";
            std::cout << "Machine: " << sysInfo.machine << "\n";
        }

        // Get CPU details
        int numCpus;
        size_t size = sizeof(numCpus);
        // Make sure sysctlbyname is properly declared for UNIX-like systems
        // if (sysctlbyname("hw.ncpu", &numCpus, &size, NULL, 0) == -1) {
        //     std::cerr << "Failed to get CPU info\n";
        // } else {
        //     std::cout << "Number of CPUs: " << numCpus << "\n";
        // }

        // Check CPU architecture
        std::cout << "CPU Architecture: ";
        #ifdef __aarch64__
            std::cout << "ARM64\n";
        #elif defined(__arm__)
            std::cout << "ARM32\n";
        #elif defined(__x86_64__)
            std::cout << "x86_64\n";
        #elif defined(__i386__)
            std::cout << "x86\n";
        #else
            std::cout << "Unknown\n";
        #endif

        // Memory information
        long long totalMem = sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGE_SIZE);
        long long availableMem = sysconf(_SC_AVPHYS_PAGES) * sysconf(_SC_PAGE_SIZE);
        std::cout << "Total physical memory: " << totalMem / (1024 * 1024) << " MB\n";
        std::cout << "Available physical memory: " << availableMem / (1024 * 1024) << " MB\n";

    #else
        std::cout << "Unsupported Operating System\n";
    #endif
}

int main() {
    printSystemInfo();
    return 0;
}
