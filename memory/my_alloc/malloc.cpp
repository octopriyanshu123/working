#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <vector>

#define HEAP_CAPACITY 64
#define ALIGN_SIZE 8

static void *current_brk_pointer = nullptr;
size_t heap_size = 0;
char heap[HEAP_CAPACITY] = {45};

void print_current_address() {
    std::cout << "Current break address: " << sbrk(0) << std::endl;
}

struct chunk {
    void* adress_pointer;
    int size;
};



std::vector<chunk> chunks;


void display_memory(){
    std::cout << "Memory Visualization:" << std::endl;

    // Print the heap as a visual map
    char memory_map[HEAP_CAPACITY] = { '.' }; // '.' for free memory
    for (auto& x : chunks) {
        int start = (char*)x.adress_pointer - heap;  // Calculate the offset from the start of the heap
        int end = start + x.size;

        // Mark the memory region as used
        for (int i = start; i < end; i++) {
            memory_map[i] = 'X';  // Mark used space with 'X'
        }
    }

    // Print the memory map
    for (int i = 0; i < HEAP_CAPACITY; i++) {
        std::cout << memory_map[i];
    }
    std::cout << std::endl;

    // Also display the chunks with start address and size for clarity
    for (auto& x : chunks) {
        std::cout << "Chunk at address " << x.adress_pointer << " with size " << x.size << std::endl;
    }
}

void *my_malloc(size_t size) {
    size_t aligned_size = (size + ALIGN_SIZE - 1) & ~(ALIGN_SIZE - 1);

    // First time allocating memory
    if (current_brk_pointer == nullptr) {
        std::cout << "First allocation" << std::endl;
        current_brk_pointer = sbrk(0);
    } else {
        std::cout << "Other allocation" << std::endl;
    }

    void *allocated_memory = current_brk_pointer;

    // Increase the program break by the required amount
    if (sbrk(aligned_size) == (void *)-1) {
        // sbrk failed, return NULL
        std::cout << "Memory allocation failed" << std::endl;
        return NULL;
    }

    // Move the current break forward
    current_brk_pointer = (char *)current_brk_pointer + aligned_size;

    chunk  new_chunk;
    new_chunk.size = size;
    new_chunk.adress_pointer = allocated_memory;

    chunks.push_back(new_chunk);
    return allocated_memory;
}

int main(int argc, char **argv) {
    size_t alloc_size = sizeof(int) * 1;  // Allocating space for 10 integers

    // First allocation
    void *ptr = my_malloc(alloc_size);
    if (ptr != NULL) {
        std::cout << "Memory allocated at address: " << ptr << std::endl;
    } else {
        std::cout << "Memory allocation failed" << std::endl;
    }
    display_memory();
    // Second allocation
    void *sptr = my_malloc(alloc_size);
    if (sptr != NULL) {
        std::cout << "Memory allocated at address: " << sptr << std::endl;
    } else {
        std::cout << "Memory allocation failed" << std::endl;
    }

    display_memory();

    return 0;
}
