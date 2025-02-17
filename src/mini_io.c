#include "mini_lib.h"

MYFILE *open_files_list = NULL;  // Initialize the list of open files as empty

MYFILE* mini_fopen(char* file, char mode) {
    MYFILE *myfile = mini_calloc(sizeof(MYFILE),1);  // Allocate memory for the MYFILE structure
    if (!myfile) return NULL;  // Return NULL if memory allocation fails

    int flags = 0;  // Flags to pass to the open() system call
    switch(mode) {
        case 'r':
            flags = O_RDONLY;  // Open file in read-only mode
            break;
        case 'w':
            flags = O_WRONLY | O_CREAT | O_TRUNC;  // Write-only, create if necessary, truncate if exists
            break;
        case 'b':
            flags = O_RDWR | O_CREAT;  // Read and write, create if necessary
            break;
        case 'a':
            flags = O_WRONLY | O_CREAT | O_APPEND;  // Write-only, create if necessary, append to file
            break;
        default:
            free(myfile);  // Free allocated memory if invalid mode
            return NULL;
    }
    
    // Open the file with the determined flags and common permission mask 0644
    myfile->fd = open(file, flags, 0644);  
    if (myfile->fd == -1) {  // If opening the file failed
        free(myfile);  // Free memory and return NULL
        return NULL;
    }

    // Allocate read buffer if mode is 'r' or 'b' (read-related modes)
    myfile->buffer_read = (mode == 'r' || mode == 'b') ? malloc(IOBUFFER_SIZE) : NULL;
    // Allocate write buffer if mode is 'w', 'b', or 'a' (write-related modes)
    myfile->buffer_write = (mode == 'w' || mode == 'b' || mode == 'a') ? malloc(IOBUFFER_SIZE) : NULL;
    // Initialize buffer indices (NOT_INIT if not used)
    myfile->ind_read = (myfile->buffer_read) ? 0 : NOT_INIT;
    myfile->ind_write = (myfile->buffer_write) ? 0 : NOT_INIT;

    return myfile;  // Return the file structure
}

int mini_fread(void* buffer, int size_element, int number_element, MYFILE* file) {
    if (file == NULL || buffer == NULL) {
        return NOT_INIT;  // Return NOT_INIT if file or buffer is invalid
    }

    int total_bytes = size_element * number_element;  // Calculate total bytes to read
    int bytes_read = read(file->fd, buffer, total_bytes);  // Read from the file descriptor

    if (bytes_read == -1) {  // If reading failed
        mini_perror("Error reading file");  // Print an error message
        return -1;
    }
    return bytes_read / size_element;  // Return number of elements read
}

int mini_fwrite(void* buffer, int size_element, int number_element, MYFILE* file) {
    if (file == NULL || buffer == NULL) {
        return NOT_INIT;  // Return NOT_INIT if file or buffer is invalid
    }

    int total_bytes = size_element * number_element;  // Calculate total bytes to write
    int bytes_written = write(file->fd, buffer, total_bytes);  // Write to the file descriptor

    if (bytes_written == -1) {  // If writing failed
        mini_perror("Error writing to file");  // Print an error message
        return -1;
    }

    return bytes_written / size_element;  // Return number of elements written
}

int mini_fflush(MYFILE* file) {
    if (file == NULL) {
        return NOT_INIT;  // Return NOT_INIT if file is invalid
    }

    // If there's no write buffer or nothing to flush, return 0
    if (file->buffer_write == NULL || file->ind_write == 0) {
        return 0;
    }

    int bytes_written = write(file->fd, file->buffer_write, file->ind_write);  // Flush write buffer to file
    if (bytes_written == -1) {  // If flushing failed
        mini_perror("Error flushing file");  // Print an error message
        return -1;
    }

    file->ind_write = 0;  // Reset write index after flushing

    return 0;  // Success
}

void add_to_open_file_list(MYFILE *file) {
    file->next = open_files_list;  // Add the new file to the front of the list
    open_files_list = file;  // Update the head of the list
}

void remove_from_open_file_list(MYFILE *file) {
    MYFILE **ptr = &open_files_list;
    while (*ptr != NULL) {
        if (*ptr == file) {  // Found the file to remove
            *ptr = file->next;  // Remove it from the list by updating the pointer
            return;
        }
        ptr = &(*ptr)->next;  // Move to the next file in the list
    }
}

int mini_fclose(MYFILE* file) {
    if (file == NULL) {
        return -1;  // Return -1 if file is invalid
    }

    mini_fflush(file);  // Flush any remaining data in the write buffer
    remove_from_open_file_list(file);  // Remove the file from the open file list
    int close_result = close(file->fd);  // Close the file descriptor
    if (close_result == -1) {  // If closing failed
        return -1;
    }

    mini_free(file);  // Free the allocated memory for the MYFILE structure
    return 0;  // Success
}

int mini_fgetc(MYFILE* file) {
    if (file == NULL || file->buffer_read == NULL) {
        return -1;  // Return -1 if file or read buffer is invalid
    }

    // If read index reached buffer size or is uninitialized, refill the buffer
    if (file->ind_read == IOBUFFER_SIZE || file->ind_read == 0) {
        int bytes_read = read(file->fd, file->buffer_read, IOBUFFER_SIZE);  // Read into buffer
        if (bytes_read <= 0) {  // If reading failed or end of file
            return -1;
        }
        file->ind_read = 0;  // Reset index after reading
    }

    char c = ((char*)file->buffer_read)[file->ind_read++];  // Get the next character from the buffer
    return (int)c;  // Return the character as an integer
}

int mini_fputc(MYFILE* file, char c) {
    if (file == NULL || file->buffer_write == NULL) {
        return -1;  // Return -1 if file or write buffer is invalid
    }

    // If write buffer is full, flush it before writing more data
    if (file->ind_write == IOBUFFER_SIZE) {
        if (mini_fflush(file) == -1) {  // If flushing failed
            return -1;
        }
    }

    ((char*)file->buffer_write)[file->ind_write++] = c;  // Write the character to the buffer
    return (int)c;  // Return the character as an integer
}
