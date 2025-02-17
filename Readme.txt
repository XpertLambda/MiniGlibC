# TP Programmation Système

## MINI_LIB 

### **Macros**

| Macro          | Value                        | Comments                                      |
|----------------|------------------------------|-----------------------------------------------|
| `MEM_FAIL`     | "Memory allocation failed"   | Indicates memery fail message 				|
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
**I've created more functions than needed. Adjusted some existant. <br>
They're in <span style="color:red">red** </span>

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



## Question Exercice 5

Avant l'initialisation, il peut y avoir des données qui étaient en mémoire. Pour des raisons de sécurité, en remplissant avec des '\0' la mémoire qu'on souhaite utiliser, on garantit que n'importe quelle allocation de mémoire se termine par un terminateur nul, ce qui est utile pour les buffers, évitant ainsi des lectures hors limites ou des erreurs lors de la manipulation de chaînes.

## Question Exercice 6

D'après la définition de `free()` :
"La fonction `free()` en C libère la mémoire précédemment allouée dynamiquement avec `malloc()`, `calloc()` ou `realloc()`. Cependant, lorsqu'on appelle `free()`, la mémoire allouée est libérée pour être réutilisée *au sein du même processus*, mais elle n'est pas forcément retournée au système d'exploitation pour être utilisée par d'autres processus. La fonction met à jour les structures internes de l'allocateur de mémoire du processus pour marquer cet espace comme disponible pour de futures allocations."

## Question Exercice 17

Quand on affiche un seul caractère, les deux conditions d'arrêt sont lors de la première saut de ligne ou lorsque le tampon est plein, ce qui peut poser des problèmes surtout si la chaîne à afficher n'atteint pas `BUFF_SIZE` et n'avait pas de saut de ligne à la fin. Il faut donc ajouter une autre condition où l'ajout au tampon s'arrête et on l'affiche lorsque le caractère nul est atteint depuis la chaîne passée en paramètre.

## Question Exercice 20

Si le nombre de caractères saisis est égal à la taille du buffer, on aura un problème de "Buffer Overflow", d'où il peut y avoir un comportement inattendu ou un "segmentation fault" puisqu'il n'y aura plus de '\0' à la fin de notre chaîne. Pour résoudre cela, on prend byte par byte et on arrête à `size_buffer - 1` pour ajouter le '\0'.

## Question Exercice 22

`mini_strlen(char* s)`
Problème : si la chaîne d'entrée `s` n'est pas terminée par un caractère nul, la fonction continue de lire la mémoire au-delà de la mémoire allouée. Cela garantit que même si `s` n'est pas terminé par null, la fonction s'arrêtera après `max_len` caractères.

Explication : En acceptant `dest_size` comme paramètre, la fonction garantit qu'elle n'écrit pas plus de caractères que la mémoire tampon de destination ne peut en contenir, y compris le terminateur nul.

En introduisant `max_len`, la fonction évite de lire au-delà de la mémoire prévue, empêchant ainsi un comportement indéfini lorsque les chaînes ne sont pas correctement terminées par null.

## Question Exercice 33

Si le programme se termine alors que le buffer d’écriture n’était pas plein ?
Lorsque le programme se termine, si le buffer d'écriture (`buffer_write`) contient des données non écrites et qu'il n'est pas plein, ces données ne seront pas automatiquement écrites sur le disque. En effet, les données stockées dans le buffer sont en attente d'être écrites lorsque le buffer sera plein ou lorsqu'une opération de flush est effectuée. Si le programme se termine avant que cela ne se produise, les données restent dans le buffer et sont perdues, ce qui peut entraîner une perte de données et un état incohérent du fichier.

Pour résoudre ce problème, il faut s'assurer que tous les buffers d'écriture des fichiers ouverts sont vidés (flush) avant que le programme ne se termine. Cela peut être fait en modifiant la fonction `mini_exit` pour qu'elle effectue les opérations suivantes :

- Maintenir une liste des fichiers ouverts : Créer une structure de données (par exemple, une liste chaînée ou un tableau dynamique) qui contient des pointeurs vers tous les objets `MYFILE` représentant les fichiers actuellement ouverts.
- Flusher tous les fichiers ouverts : Parcourir la liste des fichiers ouverts dans `mini_exit` et appeler `mini_fflush` sur chacun d'eux pour forcer l'écriture des données du buffer sur le disque.
- Fermer les fichiers ouverts : Après le flush, s'assurer que tous les fichiers sont correctement fermés pour libérer les ressources.
