# MINI_LIB

### **Macros**

| Macro          | Value                        | Comments                                      |
|----------------|------------------------------|-----------------------------------------------|
| `MEM_FAIL`     | "Memory allocation failed"    | Indicates memory allocation failure           |
| `USED`         | 1                            | Indicates memory is currently used            |
| `FREE`         | 0                            | Indicates memory is free                      |
| `NOT_INIT`     | -1                           | Indicates uninitialized state                 |
| `BUF_SIZE`     | 1024                         | Size of the buffer                            |
| `ERROR_MAX`    | 256                          |                                               |
| `IOBUFFER_SIZE`| 2048                         | Size of input/output buffer                   |
| `MAX_ARGS`     | 64                           | Maximum number of arguments in a command      |
| `MAX_PATH`     | 4096                         | Suitable buffer size for path                 |

### **Structures**
```c
typedef struct malloc_element{
    void* zone;  // Pointer to the allocated memory block
    size_t total_size;  // Size of the allocated block
    int status;  // Status of the memory (USED/FREE)
    struct malloc_element* next_malloc;  // Pointer to next memory block
} malloc_element;

typedef struct MYFILE{
    int fd;  // File descriptor
    void* buffer_read;  // Pointer to read buffer
    void* buffer_write;  // Pointer to write buffer
    int ind_read;  // Read buffer index
    int ind_write;  // Write buffer index
    struct MYFILE *next;  // Pointer to next file in the open file list
} MYFILE;
```

### **Functions**
**I have created more functions than needed and adjusted some existing ones. <br>
They are highlighted in <span style="color:red">red** </span>

| Function Signature                                       | Explanation                                                        |
|----------------------------------------------------------|--------------------------------------------------------------------|
| `void* mini_calloc(int size_element, int number_element)`| Allocates memory for an array of elements and initializes it to zero. <br> @size_element: Size of each element. <br> @number_element: Number of elements to allocate. <br> @return: Pointer to the allocated memory or NULL on failure. |
| `void mini_free(void* ptr)`                              | Frees the memory block pointed to by ptr. <br> @ptr: Pointer to the memory block to be freed. |
| `void mini_exit(int status)`                             | Terminates the program and cleans up. <br> @status: Exit status code. |
| <span style="color:red">`void real_mini_printf(char* args[])`</span>                    | Prints a string to the standard output. <br> @args: The array of strings to be printed. |
| `int mini_scanf(char* buffer, int size_buffer)`          | Reads input from standard input into the provided buffer. <br> @buffer: The buffer to store the input. <br> @size_buffer: Size of the buffer. <br> @return: The number of characters read. |
| <span style="color:red">`int mini_strnlen(char* s, size_t max_len)`</span>               | Returns the length of the string up to a maximum number of characters. <br> @s: The string to measure. <br> @max_len: Maximum number of characters to measure. |
| <span style="color:red">`int mini_strncpy(char* s, char* d, size_t dest_size)`</span>    | Copies a string to a destination buffer. <br> @s: Source string. <br> @d: Destination buffer. <br> @dest_size: Size of the destination buffer. |
| <span style="color:red">`int mini_strncmp(char* s1, char* s2, size_t max_len)`</span>    | Compares two strings up to a maximum length. <br> @s1: First string. <br> @s2: Second string. <br> @max_len: Maximum number of characters to compare. |
| `int mini_strlen(char* s)`              | Returns the length of the string up to a maximum number of characters. <br> @s: The string to measure. <br> |
| `int mini_strcpy(char* s, char* d)`    | Copies a string to a destination buffer. <br> @s: Source string. <br> @d: Destination buffer. |
| `int mini_strcmp(char* s1, char* s2)`    | Compares two strings up to a maximum length. <br> @s1: First string. <br> @s2: Second string. |
| `void mini_perror(char* message)`                        | Prints an error message to standard error. <br> @message: The error message to print. |
| <span style="color:red">`char* mini_strtok(char *str, const char *delim)`</span>  | A custom strtok function that tokenizes strings based on given delimiters. <br> @str: The string to tokenize; pass NULL to continue tokenizing the previous string. <br> @delim: The delimiters used to split the string. <br> @return: A pointer to the next token, or NULL if there are no more tokens. |
| <span style="color:red">`char* mini_strchr(const char *s, int c)`</span>  | Finds the first occurrence of any of the characters in `delim` in the string `s`. <br> @s: The string to search. <br> @delim: The characters to search for. <br> @return: A pointer to the first occurrence of any character in `delim`, or NULL if none found. |
| <span style="color:red">`int mini_atoi(char *s)`</span>                                 | Converts a string to an integer. <br> @s: String to convert. |
| <span style="color:red">`int mini_strstr(char* word1, char* word2)`</span>               | Finds the first occurrence of the substring `word2` in `word1`. <br> @word1: Main string. <br> @word2: Substring to find. |
| `int mini_fread(void* buffer, int size_element, int number_element, MYFILE *file)` | Reads data from a file into a buffer. <br> @buffer: Buffer to store data. <br> @size_element: Size of each element. <br> @number_element: Number of elements to read. <br> @file: File pointer. |
| `int mini_fwrite(void* buffer, int size_element, int number_element, MYFILE *file)`| Writes data from a buffer to a file. <br> @buffer: Buffer containing data. <br> @size_element: Size of each element. <br> @number_element: Number of elements to write. <br> @file: File pointer. |
| `int mini_fflush(MYFILE* file)`                           | Flushes the write buffer of a file. <br> @file: File pointer to flush. |
| `void add_to_open_file_list(MYFILE *file)`                | Adds a file to the open file list. <br> @file: File to add. |
| `void remove_from_open_file_list(MYFILE *file)`           | Removes a file from the open file list. <br> @file: File to remove. |
| `int mini_fclose(MYFILE* file)`                           | Closes an open file. <br> @file: File pointer to close. |
| `int mini_fgetc(MYFILE* file)`                            | Reads a character from a file. <br> @file: File pointer. |
| `int mini_fputc(MYFILE* file, char c)`                    | Writes a character to a file. <br> @file: File pointer. <br> @c: Character to write. |
| `void mini_touch(char* file_name)`                        | Creates a new file or updates the timestamp of an existing file. <br> @file_name: Name of the file. |
| `void mini_cp(char* src, char* dest)`                     | Copies a file from `src` to `dest`. <br> @src: Source file path. <br> @dest: Destination file path. |
| `void mini_cat(char* file_name)`                          | Displays the content of a file. <br> @file_name: Name of the file. |
| `void mini_head(char* file_name, int N)`                  | Displays the first `N` lines of a file. <br> @file_name: Name of the file. <br> @N: Number of lines to display. |
| `void mini_tail(char* file_name, int N)`                  | Displays the last `N` lines of a file. <br> @file_name: Name of the file. <br> @N: Number of lines to display. |
| `void mini_clean(char* file_name)`                        | Deletes all content in a file without removing the file. <br> @file_name: Name of the file. |
| `void mini_wc(char *file_name)`                           | Counts the number of lines, words, and characters in a file. <br> @file_name: Name of the file. |
| `void mini_echo(char* chaine)`                            | Outputs the string to the console. <br> @chaine: String to output. |
| `void mini_grep(char* word, char* file_name)`             | Searches for `word` in the file `file_name`. <br> @word: Word to search for. <br> @file_name: File to search in. |
| `void mini_ls(char *path)`                                | Lists all files and directories at the specified path. <br> @path: Path to list. |
| `void mini_chmod(char *file, int mode)`                   | Changes the mode (permissions) of a file. <br> @file: File whose permissions to change. <br> @mode: New permissions. |
| `void mini_mkdir(char *path)`                             | Creates a new directory. <br> @path: Path of the new directory. |
| `void mini_mv(char *oldpath, char *newpath)`              | Moves or renames a file from `oldpath` to `newpath`. <br> @oldpath: Current path of the file. <br> @newpath: New path of the file. |
| `void mini_rm(char *file)`                                | Removes a file. <br> @file: File to remove. |
| `void mini_rmdir(char *path)`                             | Removes a directory. <br> @path: Directory to remove. |
| `void mini_quickdiff(char *file1, char *file2)`           | Compares two files and displays differences. <br> @file1: First file. <br> @file2: Second file. |
| `void mini_cd(char *path)`                                | Changes the current directory. <br> @path: New directory path. |
| `void mini_env()`                                         | Displays all environment variables. |
| `void mini_getenv(char *name)`                            | Retrieves the value of an environment variable. <br> @name: Name of the variable. |
| `void mini_export(char *var)`                             | Adds or modifies an environment variable. <br> @var: Variable to modify or add. |
| <span style="color:red">`void mini_pwd()`</span>                                         | Displays the current working directory. |

Before initialization, there might be data left in memory. For security reasons, by filling the memory with '