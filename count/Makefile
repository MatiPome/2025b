CC = gcc
CFLAGS = -Wall -pedantic -ansi

OBJS = main.o module.o
TARGET = module

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)