CC = gcc
CFLAGS = -std=c90 -Wall -Wextra -pedantic
OBJS = mainmat.o mymat.o
TARGET = mainmat

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

mainmat.o: mainmat.c mymat.h
mymat.o: mymat.c mymat.h

clean:
	rm -f $(OBJS) $(TARGET)