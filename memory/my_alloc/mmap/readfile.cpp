#include <assert.h>
#include <stdio.h>
#include <fcntl.h>      // For open()
#include <sys/mman.h>   // For mmap()
#include <sys/stat.h>   // For fstat() and struct stat
#include <unistd.h>     // For read(), write(), close()

int main(int argc, char** argv) {
    assert(argc >= 2);

    const char *filepath = argv[1];
    
    // Open the file in read-write mode
    int fd = open(filepath, O_RDWR);
    assert(fd >= 0);  // Ensure the file was opened successfully
    
    // Get file status
    struct stat statbuf;
    int err = fstat(fd, &statbuf);
    assert(err >= 0);  // Ensure the file status was fetched successfully

    // Map the file into memory with read-write access
    void *ptr = mmap(NULL, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    assert(ptr != MAP_FAILED);  // Ensure memory mapping succeeded

    // Modify the contents of the file (example: change the first byte)
    ((char*)ptr)[2] = 'X';  // Modify the first byte to 'X'

    // Optionally print the modified contents (for debugging)
    for (size_t i = 0; i < statbuf.st_size && i < 10; i++) {
        printf("%c", ((char*)ptr)[i]);  // Print the first 10 bytes of the file
    }
    printf("\n");

    // Write the entire memory-mapped region back to the file
    ssize_t n = write(1, ptr, statbuf.st_size);  // Write to stdout
    assert(n == statbuf.st_size);  // Ensure all data is written

    // Clean up
    munmap(ptr, statbuf.st_size);  // Unmap the memory
    close(fd);  // Close the file descriptor

    return 0;
}
