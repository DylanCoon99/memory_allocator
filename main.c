#include<stdio.h>
#include "allocator.h"

/*
Review of how a memory allocator works

Memory allocator manages the heap as a free list. Upon calling malloc, the allocator finds an appropriate amount of memory
to give to allocate and returns a pointer to the memory. When memory is freed, the memory is unallocated and marked free.


Start out with a free list allocator without coalescing.



Goals for today:

	(1) Implement Free List: This is a just a linked list of blocks of free memory


	


*/









int main() {

	printf("Testing my_malloc function!\n");

	int *buffer;


	buffer = my_malloc(100);


	printf("Calling malloc again. Free list should already by initialized\n");

	buffer = my_malloc(200);

	printf("Here is my buffer: %d\n", buffer[0]);

	my_free(buffer);

	return 0;
}

