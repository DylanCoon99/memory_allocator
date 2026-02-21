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



void print_buffer(int *buffer, int size) {

	printf("Printing buffer: %p\n", buffer);
	for (int i = 0; i < size; i++) {
		printf("%d\n", buffer[i]);
	}

}





int main() {

	printf("Testing my_malloc function!\n");

	int *buffer;


	buffer = my_malloc(100);

	for (int i = 0; i < 100; i++) {
		buffer[i] = i*i;
	}

	//print_buffer(buffer, 100);

	my_free(buffer);


	printf("Calling malloc again. Free list should already by initialized\n");

	buffer = my_malloc(200);

	for (int i = 0; i < 200; i++) {
		buffer[i] = i*i;
	}

	//printf("Here is my buffer[0]: %d\n", buffer[0]);

	//print_buffer(buffer, 200);

	my_free(buffer);

	return 0;
}

