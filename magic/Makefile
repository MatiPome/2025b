CC = gcc
CFLAGS = -Wall -ansi -pedantic
TARGET = magic
OBJS = main.o input.o magic.o output.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c input.h magic.h output.h
	$(CC) $(CFLAGS) -c main.c

input.o: input.c input.h magic.h
	$(CC) $(CFLAGS) -c input.c

magic.o: magic.c magic.h input.h
	$(CC) $(CFLAGS) -c magic.c

output.o: output.c output.h input.h magic.h
	$(CC) $(CFLAGS) -c output.c

clean:
	rm -f *.o $(TARGET)