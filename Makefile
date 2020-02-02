CC = gcc

all: main.o
	$(CC) -lm -o picMaker main.o

main.o: main.c
	$(CC) -lm -c main.c

run: picMaker
	./picMaker