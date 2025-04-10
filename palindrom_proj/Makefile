# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -ansi  # Strict warnings, ISO C90

# Target binary name
TARGET = palindrome

# Source and object files
SRCS = main.c palindrome.c
OBJS = $(SRCS:.c=.o)

# Default target: link all object files into final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile each .c file into a .o file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Remove all build artifacts
clean:
	rm -f *.o $(TARGET)