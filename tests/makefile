CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -ggdb3 -pthread
# List of source files
SRCS = main.c ../sigterm.c ../cpu_list.c ../buffer.c ../reader.c ../analyzer.c buffer_test.c

# List of object files
OBJS = $(SRCS:.c=.o)

# Name of the executable
TARGET = test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile each C source file into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)