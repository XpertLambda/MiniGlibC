CC = gcc
CFLAGS = -Wall -g -Iinclude
TARGET = main
SRCS = main.c mini_io.c mini_string.c mini_memory.c
OBJS = $(SRCS:.c=.o)
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) test.txt

.PHONY: clean all

