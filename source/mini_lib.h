#ifndef __MINI_LIB__
#define __MINI_LIB__

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h> // For size_t definition
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <dirent.h>


#define MEM_FAIL "Memory allocation failed" // Error message to display when memory allocation fails
#define USED 1  // Indicates memory is currently used
#define FREE 0  // Indicates memory is free
#define NOT_INIT -1 // Indicates uninitialized state
#define BUF_SIZE 1024 // Size of the buffer
#define ERROR_MAX 256
#define IOBUFFER_SIZE 2048 // Size of input/output buffer
#define MAX_ARGS 64  // Maximum number of arguments in a command
#define MAX_PATH 4096 // Suitable buffer size for path

// Created a better verision of mini_printf wich can pint multiple string at once by using vargs
#define mini_printf(...) real_mini_printf((char*[]){__VA_ARGS__, NULL})


/**
 * Structure representing an allocated memory block.
 * 
 * @zone: Pointer to the allocated memory.
 * @total_size: Total size of the memory block.
 * @status: Status of the memory (USED or FREE).
 * @next_malloc: Pointer to the next allocated block in the linked list.
 */
typedef struct malloc_element{
	void* zone;  // Pointer to the allocated memory block
	size_t total_size;  // Size of the allocated block
	int status;  // Status of the memory (USED/FREE)
	struct malloc_element* next_malloc;  // Pointer to next memory block
} malloc_element;

/**
 * Structure representing a file in the system.
 * 
 * @fd: File descriptor associated with the file.
 * @buffer_read: Pointer to the read buffer.
 * @buffer_write: Pointer to the write buffer.
 * @ind_read: Current index in the read buffer.
 * @ind_write: Current index in the write buffer.
 * @next: Pointer to the next file in the linked list.
 */
typedef struct MYFILE{
	int fd;  // File descriptor
	void* buffer_read;  // Pointer to read buffer
	void* buffer_write;  // Pointer to write buffer
	int ind_read;  // Read buffer index
	int ind_write;  // Write buffer index
	struct MYFILE *next;  // Pointer to next file in the open file list
} MYFILE;

// Global variables for memory and file management
extern malloc_element *malloc_list; // Linked list of allocated memory blocks
extern char buffer[]; // General-purpose buffer
extern int ind; // Buffer index for tracking positions
extern MYFILE *open_files_list; // Linked list of open files
extern char** environ; // Environment varibale

//____________MINI_MEMROY.C____________
/**
 * Allocates memory for an array of elements and initializes it to zero.
 * 
 * @size_element: Size of each element.
 * @number_element: Number of elements to allocate.
 * @return: Pointer to the allocated memory or NULL on failure.
 */
void* mini_calloc(int size_element, int number_element);

/**
 * Frees the memory block pointed to by ptr.
 * 
 * @ptr: Pointer to the memory block to be freed.
 */
void mini_free(void* ptr);

/**
 * Terminates the program and cleans up.
 * 
 * @status: Exit status code.
 */
void mini_exit(int status);

//____________MINI_STRING.C____________
/**
 * Prints a string to the standard output.
 * 
 * @args: The array of strings to be printed.
 */
void real_mini_printf(char* args[]);

/**
 * Reads input from standard input into the provided buffer.
 * 
 * @buffer: The buffer to store the input.
 * @size_buffer: Size of the buffer.
 * @return: The number of characters read.
 */
int mini_scanf(char* buffer, int size_buffer);

/**
 * Computes the length of the given string.
 * 
 * @s: The string whose length is to be computed.
 * @max_len: maximum allocated memory for s
 * @return: Length of the string.
 */
int mini_strnlen(char* s, size_t max_len);

/**
 * Computes the length of the given string.
 * 
 * @s: The string whose length is to be computed.
 * @return: Length of the string.
 */
int mini_strlen(char* s);

/**
 * Copies the string from source to destination.
 * 
 * @s: Source string.
 * @d: Destination string.
 * @dest_size: maximum allocated memory for d
 * @return: 0 on success, -1 on failure.
 */
int mini_strncpy(char* s, char* d, size_t dest_size);

/**
 * Copies the string from source to destination.
 * 
 * @s: Source string.
 * @d: Destination string.
 * @return: 0 on success, -1 on failure.
 */
int mini_strcpy(char* s, char* d);

/**
 * Compares two strings lexicographically.
 * 
 * @s: First string.
 * @d: Second string.
 * @max_len: maximum allocated memory for the smaller memory between s1 or s2 
 * @return: 0 if strings are equal, non-zero otherwise.
 */
int mini_strncmp(char* s1, char* s2, size_t max_len);

/**
 * Compares two strings lexicographically.
 * 
 * @s: First string.
 * @d: Second string.
 * @return: 0 if strings are equal, non-zero otherwise.
 */
int mini_strcmp(char* s1, char* s2);



/**
 * Returns a message describing the last error encountered.
 * 
 * @return: Error message string.
 */
char* error_message();

/**
 * Prints a system error message followed by a custom message.
 * 
 * @message: Custom error message.
 */
void mini_perror(char* message);

/**
 * Converts an integer to a string.
 * @param num The integer to be converted.
 * @return The Stringed value of the integer.
 */
char* mini_itoa(int num);

/**
 * Converts a string to an integer.
 * @param s The string containing the integer representation.
 * @return The integer value of the string.
 */
int mini_atoi(char *s);

/**
 * Searches for the first occurrence of the substring 'word2' in the string 'word1'.
 * @param word1 The string to be searched.
 * @param word2 The substring to find.
 * @return A pointer to the beginning of the substring in 'word1', or NULL if the substring is not found.
 */
int mini_strstr(char* word1, char* word2);

/**
 * A custom strtok function that tokenizes strings based on given delimiters.
 * @param str The string to tokenize; pass NULL to continue tokenizing the previous string.
 * @param delim The delimiters used to split the string.
 * @return A pointer to the next token, or NULL if there are no more tokens.
 */
char* mini_strtok(char *str, const char *delim);

/**
 * Finds the first occurrence of any of the characters in `delim` in the string `s`.
 * @param s The string to search.
 * @param delim The characters to search for.
 * @return A pointer to the first occurrence of any character in `delim`, or NULL if none found.
 */
char* mini_strchr(const char *s, int c);

//____________MINI_IO.C____________
/**
 * Opens a file with the specified mode (read or write).
 * 
 * @file: Path to the file.
 * @mode: Mode for opening the file ('r' for read, 'w' for write).
 * @return: Pointer to MYFILE structure representing the opened file.
 */
MYFILE* mini_fopen(char* file, char mode);

/**
 * Reads data from a file into the provided buffer.
 * 
 * @buffer: Buffer to store the data.
 * @size_element: Size of each element.
 * @number_element: Number of elements to read.
 * @file: Pointer to the file from which to read.
 * @return: Number of elements read.
 */
int mini_fread(void* buffer, int size_element, int number_element, MYFILE* file);

/**
 * Writes data from the buffer to the file.
 * 
 * @buffer: Buffer containing the data to write.
 * @size_element: Size of each element.
 * @number_element: Number of elements to write.
 * @file: Pointer to the file to which data will be written.
 * @return: Number of elements written.
 */
int mini_fwrite(void* buffer, int size_element, int number_element, MYFILE* file);

/**
 * Flushes the write buffer of a file.
 * 
 * @file: Pointer to the file to flush.
 * @return: 0 on success, -1 on failure.
 */
int mini_fflush(MYFILE* file);

/**
 * Adds a file to the list of open files.
 * 
 * @file: Pointer to the file to add to the list.
 */
void add_to_open_file_list(MYFILE *file);

/**
 * Removes a file from the list of open files.
 * 
 * @file: Pointer to the file to remove from the list.
 */
void remove_from_open_file_list(MYFILE *file);

/**
 * Closes a file and removes it from the list of open files.
 * 
 * @file: Pointer to the file to close.
 * @return: 0 on success, -1 on failure.
 */
int mini_fclose(MYFILE* file);

/**
 * Reads a single character from the file.
 * 
 * @file: Pointer to the file from which to read.
 * @return: The character read, or -1 on failure.
 */
int mini_fgetc(MYFILE* file);

/**
 * Writes a single character to the file.
 * 
 * @file: Pointer to the file to which the character will be written.
 * @c: The character to write.
 * @return: 0 on success, -1 on failure.
 */
int mini_fputc(MYFILE* file, char c);

//____________MINI_SHELL.C____________
/**
 * mini_touch - Creates an empty file if it doesn't already exist.
 *
 * @file_name: The name of the file to create.
 */
void mini_touch(char* file_name);

/**
 * mini_cp - Copies the contents of the source file into a destination file.
 *
 * @src: The source file to copy.
 * @dest: The destination file.
 */
void mini_cp(char* src, char* dest);

/**
 * mini_cat - Displays the contents of a file.
 *
 * @file_name: The name of the file whose contents will be displayed.
 */
void mini_cat(char* file_name);

/**
 * mini_head - Displays the first N lines of a file.
 *
 * @file_name: The name of the file whose lines will be displayed.
 * @N: The number of lines to display.
 */
void mini_head(char* file_name, int N);

/**
 * mini_tail - Displays the last N lines of a file.
 *
 * @file_name: The name of the file whose last lines will be displayed.
 * @N: The number of lines to display.
 */
void mini_tail(char* file_name, int N);

/**
 * mini_clean - Creates an empty file if it doesn't exist or clears the contents of an existing file.
 *
 * @file_name: The name of the file to clear or create.
 */
void mini_clean(char* file_name);

/**
 * Counts the words in a file.
 * @param file_name The path to the file.
 */
void mini_wc(char *file_name);


/**
 * mini_echo - Displays a string to the screen.
 *
 * @chaine: The string to display (can contain spaces).
 */
void mini_echo(char* chaine);

/**
 * mini_grep - Searches and displays all lines containing a specific word in a file.
 *
 * @word: The word to search for in the file.
 * @file_name: The name of the file in which to search for the word.
 */
void mini_grep(char* word, char* file_name);

/**
 * Lists the contents of a directory.
 * @param path The path of the directory to list.
 */
void mini_ls(char *path);

/**
 * Changes the permissions of a file or directory.
 * @param file Path to the file or directory.
 * @param mode Permission settings to apply.
 */
void mini_chmod(char *file, int mode);

/**
 * Creates a directory.
 * @param path The path of the directory to create.
 */
void mini_mkdir(char *path);

/**
 * Moves or renames a file or directory.
 * @param oldpath The current path of the file or directory.
 * @param newpath The new path of the file or directory.
 */
void mini_mv(char *oldpath, char *newpath);

/**
 * Removes a file.
 * @param file The path to the file to remove.
 */
void mini_rm(char *file);

/**
 * Removes a directory.
 * @param path The path of the directory to remove.
 */
void mini_rmdir(char *path);

/**
 * Compares two files and reports if they are identical or not.
 * @param file1 Path to the first file.
 * @param file2 Path to the second file.
 */
void mini_quickdiff(char *file1, char *file2);

/**
 * Changes the current directory.
 * @param path The path to change to.
 */
void mini_cd(char *path);

/**
 * Prints all environment variables.
 */
void mini_env(void);

/**
 * Prints the value of a specified environment variable.
 * @param name The name of the environment variable to query.
 */
void mini_getenv(char *name);

/**
 * Adds or modifies an environment variable.
 * @param var The variable with format "KEY=value" to add or modify.
 */
void mini_export(char *var);


/**
 * Prints the current working directory using low-level system calls.
 */
void mini_pwd();

#endif
