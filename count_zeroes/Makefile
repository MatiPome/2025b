# Compiler and flags
CC = gcc                   # Compiler to use: gcc (GNU Compiler Collection)
CFLAGS = -Wall -pedantic -ansi  # CFLAGS:
                               # -Wall: Enable all warnings
                               # -pedantic: Enforce strict compliance to ISO C90 standard
                               # -ansi: Use the ANSI C standard (C90)

# Object files and final binary name
OBJS = main.o module.o     # List of object files to be linked into the final executable
TARGET = module            # The name of the final executable (output binary)

# Default target: link object files into final executable
$(TARGET): $(OBJS)         # The target is the final executable 'module', which depends on 'main.o' and 'module.o'
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)  # Compile the object files into the final binary using gcc

# Compile each .c source into a .o object
%.o: %.c                    # Pattern rule to compile .c files into .o object files
	$(CC) $(CFLAGS) -c $< -o $@  # Compile source file ($<) into object file ($@)

# Clean build artifacts
clean:
	rm -f *.o $(TARGET)      # Remove all object files (*.o) and the final binary (module)
