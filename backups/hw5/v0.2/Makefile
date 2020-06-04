# Makefile for hw4, EECS22 Fall 2017 fall 
# Author: Huan Chen
# Modified by: Mihnea Chirila
# Modification: Ali Nickparsa 11/11/2018
# Date:   11/01/2017
CC     = gcc
DEBUG  = -g -DDEBUG
CFLAGS = -ansi -Wall -c
LFLAGS = -Wall

OBJS = PhotoLab.o FileIO.o Image.o Test.o
DEBUG_OBJS = PhotoLab_DEBUG.o FileIO_DEBUG.o Image_DEBUG.o Test_DEBUG.o
DEPS = Image.h FileIO.h DIPs.h Advanced.h

DESIGN = PhotoLab PhotoLabTest
all: $(DESIGN)
PhotoLab: $(OBJS) libFilter.a
	$(CC) $(LFLAGS) $(OBJS) -lm -L. -lFilter -o PhotoLab
PhotoLabTest: $(DEBUG_OBJS) libFilter.a
	$(CC) $(LFLAGS) $(DEBUG) $(DEBUG_OBJS) -lm -L. -lFilter -o PhotoLabTest

libFilter.a: DIPs.o Advanced.o
	ar rc libFilter.a Advanced.o DIPs.o
	ranlib libFilter.a

PhotoLab.o: PhotoLab.c $(DEPS)
	$(CC) $(CFLAGS) PhotoLab.c -o PhotoLab.o
FileIO.o: FileIO.c FileIO.h Image.h
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o
DIPs.o: DIPs.c DIPs.h Image.h
	$(CC) $(CFLAGS) DIPs.c -o DIPs.o
Advanced.o: Advanced.c Advanced.h Image.h
	$(CC) $(CFLAGS) Advanced.c -lm -o Advanced.o
Image.o: Image.c Image.h
	$(CC) $(CFLAGS) Image.c -o Image.o
Test.o: Test.c Test.h $(DEPS)
	$(CC) $(CFLAGS) Test.c -o Test.o

PhotoLab_DEBUG.o: PhotoLab.c $(DEPS)
	$(CC) $(CFLAGS) $(DEBUG) PhotoLab.c -o PhotoLab_DEBUG.o
FileIO_DEBUG.o: FileIO.c FileIO.h Image.h
	$(CC) $(CFLAGS) $(DEBUG) FileIO.c -o FileIO_DEBUG.o
DIPs_DEBUG.o: DIPs.c DIPs.h Image.h
	$(CC) $(CFLAGS) $(DEBUG) DIPs.c -o DIPs_DEBUG.o
Advanced_DEBUG.o: Advanced.c Advanced.h Image.h
	$(CC) $(CFLAGS) $(DEBUG) Advanced.c -lm -o Advanced_DEBUG.o
Image_DEBUG.o: Image.c Image.h
	$(CC) $(CFLAGS) $(DEBUG) Image.c -o Image_DEBUG.o
Test_DEBUG.o: Test.c Test.h $(DEPS)
	$(CC) $(CFLAGS) $(DEBUG) Test.c -o Test_DEBUG.o

clean:
	rm -f *.o *.a $(DESIGN) `find . -name '*.ppm' ! -name 'HSSOE.ppm'`
