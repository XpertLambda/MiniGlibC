# Mini Lib Project

A minimalistic C library that reimplements basic system functionality: memory
management, string handling, buffered file I/O, and a set of shell-like
utilities, together with a small interactive shell that ties them together.

## Features

- **Custom memory management** - `mini_calloc`, `mini_free`, and `mini_exit`
  backed by a linked list of allocated blocks.
- **String utilities** - length, copy, compare, tokenize, search, and
  integer/string conversion (`mini_strlen`, `mini_strncpy`, `mini_strtok`,
  `mini_strstr`, `mini_itoa`, `mini_atoi`, and more).
- **Buffered file I/O** - a small `MYFILE` abstraction with `mini_fopen`,
  `mini_fread`, `mini_fwrite`, `mini_fflush`, `mini_fclose`, `mini_fgetc`, and
  `mini_fputc`, tracked through an open-files list.
- **Shell-like commands** - reimplementations of common utilities such as
  `cat`, `cp`, `ls`, `grep`, `head`, `tail`, `wc`, `echo`, `touch`, `mkdir`,
  `rm`, `rmdir`, `mv`, `chmod`, `cd`, `pwd`, `env`, `getenv`, and `export`.
- **Interactive shell** - `SHELL`, a minimal command interpreter that loads
  `~/.mini_bashrc` on startup and dispatches to the utilities above.

## Project Structure

```
src/
  mini_lib.h        Definitions, structures, and function prototypes
  mini_memory.c     Memory management implementation
  mini_string.c     String utilities implementation
  mini_io.c         Buffered file I/O implementation
  SHELL/
    Makefile        Build/test/clean rules
    mini_shell.c    Shell-command implementations (mini_cat, mini_ls, ...)
    SHELL.c         Interactive shell entry point
    mini_*.c        Standalone entry point for each utility
```

### Header File (`mini_lib.h`)

The `mini_lib.h` file contains definitions, structures, and function prototypes
for memory management, string manipulation, file handling, and shell-like
commands.

#### Key Structures

- **`malloc_element`**: Represents an allocated memory block and its status
  (used or free).
- **`MYFILE`**: Represents an open file, its buffers, and file descriptor.

#### Memory Management Functions

- **`mini_calloc`**: Allocates memory for an array of elements and initializes
  it to zero.
- **`mini_free`**: Frees a previously allocated memory block.
- **`mini_exit`**: Terminates the program and cleans up.

#### String Functions

- **`real_mini_printf`**: A simple printf function that prints multiple strings
  using variadic arguments (invoked via the `mini_printf` macro).
- **`mini_scanf`**: Reads user input into a buffer.
- **`mini_strlen`**: Computes the length of a string.
- **`mini_strncpy`**: Copies a string to another buffer with a size limit.
- **`mini_strtok`**: Tokenizes a string based on delimiters.
- Additional functions include `mini_strnlen`, `mini_strcpy`, `mini_strncmp`,
  `mini_strcmp`, `mini_perror`, `mini_itoa`, `mini_atoi`, `mini_strstr`, and
  `mini_strchr`.

#### File Operations

- **`mini_fopen`**: Opens a file with a specified mode ('r' for read, 'w' for
  write).
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
- **`mini_pwd`**: Prints the current working directory (implemented with
  `getcwd`).

#### Error Handling

- **`error_message`**: Returns a message describing the last error encountered.
- **`mini_perror`**: Prints a system error message followed by a custom message.

#### Constants

- **`MEM_FAIL`**: Error message for memory allocation failure.
- **`USED`, `FREE`, `NOT_INIT`**: Memory block states.
- **`BUF_SIZE`, `IOBUFFER_SIZE`, `MAX_ARGS`, `MAX_PATH`**: Buffer and argument
  sizes.
- **`ERROR_MAX`**: Maximum length for error messages.

## Installation

The project is built with `gcc` and `make`. A `Makefile` lives in the
`src/SHELL` directory:

```bash
cd src/SHELL
make          # Build all utilities and the interactive shell
make test     # Run basic functionality tests
make clean    # Remove compiled files
```

Compilation flags are `-Wall -Wextra -std=c99 -pedantic -g`.

## Usage

After building, run the interactive shell or any individual utility from
`src/SHELL`:

```bash
cd src/SHELL
./SHELL                 # Start the interactive mini-shell
./mini_echo "Hello"     # Run a standalone utility
./mini_cat file.txt
./mini_ls .
```

To use the library in your own C program, include the header and compile
against the implementation files:

```c
#include "mini_lib.h"
```

## Recent Improvements

The project has been reviewed and the following changes were made:

### Code Quality Improvements
- Fixed memory management: `malloc`/`free` calls replaced with custom
  `mini_calloc`/`mini_free`.
- Corrected function parameter order in `mini_strcpy` and `mini_strncpy`.
- Fixed buffer management in file I/O operations.
- Added proper null-termination in string operations.
- Fixed compilation warnings and errors with modern compiler flags.

### Structure
- Added error handling throughout the codebase.
- Improved the Makefile with proper compilation flags
  (`-Wall -Wextra -std=c99 -pedantic -g`).
- Added a basic test target in the Makefile.
- Fixed header file declarations to match implementations.
- Added feature test macros for POSIX compliance.

### Functionality Fixes
- Fixed file descriptor leaks by properly tracking open files.
- Reimplemented `mini_pwd` to use the standard `getcwd`.
- Fixed `mini_export` with proper environment variable handling.
- Added proper newline handling in output functions.
- Fixed memory leaks in buffer allocations.

## License

This project is licensed under the GNU GPL v3.0. See [LICENSE](LICENSE).
