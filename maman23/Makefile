CC = gcc
CFLAGS = -ansi -pedantic -Wall -Wextra -g
TARGET = numbers
OBJS = numbers.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

numbers.o: numbers.c

clean:
	rm -f $(TARGET) $(OBJS)
