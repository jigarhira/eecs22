# Makefile: PhotoLab2
#
# Assignment 3
# Jigar Hira
# EECS 22


# variable definitions
CC = gcc
DEBUG = -g -DDEBUG
LIB = -lm
CFLAGS = -c -ansi -std=c99 -Wall
LFLAGS = -Wall $(LIB)


# default target
all: PhotoLab PhotoLabTest

# clean
clean:
	rm *.o		# Removes all the object files
	rm PhotoLab	# Removes the PhotoLab binary file
	find . -maxdepth 1 \( -name '*.ppm' -a ! \( -name 'HSSOE.ppm' \) \) -type f -exec rm {} +	# Removes all .ppm files except for HSSOE.ppm

FileIO.o: FileIO.c FileIO.h Constants.h
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o

DIPs.o: DIPs.c DIPs.h Constants.h
	$(CC) $(CFLAGS) DIPs.c -o DIPs.o

Advanced.o: Advanced.c Advanced.h Constants.h
	$(CC) $(CFLAGS) Advanced.c -o Advanced.o

PhotoLab.o: PhotoLab.c Constants.h
	$(CC) $(CFLAGS) PhotoLab.c -o PhotoLab.o

PhotoLabTest.o: PhotoLab.c Constants.h
	$(CC) $(CFLAGS) $(DEBUG) PhotoLab.c -o PhotoLabTest.o

PhotoLab: PhotoLab.o FileIO.o DIPs.o Advanced.o
	$(CC) $(LFLAGS) PhotoLab.o FileIO.o DIPs.o Advanced.o -o PhotoLab

PhotoLabTest: PhotoLabTest.o FileIO.o DIPs.o Advanced.o
	$(CC) $(LFLAGS)	PhotoLabTest.o FileIO.o DIPs.o Advanced.o -o PhotoLabTest

