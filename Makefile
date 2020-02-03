CC = gcc

all: main.o
	$(CC) -o picMaker main.o -lm

main.o: main.c
	$(CC) -c main.c -lm

run: picMaker
	./picMaker 300
