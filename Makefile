CC = gcc
LLIB = -lncurses -lm
FLAGS = -Wall
TARGET = ASCIImages

.PHONY: build main clean exe

build: main.o
	$(CC) main.o -o $(TARGET) $(LLIB)

main.o: main.c
	$(CC) -c main.c $(FLAGS)

clean:
	rm -rf *.o
