CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -ggdb3 -pthread
# List of source files
SRCS = main.c ../sigterm.c ../cpu_stat_list.c ../cpu_stat_buffer.c ../cpu_usage_list.c ../cpu_usage_buffer.c ../reader.c ../analyzer.c cpu_stat_buffer_test.c

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