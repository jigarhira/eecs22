# Makefile for sqrt program

# variable declaration
CC = gcc
CFLAGS = -c -ansi -std=c99 -Wall -g
LFLAGS = -Wall

all: Main

clean:
	rm *.o		# removes all object files

Main.o: Main.c
	$(CC) $(CFLAGS) Main.c -o Main.o

sqrt.o: sqrt.c sqrt.h
	$(CC) $(CFLAGS) sqrt.c -o sqrt.o

Main: Main.o sqrt.o
	$(CC) $(LFLAGS) Main.o sqrt.o -o SquareRoot


