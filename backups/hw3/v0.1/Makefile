# Makefile: PhotoLab2
#
# Assignment 3
# Jigar Hira
# EECS 22


# variable definitions
CC = gcc
DEBUG = -g -DDEBUG
CFLAGS = -c -ansi -std=c99 -Wall $(DEBUG)
LFLAGS = -Wall $(DEBUG)


# default target
all: PhotoLab

# clean
clean:
	rm *.o

FileIO.o: FileIO.c FileIO.h Constants.h
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o

DIPs.o: DIPs.c DIPs.h Constants.h
	$(CC) $(CFLAGS) DIPs.c -o DIPs.o

PhotoLab.o: PhotoLab.c Constants.h
	$(CC) $(CFLAGS) PhotoLab.c -o PhotoLab.o

PhotoLab: PhotoLab.o FileIO.o DIPs.o
	$(CC) $(LFLAGS) PhotoLab.o FileIO.o DIPs.o -o PhotoLab

