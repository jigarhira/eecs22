# Makefile for hw4, EECS22 Fall 2017 fall 
# Author: Huan Chen
# Modified by: Mihnea Chirila
# Modification: Ali Nickparsa 11/11/2018
# Date:   11/01/2017
CC     = gcc
DEBUG  = -g -DDEBUG
CFLAGS = -ansi -std=c99 -Wall -c
LFLAGS = -Wall

OBJS = MovieLab.o Image.o FileIO.o DIPs.o ImageList.o IterativeFilter.o Movie.o MovieIO.o
DEBUG_OBJS = MovieLab_DEBUG.o Image_DEBUG.o FileIO_DEBUG.o DIPs_DEBUG.o ImageList_DEBUG.o IterativeFilter_DEBUG.o Movie_DEBUG.o MovieIO_DEBUG.o
DEPS = Image.h FileIO.h DIPs.h ImageList.h IterativeFilter.h Movie.h MovieIO.h Constants.h

DESIGN = MovieLab MovieLab_DEBUG

all: $(DESIGN)

clean:
	rm *.o $(DESIGN)



#BINARIES

MovieLab: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -lm -o MovieLab

MovieLab_DEBUG: $(DEBUG_OBJS)
	$(CC) $(LFLAGS)  $(DEBUG_OBJS) -lm -o MovieLab_DEBUG



#OBJECTS

MovieLab.o: MovieLab.c $(DEPS)
	$(CC) $(CFLAGS) MovieLab.c -o MovieLab.o

FileIO.o: FileIO.c FileIO.h Image.h
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o

DIPs.o: DIPs.c DIPs.h Image.h
	$(CC) $(CFLAGS) DIPs.c -o DIPs.o

ImageList.o: ImageList.c ImageList.h Image.h
	$(CC) $(CFLAGS) ImageList.c -lm -o ImageList.o

Image.o: Image.c Image.h
	$(CC) $(CFLAGS) Image.c -o Image.o

Movie.o: Movie.c Movie.h ImageList.h
	$(CC) $(CFLAGS) Movie.c -o Movie.o

IterativeFilter.o: IterativeFilter.c IterativeFilter.h Movie.h
	$(CC) $(CFLAGS) IterativeFilter.c -o IterativeFilter.o

MovieIO.o: MovieIO.c MovieIO.h Movie.h
	$(CC) $(CFLAGS) MovieIO.c -o MovieIO.o



#DEBUG OBJECTS

MovieLab_DEBUG.o: MovieLab.c $(DEPS)
	$(CC) $(CFLAGS) $(DEBUG) MovieLab.c -o MovieLab_DEBUG.o

FileIO_DEBUG.o: FileIO.c FileIO.h Image.h
	$(CC) $(CFLAGS) $(DEBUG) FileIO.c -o FileIO_DEBUG.o

DIPs_DEBUG.o: DIPs.c DIPs.h Image.h
	$(CC) $(CFLAGS) $(DEBUG) DIPs.c -o DIPs_DEBUG.o

ImageList_DEBUG.o: ImageList.c ImageList.h Image.h
	$(CC) $(CFLAGS) $(DEBUG) ImageList.c -lm -o ImageList_DEBUG.o

Image_DEBUG.o: Image.c Image.h
	$(CC) $(CFLAGS) $(DEBUG) Image.c -o Image_DEBUG.o

Movie_DEBUG.o: Movie.c Movie.h ImageList.h
	$(CC) $(CFLAGS) $(DEBUG) Movie.c -o Movie_DEBUG.o

IterativeFilter_DEBUG.o: IterativeFilter.c IterativeFilter.h Movie.h
	$(CC) $(CFLAGS) $(DEBUG) IterativeFilter.c -o IterativeFilter_DEBUG.o

MovieIO_DEBUG.o: MovieIO.c MovieIO.h Movie.h
	$(CC) $(CFLAGS) $(DEBUG) MovieIO.c -o MovieIO_DEBUG.o


