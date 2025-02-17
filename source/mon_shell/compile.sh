#!/bin/bash

# List of file1 programs to compile
files=("mini_touch" "mini_cp" "mini_cat" "mini_head" "mini_tail" "mini_clean" "mini_wc" "mini_echo" "mini_grep" "mini_ls" "mini_chmod" "mini_mkdir" "mini_mv" "mini_rm" "mini_rmdir" "mini_quickdiff" "mini_cd" "mini_env" "mini_getenv" "mini_pwd")

# Loop through the list and compile each one
for file in "${files[@]}"; do
    echo "Compiling $file.c with mini_shell.c ../*.c"
    gcc "$file.c" ../*.c mini_shell.c -o "$file"
    if [ $? -eq 0 ]; then
        echo "$file compiled successfully."
    else
        echo "Failed to compile $file."
    fi
done
