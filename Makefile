CC = gcc

all: main.o
	$(CC) -o picMaker main.o 

main.o:
	$(CC) -c main.c
