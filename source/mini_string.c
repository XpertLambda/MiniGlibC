#include "mini_lib.h"

char buffer[BUF_SIZE]; // Buffer to hold data for mini_printf...
int ind = NOT_INIT;    // Index to track the buffer's current position, initially set to NOT_INIT

void real_mini_printf(char* args[]) {
    // Initialize the buffer and index if this is the first call to mini_printf
    if (ind == NOT_INIT) {
        ind = 0;
        buffer[0] = '\0';  // Initialize the buffer with an empty string
    }

    for(int i = 0; args[i]!=NULL; i++) {
        // Iterate through the input string
        for (int j = 0; args[i][j] != '\0'; j++) {
            // If the buffer is full or a newline is found, flush the buffer
            if (ind == BUF_SIZE - 1 || args[i][j] == '\n') {
                write(1, buffer, ind); // Write the buffer content to stdout
                write(1, "\n", 1); // Add the newline
                ind = 0; // Reset buffer index
                buffer[ind] = '\0'; // Reset the buffer
            }

            // If the character isn't a newline, add it to the buffer
            if (args[i][j] != '\n') 
                buffer[ind++] = args[i][j];
        }

    }

    // Ensure any leftover data is written if there's no trailing newline
    if (ind > 0) {
        buffer[ind] = '\0'; // Null-terminate the remaining data in the buffer
        write(1, buffer, ind); // Flush the remaining buffer content
        //write(1, "\n", 1); // Add newline
        ind = 0; // Reset index
    }
}

int mini_scanf(char* buffer, int size_buffer){
    int bytesRead = 0;  // Number of bytes read in one iteration
    int totalRead = 0;  // Total number of bytes read

    // If the buffer is NULL or size_buffer is invalid, return 0
    if(buffer == NULL || size_buffer <= 0) {
        return 0;
    }

    // Loop to read input one character at a time
    while(totalRead < size_buffer - 1){ 
        bytesRead = read(0, buffer + totalRead, 1); // Read 1 byte from stdin
        if (bytesRead <= 0 || buffer[totalRead] == '\n') { // Stop if end of input or newline is reached
            break;
        }
        totalRead += bytesRead; // Increment total bytes read
    }

    buffer[totalRead] = '\0'; // Null-terminate the string
    return totalRead; // Return the number of characters read
}

int mini_strlen(char* s){
    size_t i = 0;
    // Iterate through the string until null character is encountered
    for(i = 0 ; s[i] != '\0'; i++);
    return i; // Return the length
}

int mini_strnlen(char* s, size_t max_len){
    size_t i = 0;
    // Iterate through the string until null character is encountered
    for(i = 0 ; s[i] != '\0' && i < max_len; i++);
    return i; // Return the length
}

int mini_strcpy(char* s, char* d) {
    int i = 0;
    while (s[i] != '\0') {
        d[i] = s[i];
        i++;
    }
    d[i] = '\0'; // Null-terminate the destination string
    return i;
}

int mini_strncpy(char* s, char* d, size_t dest_size) {
    int i = 0;
    while (i < dest_size && s[i] != '\0') {
        d[i] = s[i];
        i++;
    }
    d[i] = '\0'; // Null-terminate the destination string
    return i;
}

int mini_strcmp(char* s1, char* s2) {
    size_t i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) {
            return s1[i] - s2[i];
        }
        i++;
    }
    return s1[i] - s2[i];
}

int mini_strncmp(char* s1, char* s2, size_t max_len) {
    size_t i = 0;
    while (i < max_len && s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) {
            return s1[i] - s2[i];
        }
        i++;
    }
    if (i == max_len) return 0;
    return s1[i] - s2[i];
}

char* error_message() {
    switch(errno) {
        case EACCES:
            return "Permission denied";  // Attempted access to forbidden file
        case ENOENT:
            return "No such file or directory";  // File or directory does not exist
        case EEXIST:
            return "File exists";  // Attempt to create a file that already exists
        case EBADF:
            return "Bad file descriptor";  // Invalid file descriptor number
        case EISDIR:
            return "Is a directory";  // Expected a file, but is a directory
        case ENOTDIR:
            return "Not a directory";  // Expected a directory, but is not a directory
        case EAGAIN:
            return "Resource temporarily unavailable";  // Resource is temporarily unavailable
        case EINVAL:
            return "Invalid argument";  // Invalid argument to function
        case ENOSPC:
            return "No space left on device";  // No space left on the device
        case EPERM:
            return "Operation not permitted";  // Operation not permitted
        case ENOMEM:
            return "Cannot allocate memory";  // Insufficient memory available
        case ERANGE:
            return "Number out of range";  // Number out of range, such as during `atoi`
        case EINTR:
            return "Interrupted function call";  // Function call was interrupted by a signal
        case EIO:
            return "Input/output error";  // Generic I/O error
        case ENODEV:
            return "No such device";  // No such device
        case EROFS:
            return "Read-only file system";  // Attempted to modify a read-only file system
        case EBUSY:
            return "Device or resource busy";  // Device or resource is busy
        case EXDEV:
            return "Cross-device link";  // Attempted an operation across different devices
        case EFAULT:
            return "Bad address";  // Invalid address pointer
        case EPIPE:
            return "Broken pipe";  // Writing to a pipe without a reader
        default:
            mini_printf("Unhandled error code:", mini_itoa(errno),"\n");
            return "Unknown error";
    }
}

void mini_perror(char *message) {
    // Print the custom message, if provided
    if (message && message[0] != '\0') {
        write(2, message, mini_strnlen(message, ERROR_MAX)); // Write message to stderr (fd = 2)
        write(2, " : ", 3); // Print separator ": "
    }

    // Get the corresponding system error message and print it
    char* err_msg = error_message();
    write(2, err_msg, mini_strnlen(err_msg, 20)); // Write error message to stderr
    write(2, "\n", 1); // Newline
    mini_exit(errno);
}

char* mini_itoa(int num) {
    char* str = mini_calloc(sizeof(char), 12);  // Allocate memory for the string
    if (str == NULL) return NULL;  // Always check if memory allocation was successful

    int i = 0; 
    int isNegative = 0;

    // Handle negative numbers
    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    // Process individual digits
    do {
        str[i++] = num % 10 + '0';  // Get the last digit and convert it to a character
        num /= 10;
    } while (num != 0);

    // If number is negative, append '-'
    if (isNegative) {
        str[i++] = '-';
    }

    str[i] = '\0';  // Null-terminate the string

    // Reverse the string
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }

    return str;
}

int mini_atoi(char *s) {
    int result = 0;  // This will hold the converted number
    int sign = 1;    // This will hold the sign of the number

    // Skip whitespace
    while (*s == ' ' || *s == '\t' || *s == '\n') {
        s++;
    }

    // Check for a sign
    if (*s == '-') {
        sign = -1;
        s++;  // Move to the next character
    } else if (*s == '+') {
        s++;  // Move to the next character
    }

    // Convert each digit character to the corresponding integer value
    while (*s >= '0' && *s <= '9') {
        result = result * 10 + (*s - '0');
        s++;
    }

    return sign * result;  // Apply the sign before returning the result
}

int mini_strstr(char* haystack, char* needle) {
    for (int i = 0; haystack[i] != '\0'; i++) {
        int found = 1;
        for (int j = 0; needle[j] != '\0'; j++) {
            if (haystack[i + j] == '\0' || haystack[i + j] != needle[j]) {
                found = 0;
                break;
            }
        }
        if (found) {
            return 1; // Substring found
        }
    }
    return 0; // Substring not found
}

char* mini_strtok(char *str, const char *delim) {
    static char *next_token = NULL;
    char *start;
    char *end;

    // If str is not NULL, tokenizing str. If it is NULL, continue tokenizing the previous string
    if (str) {
        start = str;
    } else {
        if (!next_token)
            return NULL;
        start = next_token;
    }

    // Skip initial delimiter characters
    while (*start && mini_strchr(delim, *start)) {
        start++;
    }

    // If we reach the end of the string
    if (*start == '\0') {
        next_token = NULL;
        return NULL;
    }

    // Find the end of the token
    end = start;
    while (*end && !mini_strchr(delim, *end)) {
        end++;
    }

    // Place a null terminator at the end of the token
    if (*end) {
        *end++ = '\0';
    }

    // Update next_token to point past the current token
    next_token = end;

    return start;
}

char* mini_strchr(const char *s, int c) {
    while (*s != '\0') {
        if (*s == c) {
            return (char *)s;
        }
        s++;
    }
    return NULL;
}
