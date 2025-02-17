# Mini Lib Project

This project implements a minimalistic library that provides basic functionalities such as memory management, string handling, file operations, and shell-like utilities. It mimics some of the basic system commands and provides simple I/O operations.

## Project Structure

### Header File (`mini_lib.h`)

The `mini_lib.h` file contains definitions, structures, and function prototypes for memory management, string manipulation, file handling, and shell-like commands.

#### Key Structures

- **`malloc_element`**: Represents an allocated memory block and its status (used or free).
- **`MYFILE`**: Represents an open file, its buffers, and file descriptor.

#### Memory Management Functions

- **`mini_calloc`**: Allocates memory for an array of elements and initializes it to zero.
- **`mini_free`**: Frees a previously allocated memory block.
- **`mini_exit`**: Terminates the program and cleans up.

#### String Functions

- **`real_mini_printf`**: A simple printf function that prints multiple strings using variadic arguments.
- **`mini_scanf`**: Reads user input into a buffer.
- **`mini_strlen`**: Computes the length of a string.
- **`mini_strncpy`**: Copies a string to another buffer with a size limit.
- **`mini_strtok`**: Tokenizes a string based on delimiters.
- Additional functions include `mini_strnlen`, `mini_strcpy`, `mini_strncmp`, `mini_strcmp`, `mini_perror`, `mini_itoa`, `mini_atoi`, `mini_strstr`, and `mini_strchr`.

#### File Operations

- **`mini_fopen`**: Opens a file with a specified mode ('r' for read, 'w' for write).
- **`mini_fread`**: Reads data from a file into a buffer.
- **`mini_fwrite`**: Writes data from a buffer to a file.
- **`mini_fflush`**: Flushes the write buffer of a file.
- **`mini_fclose`**: Closes a file and removes it from the open file list.
- **`mini_fgetc`**: Reads a single character from a file.
- **`mini_fputc`**: Writes a single character to a file.
- Helper functions include adding and removing files from the open files list.

#### Shell-like Commands

- **`mini_touch`**: Creates an empty file if it doesn't exist.
- **`mini_cp`**: Copies contents from source file to destination.
- **`mini_cat`**: Displays the contents of a file.
- **`mini_head`**: Displays the first N lines of a file.
- **`mini_tail`**: Displays the last N lines of a file.
- **`mini_clean`**: Clears or creates an empty file.
- **`mini_wc`**: Counts the number of words in a file.
- **`mini_echo`**: Displays a string to the screen.
- **`mini_grep`**: Searches for a word in a file and displays matching lines.
- **`mini_ls`**: Lists the contents of a directory.
- **`mini_chmod`**: Changes the permissions of a file or directory.
- **`mini_mkdir`**: Creates a directory.
- **`mini_mv`**: Renames or moves a file/directory.
- **`mini_rm`**: Removes a file.
- **`mini_rmdir`**: Removes a directory.
- **`mini_quickdiff`**: Compares two files and reports if they are identical.
- **`mini_cd`**: Changes the current directory.
- **`mini_env`**: Prints all environment variables.
- **`mini_getenv`**: Prints the value of a specified environment variable.
- **`mini_export`**: Adds or modifies an environment variable.
- **`mini_pwd`**: Prints the current working directory using low-level system calls.

## Error Handling

- **`error_message`**: Returns a message describing the last error encountered.
- **`mini_perror`**: Prints a system error message followed by a custom message.

## Constants

- **`MEM_FAIL`**: Error message for memory allocation failure.
- **`USED`, `FREE`, `NOT_INIT`**: Memory block states.
- **`BUF_SIZE`, `IOBUFFER_SIZE`, `MAX_ARGS`, `MAX_PATH`**: Buffer and argument sizes.
- **`ERROR_MAX`**: Maximum length for error messages.

## Usage

The library provides various functionalities that can be used in C programs for basic operations like memory management, file handling, and interacting with the operating system.

- To use the library, include the `mini_lib.h` header file in your source code.
- Compile the code with the necessary source files to link the functions.

## Makefile

The `Makefile` is located in the `miniGlibc/src/SHELL` directory. Use it to build the project:
```bash
cd miniGlibc/src/SHELL
make
```