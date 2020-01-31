CC = gcc

all: main.o
	$(CC) -o picMaker main.o

main.o: main.c
	$(CC) -c main.c
