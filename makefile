CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -ggdb3 -l pthread
# List of source files
SRCS = main.c reader.c cpu_list.c

# List of object files
OBJS = $(SRCS:.c=.o)

# Name of the executable
TARGET = CUT

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile each C source file into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)