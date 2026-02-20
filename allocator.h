// header file containing structs
#ifndef ALLOCATOR_H // prevents the header from being included more than once in the compilation process
#define ALLOCATOR_H // another file might import this and it could be made redundant or cause problems w/o this
					
#include<stdio.h>
#include <stddef.h>



void *my_malloc(size_t size);
void my_free(void *ptr);


/*
Block Design

Minimum block size must hold:
- Size field (4-8 bytes)
- Next pointer for the free list (8 bytes on 64-bit)


*/



// the ptr to the free block is implicitly right after the header of the block -> so it's the (ptr to the block + size of header)
typedef struct block {
	size_t size;
	struct block *next;  // only used when free
} block_t;



struct free_list {
	block_t *head;	
};





#endif