#include "mini_lib.h"

void mini_touch(char* file_name) {
    MYFILE* file = mini_fopen(file_name, 'w');
    if (file == NULL) {
        mini_perror("Failed to create file");
        return;
    }
    mini_fclose(file);
}

void mini_cp(char* src, char* dest) {
    char buffer[BUF_SIZE];
    MYFILE* src_file = mini_fopen(src, 'r');
    if (src_file == NULL) {
        mini_perror("Source file not found");
        return;
    }

    MYFILE* dest_file = mini_fopen(dest, 'w');
    if (dest_file == NULL) {
        mini_perror("Failed to open destination file");
        mini_fclose(src_file);
        return;
    }

    int bytes_read;
    while ((bytes_read = mini_fread(buffer, 1, BUF_SIZE, src_file)) > 0) {
        mini_fwrite(buffer, 1, bytes_read, dest_file);
    }

    mini_fclose(src_file);
    mini_fclose(dest_file);
}

void mini_cat(char* file_name) {
    char buffer[BUF_SIZE];
    MYFILE* file = mini_fopen(file_name, 'r');
    if (file == NULL) {
        mini_perror("File not found");
        return;
    }

    int bytes_read;
    while ((bytes_read = mini_fread(buffer, 1, BUF_SIZE, file)) > 0) {
        mini_printf(buffer);
    }

    mini_fclose(file);
}

void mini_head(char* file_name, int N) {
    char buffer[BUF_SIZE];
    MYFILE* file = mini_fopen(file_name, 'r');
    if (file == NULL) {
        mini_perror("File not found");
        return;
    }

    int lines = 0;
    int bytes_read;
    while ((bytes_read = mini_fread(buffer, 1, BUF_SIZE, file)) > 0 && lines < N) {
        for (int i = 0; i < bytes_read && lines < N; i++) {
            write(STDOUT_FILENO, &buffer[i], 1);
            if (buffer[i] == '\n') {
                lines++;
            }
        }
    }

    mini_fclose(file);
}

void mini_tail(char* file_name, int N) {
    char buffer[BUF_SIZE];
    MYFILE* file = mini_fopen(file_name, 'r');
    if (file == NULL) {
        mini_perror("File not found");
        return;
    }

    // Lire tout le fichier pour compter les lignes
    int total_lines = 0;
    int bytes_read;
    while ((bytes_read = mini_fread(buffer, 1, BUF_SIZE, file)) > 0) {
        for (int i = 0; i < bytes_read; i++) {
            if (buffer[i] == '\n') {
                total_lines++;
            }
        }
    }

    // Repositionner le pointeur au début du fichier
    mini_fclose(file);
    file = mini_fopen(file_name, 'r');
    int lines_to_skip = total_lines - N;
    int current_line = 0;

    while ((bytes_read = mini_fread(buffer, 1, BUF_SIZE, file)) > 0) {
        for (int i = 0; i < bytes_read; i++) {
            if (current_line >= lines_to_skip) {
                write(STDOUT_FILENO, &buffer[i], 1);
            }
            if (buffer[i] == '\n') {
                current_line++;
            }
        }
    }

    mini_fclose(file);
}

void mini_clean(char* file_name) {
    MYFILE* file = mini_fopen(file_name, 'w');
    if (file == NULL) {
        mini_perror("Failed to create or clean file");
        return;
    }
    mini_fclose(file);
}

void mini_wc(char *file_name) {
    MYFILE *file = mini_fopen(file_name, 'r');
    if (file == NULL) {
        mini_perror("Failed to open file");
        return;
    }

    int word_count = 0;
    int in_word = 0;
    char c;
    while ((c = mini_fgetc(file)) != -1) {
        if (c == ' ') {
            if (in_word) {
                word_count++;
                in_word = 0;
            }
        } else {
            in_word = 1;
        }
    }

    // If the last character was not a space, the last word won't be counted in the loop
    if (in_word) {
        word_count++;
    }

    mini_fclose(file);
    mini_printf("Word count: ", mini_itoa(word_count),"\n");
}

void mini_echo(char* str){
    mini_printf(str);
}

void mini_grep(char* keyword, char* filename){
    // Allocate a buffer to hold lines from the file
    char* buffer = mini_calloc(sizeof(char), IOBUFFER_SIZE);
    if (!buffer) {
        mini_printf(MEM_FAIL);
        mini_exit(1);
    }

    // Open the file
    MYFILE* file = mini_fopen(filename, 'r');
    if (!file) {
        mini_printf("Failed to open file");
        mini_free(buffer);
        mini_exit(1);
    }

    int index = 0, c;
    while ((c = mini_fgetc(file)) != -1) { // Read until EOF
        if (c != '\n' && index < IOBUFFER_SIZE - 1) {
            buffer[index++] = c;
        } else {
            // Terminate the current line and reset index
            buffer[index] = '\0';

            // Check if the keyword exists in the line
            if (mini_strstr(buffer, keyword)) {
                mini_printf(buffer);
            }

            // Reset the buffer index for the next line
            index = 0;
        }
    }

    // Free the allocated buffer and close the file
    mini_free(buffer);
    mini_fclose(file);
}

void mini_ls(char *path) {
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(path)) == NULL) {
        mini_perror("Failed to open directory");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        mini_printf(entry->d_name,"\n");
    }

    closedir(dir);
}

void mini_chmod(char *file, int mode) {
    if (chmod(file, mode) < 0) {
        mini_perror("chmod failed");
    }
}

void mini_mkdir(char *path) {
    if (mkdir(path, 0755) < 0) { // 0755 are typical read/write/execute permissions
        mini_perror("mkdir failed");
    }
}

void mini_mv(char *oldpath, char *newpath) {
    if (rename(oldpath, newpath) < 0) {
        mini_perror("mv failed");
    }
}

void mini_rm(char *file) {
    if (unlink(file) < 0) {
        mini_perror("rm failed");
    }
}

void mini_rmdir(char *path) {
    if (rmdir(path) < 0) {
        mini_perror("rmdir failed");
    }
}

void mini_quickdiff(char *file1, char *file2) {
    MYFILE *f1 = mini_fopen(file1, 'r');
    MYFILE *f2 = mini_fopen(file2, 'r');
    int c1, c2;

    if (!f1 || !f2) {
        mini_perror("Failed to open files");
        return;
    }

    while ((c1 = mini_fgetc(f1)) != -1 && (c2 = mini_fgetc(f2)) != -1) {
        if (c1 != c2) {
            mini_printf("Files differ\n");
            mini_fclose(f1);
            mini_fclose(f2);
            return;
        }
    }

    mini_printf("Files are the same\n");
    mini_fclose(f1);
    mini_fclose(f2);
}

void mini_cd(char *path) {
    if (chdir(path) != 0) {
        mini_perror("Failed to change directory");
    }
}

void mini_env() {
    for (int i = 0; environ[i] != NULL; i++) {
        mini_printf(environ[i],"\n");
    }
}

void mini_getenv(char *name) {
    int len = mini_strnlen(name, BUF_SIZE);
    for (int i = 0; environ[i] != NULL; i++) {
        if (mini_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=') {
            mini_printf(&environ[i][len+1],"\n");
            return;
        }
    }
    mini_printf("Variable ",name," not found\n");
}
void mini_export(char *var) {
    char *equal_sign = mini_strchr(var, '='); // Find the '=' character
    if (equal_sign == NULL || equal_sign == var || *(equal_sign + 1) == '\0') {
        // Check if the '=' is missing or if there's no key or value
        mini_perror("Invalid format for environment variable. Use 'KEY=value'\n");
    }

    // Calculate the length of the key and value
    size_t key_length = equal_sign - var; // Length of the key
    size_t value_length = mini_strlen(equal_sign + 1); // Length of the value

    // Create buffers for the key and value
    char *key = (char *)mini_calloc(key_length + 1, 1);
    char *value = (char *)mini_calloc(value_length + 1, 1);

    if (key == NULL || value == NULL) {
        mini_perror(MEM_FAIL);
        return;
    }

    // Copy the key and value into the buffers
    mini_strncpy(key, var, key_length);
    key[key_length] = '\0'; // Null-terminate the key
    mini_strcpy(value, equal_sign + 1); // Copy value and null-terminate

    // Use setenv to set the environment variable
    if (setenv(key, value, 1) != 0) {
        mini_perror("Failed to set environment variable");
    }

    // Free allocated memory
    free(key);
    free(value);
}

void mini_pwd() {
    char cwd[PATH_MAX];
    ssize_t len;

    len = readlink("/proc/self/cwd", cwd, sizeof(cwd) - 1);
    if (len == -1) {
        mini_perror("Failed to read link");
    } else {
        cwd[len] = '\0';  // Null-terminate the string
        mini_printf(cwd);
    }
}
