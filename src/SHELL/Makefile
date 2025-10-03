# Compiler
CC = gcc

# Compilation flags
CFLAGS = -Wall -Wextra -std=c99 -pedantic -g

# Source files
COMMON_SRC = mini_shell.c ../*.c
PROGRAMS = mini_touch mini_cp mini_cat mini_head mini_tail mini_clean mini_wc \
           mini_echo mini_grep mini_ls mini_chmod mini_mkdir mini_mv mini_rm \
           mini_rmdir mini_quickdiff mini_cd mini_env mini_getenv mini_pwd \
           SHELL

# Compilation rule
all: $(PROGRAMS)

%: %.c $(COMMON_SRC)
	$(CC) $(CFLAGS) $< $(COMMON_SRC) -o $@
	@echo "$@ compiled successfully."

# Test rule
test: all
	@echo "Running basic tests..."
	@echo "Testing mini_echo..."
	@./mini_echo "Test successful"
	@echo "Testing mini_pwd..."
	@./mini_pwd
	@echo "Testing file operations..."
	@echo "test content" > test_file.txt
	@./mini_cat test_file.txt
	@./mini_wc test_file.txt
	@rm -f test_file.txt
	@echo "All tests passed!"

# Clean rule
clean:
	rm -f $(PROGRAMS) test_file.txt
	@echo "All compiled files removed."
