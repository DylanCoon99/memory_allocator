#include<stdio.h>
#include <sys/mman.h>
#include"allocator.h"

#include <stdlib.h>


// Implementation of malloc function using free list allocation


static block_t *free_list = NULL;


void print_free_list() {
	block_t *current = free_list;
	int i = 0;

	printf("=== Free List ===\n");
	if (current == NULL) {
		printf("(empty)\n");
		printf("=================\n");
		return;
	}

	while (current != NULL) {
		printf("[%d] addr: %p, size: %zu, next: %p\n", i, (void *)current, current->size, (void *)current->next);
		current = current->next;
		i++;
	}
	printf("=================\n");
}


block_t *find_free_block(size_t size) {
	// iterates over the free list and finds the first fit
	printf("Found a free block of size: %lu\n", size);
	block_t *free_block = NULL;

	/*
	Need to find a free block

	Algorithm: Find first fit for a block -> split it into two blocks -> maintain free list



	When a block is requested, we find first fit of free block by
	iterating over the free list. When we find it, we take only the
	memory we need, break the free block in two and add the new free
	block to the free list.
	*/

	// iterate over free list and find the first fit

	block_t *prev = NULL;
	block_t *current = free_list;

	// need to have a way of making sure the head of the free list is updated


	while (current != NULL) {
		if (current->size > size) {
			// if current block is adequate size -> split this block

			// update new block
			block_t *new_block = current + 1 + size; // add the header and size of newly allocated block
			new_block->size = current->size - size ;
 
			// update the current block size
			current->size = size;
			free_block = current;

			if (prev == NULL) {
				free_list = new_block;	
			} else {
				prev->next = new_block;
			}

			// update free list size
			free_list->size = free_list->size - size;

			break;
		} else if (current->size == size) {
			// insert new block in free list

			prev->next = current->next;
			free_block = current;

			if (prev == NULL) {
				free_list = current->next;
			} else {
				prev->next = current->next;
			}

			free_list->size = free_list->size - size;
			break;

		}
		prev = current;
		current = current->next;

	}

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

    // define the size of the free list by subtracting size of header
    free_list->size = SIZE - sizeof(block_t);
    free_list->next = NULL;

	return EXIT_SUCCESS;
}


void *my_malloc(size_t size){
	// on first my_malloc call, the free list will be NULL -> need to request memory from the OS (sbrk() of mmap())
	if (free_list == NULL) {
		int ret;

		ret = init_free_list();
		if (ret == 1) {
			// Error
			perror("Error while initializing free list.\n");
			return NULL;
		}
		printf("Initialized free list.\n");
		print_free_list();
	}

	printf("Looking for a free block of size: %lu\n", size);

	// find free block
	block_t *block = find_free_block(size);
	print_free_list();
	return (void *)(block + 1);	
}


void my_free(void *ptr) {
	// Step BACK to get the header
	block_t *block = (block_t *)ptr - 1;
	block_t *prev = NULL;
	block_t *current = free_list;

	// Add to the free list
	// from the header -> get the size -> free the block
	while (current->next != NULL && current < block) {
		prev = current;
		current = current->next;
	}

	// insert into free list sorted address order
	if (prev == NULL) {

		// TO BE IMPLEMENTED

		block->next = free_list;
		free_list = block;

		// need to sort this out

	} else {
		prev->next = block;
	}
	printf("Freed block: %p\n", block);
	print_free_list();


	// implement coalescing here; blocks should be coalesced if they are adjacent

}
