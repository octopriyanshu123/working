#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // For memset
#include <stdbool.h> // For bool
#include <unistd.h>  // For sbrk

// Define a simple block header to track memory allocation
typedef struct Block {
    size_t size;          // Size of the block (including header)
    struct Block *next;   // Pointer to the next block in the free list
    bool free;            // Whether this block is free or not
} Block;

#define BLOCK_SIZE sizeof(Block)

static Block *freeList = NULL;

Block* findFreeBlock(size_t size) {
    Block *current = freeList;
    while (current) {
        if (current->free && current->size >= size) {
            // Split the block if it's significantly larger than requested
            if (current->size > size + BLOCK_SIZE) {
                Block *newBlock = (Block*)((char*)current + BLOCK_SIZE + size);
                newBlock->size = current->size - size - BLOCK_SIZE;
                newBlock->free = true;
                newBlock->next = current->next;
                current->size = size;
                current->next = newBlock;
            }
            current->free = false; 
            return current;
        }
        current = current->next;
    }
    return NULL;  
}

void* my_malloc(size_t size) {
    if (size <= 0) return NULL;
    
    size = (size + BLOCK_SIZE - 1) & ~(BLOCK_SIZE - 1);  // Align to the block size
    Block *block = findFreeBlock(size);
    
    if (block) {
        return (void*) (block + 1);  // Return pointer after the Block header
    }

    // If no free block found, request more memory from the system
    block = (Block*)sbrk(size + BLOCK_SIZE);  // Cast void* to Block*
    if (block == (void*) -1) return NULL;  // sbrk failed
    
    block->size = size;
    block->free = false;
    block->next = freeList;
    freeList = block;

    return (void*) (block + 1);  // Return pointer after the Block header
}

// Custom calloc implementation (malloc + zero-initialize)
void* my_calloc(size_t count, size_t size) {
    size_t total_size = count * size;
    void *ptr = my_malloc(total_size);
    if (ptr) {
        memset(ptr, 0, total_size);
    }
    return ptr;
}

// Custom free implementation
void my_free(void *ptr) {
    if (!ptr) return;

    Block *block = (Block*) ptr - 1;  // Get the block header
    block->free = true;  // Mark the block as free

    // Coalesce adjacent free blocks
    Block *current = freeList;
    while (current) {
        if ((char*)current + BLOCK_SIZE + current->size == (char*)block) {
            // Merge with the next block
            current->size += BLOCK_SIZE + block->size;
            block = current;
        } else if ((char*)block + BLOCK_SIZE + block->size == (char*)current) {
            // Merge with the previous block
            block->size += BLOCK_SIZE + current->size;
            block->next = current->next;
        }
        current = current->next;
    }
}

// Example usage
int main() {
    int *arr = (int*)my_malloc(10 * sizeof(int));  // Cast my_malloc result to int*
    if (!arr) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Use the array
    for (int i = 0; i < 10; i++) {
        arr[i] = i;
        printf("%d ", arr[i]);
    }
    printf("\n");

    my_free(arr);

    // Test calloc
    int *zeros = (int*)my_calloc(10, sizeof(int));  // Cast my_calloc result to int*
    if (!zeros) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        printf("%d ", zeros[i]);  // Should print all zeros
    }
    printf("\n");

    my_free(zeros);
    return 0;
}
