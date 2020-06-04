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
	rm *.o		# Removes all the object files

FileIO.o: FileIO.c FileIO.h Constants.h
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o

DIPs.o: DIPs.c DIPs.h Constants.h
	$(CC) $(CFLAGS) DIPs.c -o DIPs.o

Advanced.o: Advanced.c Advanced.h Constants.h
	$(CC) $(CFLAGS) Advanced.c -o Advanced.o

PhotoLab.o: PhotoLab.c Constants.h
	$(CC) $(CFLAGS) PhotoLab.c -o PhotoLab.o

PhotoLab: PhotoLab.o FileIO.o DIPs.o Advanced.o
	$(CC) $(LFLAGS) PhotoLab.o FileIO.o DIPs.o Advanced.o -o PhotoLab

