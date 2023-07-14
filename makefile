CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g -std=c99 -ggdb3 -pthread
# CC = clang
# CFLAGS = -Weverything -std=c99 -ggdb3 -pthread -Wno-disabled-macro-expansion -Wno-declaration-after-statement
# List of source files
SRCS = sigterm.c main.c cpu_stat_list.c cpu_stat_buffer.c cpu_usage_list.c cpu_usage_buffer.c reader.c analyzer.c printer.c
TEST_SRCS = tests/test_runner.c tests/cpu_stat_buffer_test.c tests/analyzer_test.c

# List of object files
OBJS = $(SRCS:.c=.o)
TEST_OBJS = $(TEST_SRCS:.c=.o)

# Name of the executable
TARGET = CUT
TEST_TARGET = tests/test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(TEST_TARGET): $(TEST_OBJS) $(filter-out main.o,$(OBJS))
	$(CC) $(CFLAGS) -o $@ $^

# Compile each C source file into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

tests/%.o: tests/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(TEST_OBJS) $(TEST_TARGET)