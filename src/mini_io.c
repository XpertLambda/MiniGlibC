#include "mini_lib.h"

MYFILE *open_files_list = NULL;

MYFILE* mini_fopen(char* file, char mode) {
    MYFILE *myfile = mini_calloc(sizeof(MYFILE), 1);
    if (!myfile) return NULL;

    int flags = 0;
    switch(mode) {
        case 'r':
            flags = O_RDONLY;
            break;
        case 'w':
            flags = O_WRONLY | O_CREAT | O_TRUNC;
            break;
        case 'b':
            flags = O_RDWR | O_CREAT;
            break;
        case 'a':
            flags = O_WRONLY | O_CREAT | O_APPEND;
            break;
        default:
            mini_free(myfile);
            return NULL;
    }
    
    myfile->fd = open(file, flags, 0644);
    if (myfile->fd == -1) {
        mini_free(myfile);
        return NULL;
    }

    myfile->buffer_read = (mode == 'r' || mode == 'b') ? mini_calloc(IOBUFFER_SIZE, 1) : NULL;
    myfile->buffer_write = (mode == 'w' || mode == 'b' || mode == 'a') ? mini_calloc(IOBUFFER_SIZE, 1) : NULL;
    myfile->ind_read = (myfile->buffer_read) ? 0 : NOT_INIT;
    myfile->ind_write = (myfile->buffer_write) ? 0 : NOT_INIT;

    add_to_open_file_list(myfile);
    return myfile;
}

int mini_fread(void* buffer, int size_element, int number_element, MYFILE* file) {
    if (file == NULL || buffer == NULL) {
        return NOT_INIT;
    }

    int total_bytes = size_element * number_element;
    int bytes_read = read(file->fd, buffer, total_bytes);

    if (bytes_read == -1) {
        mini_perror("Error reading file");
        return -1;
    }
    return bytes_read / size_element;
}

int mini_fwrite(void* buffer, int size_element, int number_element, MYFILE* file) {
    if (file == NULL || buffer == NULL) {
        return NOT_INIT;
    }

    int total_bytes = size_element * number_element;
    int bytes_written = write(file->fd, buffer, total_bytes);

    if (bytes_written == -1) {
        mini_perror("Error writing to file");
        return -1;
    }

    return bytes_written / size_element;
}

int mini_fflush(MYFILE* file) {
    if (file == NULL) {
        return NOT_INIT;
    }

    if (file->buffer_write == NULL || file->ind_write == 0) {
        return 0;
    }

    int bytes_written = write(file->fd, file->buffer_write, file->ind_write);
    if (bytes_written == -1) {
        mini_perror("Error flushing file");
        return -1;
    }

    file->ind_write = 0;
    return 0;
}

void add_to_open_file_list(MYFILE *file) {
    file->next = open_files_list;
    open_files_list = file;
}

void remove_from_open_file_list(MYFILE *file) {
    MYFILE **ptr = &open_files_list;
    while (*ptr != NULL) {
        if (*ptr == file) {
            *ptr = file->next;
            return;
        }
        ptr = &(*ptr)->next;
    }
}

int mini_fclose(MYFILE* file) {
    if (file == NULL) {
        return -1;
    }

    mini_fflush(file);
    remove_from_open_file_list(file);
    int close_result = close(file->fd);
    if (close_result == -1) {
        return -1;
    }

    if (file->buffer_read) mini_free(file->buffer_read);
    if (file->buffer_write) mini_free(file->buffer_write);
    mini_free(file);
    return 0;
}

int mini_fgetc(MYFILE* file) {
    if (file == NULL || file->buffer_read == NULL) {
        return -1;
    }

    if (file->ind_read == IOBUFFER_SIZE || file->ind_read == 0) {
        int bytes_read = read(file->fd, file->buffer_read, IOBUFFER_SIZE);
        if (bytes_read <= 0) {
            return -1;
        }
        file->ind_read = 0;
    }

    char c = ((char*)file->buffer_read)[file->ind_read++];
    return (int)c;
}

int mini_fputc(MYFILE* file, char c) {
    if (file == NULL || file->buffer_write == NULL) {
        return -1;
    }

    if (file->ind_write == IOBUFFER_SIZE) {
        if (mini_fflush(file) == -1) {
            return -1;
        }
    }

    ((char*)file->buffer_write)[file->ind_write++] = c;
    return (int)c;
}
