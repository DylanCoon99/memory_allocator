#include<stdio.h>
#include <sys/mman.h>
#include"allocator.h"

#include <stdlib.h>


// Implementation of malloc function


static block_t *free_list = NULL;


block_t *find_free_block(size_t size) {
	// iterates over the free list and finds the first fit
	printf("Found a free block of size: %lu\n", size);

	block_t *free_block = NULL;

	/*
	Need to find a free block

	*/




	return free_block;
}



int init_free_list(){

    // Call mmap to request memory from the kernel.
    free_list = mmap(
        NULL,           // addr: Let the system choose the address.
        SIZE,           // len: The length of the mapping in bytes.
        PROT_READ | PROT_WRITE, // prot: Memory protection (read and write access).
        MAP_PRIVATE | MAP_ANONYMOUS, // flags: Private to the process, not file-backed.
        -1,             // fd: File descriptor (ignored for anonymous mapping, must be -1).
        0               // offset: Offset into file (ignored for anonymous mapping, must be 0).
    );

    // Check for errors.
    if (free_list == MAP_FAILED) {
        perror("mmap failed\n");
        return EXIT_FAILURE;
    }

    printf("Memory allocated at address: %p\n", free_list);

    free_list->size = SIZE - sizeof(block_t);
    free_list->next = NULL;

	return EXIT_SUCCESS;
}


void *my_malloc(size_t size){
	// on first my_malloc call, the free list will be NULL -> need to request memory from the OS (sbrk() of mmap())
	if (free_list == NULL) {
		// Request memory from the OS using mmap
		// 1. Declare a pointer to hold the address of the allocated memory.
		int ret;

		ret = init_free_list();
		if (ret == 1) {
			// Error
			perror("Error while initializing free list.\n");
			return NULL;
		}
		printf("Initialized free list.\n");
	}

	printf("Looking for a free block of size: %lu\n", size);

	// find free block
	block_t *block = find_free_block(size);
	return (void *)(block + 1);	
}

/*
void my_free(void *ptr) {
  // Step BACK to get the header
  block_t *block = (block_t *)ptr - 1;

  // Add to the free list
  // from the header -> get the size -> free the block
}
*/