CC = gcc
CFLAGS = -Wall -Wextra -pedantic -ansi
TARGET = palindrome
SRCS = main.c palindrome.c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)