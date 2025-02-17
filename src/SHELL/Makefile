# Compiler
CC = gcc

# Source files
COMMON_SRC = mini_shell.c ../*.c
PROGRAMS = mini_touch mini_cp mini_cat mini_head mini_tail mini_clean mini_wc \
           mini_echo mini_grep mini_ls mini_chmod mini_mkdir mini_mv mini_rm \
           mini_rmdir mini_quickdiff mini_cd mini_env mini_getenv mini_pwd \
           SHELL

# Compilation rule
all: $(PROGRAMS)

%: %.c $(COMMON_SRC)
	$(CC) $< $(COMMON_SRC) -o $@
	@echo "$@ compiled successfully."

# Clean rule
clean:
	rm -f $(PROGRAMS)
	@echo "All compiled files removed."
