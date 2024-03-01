CC=gcc
CFLAGS=-Wall 
TARGET=digitcompress

all: $(TARGET)

$(TARGET): compress.o encodemain.o
	$(CC) $(CFLAGS) -o $(TARGET) compress.o encodemain.o

compress.o: compress.c compress.h
	$(CC) $(CFLAGS) -c compress.c

encodemain.o: encodemain.c compress.h
	$(CC) $(CFLAGS) -c encodemain.c

clean:
	rm -f $(TARGET) *.o
