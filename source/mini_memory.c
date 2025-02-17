#include "mini_lib.h"

malloc_element *malloc_list = NULL;  // Initialize the global malloc list

void* mini_calloc(int size_element, int number_element){
	size_t total_size = size_element * number_element;  // Calculate total memory size
	malloc_element *current = malloc_list;
	void* ptr = NULL;
	unsigned char *buffer = NULL;
	
	// Check if there is a free memory block large enough to reuse
	while(current != NULL) {
        if(current->total_size >= total_size && current->status == FREE) {  
            current->status = USED;  // Mark block as used
            buffer = current->zone;
            // Initialize the memory block to zero
            for(size_t i = 0; i < current->total_size; i++) buffer[i] = '\0';
            return current->zone;
        }
        current = current->next_malloc;
    }

	// No suitable block found, allocate new memory using sbrk
	ptr = sbrk(total_size);  
	if(ptr == (void*) -1) return NULL;  // Return NULL if sbrk fails

	buffer = (unsigned char*)ptr;
	// Initialize the newly allocated memory to zero
    for(size_t i = 0; i < total_size; i++) buffer[i] = '\0';
    
    // Allocate memory for the new malloc_element structure
    malloc_element *new_elt = sbrk(sizeof(malloc_element));
	if(new_elt == (void*) -1) return NULL;  // Return NULL if sbrk fails
 
    new_elt->zone = ptr;  // Store the pointer to the allocated memory
	new_elt->total_size = total_size;  // Store the size of the allocated block
	new_elt->status = USED;  // Mark the new block as used

	// Add the new memory block to the malloc list
	if(malloc_list == NULL) {
		new_elt->next_malloc = NULL;  // First block in the list
		malloc_list = new_elt;  // Set the new block as the head of the list
	} else {
   		new_elt->next_malloc = malloc_list;  // Add the block to the beginning of the list
    	malloc_list = new_elt;
    }
	
	return ptr;  // Return the pointer to the allocated memory
}

void mini_free(void* ptr){
	malloc_element *current = malloc_list;
    while(current != NULL) {
        if(current->zone == ptr) {  // If the memory block matches the one to free
            if(current->status == USED) {  
                current->status = FREE;  // Mark the block as free
                return;
            }
        }
        current = current->next_malloc;
    }
}

void mini_exit(int status) {
    MYFILE *current = open_files_list;
    // Flush all open files before exiting
    while (current != NULL) {
        mini_fflush(current);  // Flush the file buffers
        current = current->next;
    }

    _exit(status);  // Terminate the process immediately
}
