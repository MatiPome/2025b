# Compiler and flags
CC = gcc
CFLAGS = -Wall -pedantic -ansi  # Strict ISO C90, show all warnings

# Object files and final binary name
OBJS = main.o module.o
TARGET = module

# Default target: link object files into final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile each .c source into a .o object
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f *.o $(TARGET)