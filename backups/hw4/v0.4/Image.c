/**************************************
 * PhotoLab Version 3
 * Jigar Hira
 * EECS 22
 * Fall 2018
 **************************************/


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Image.h"


/* Get the R intensity of pixel (x, y) in image */
unsigned char GetPixelR(const IMAGE *image, unsigned int x,  unsigned int y)
{
	return image->R[x + (y * image->W)];	/* get index of pixel and return value */

}


/* Get the G intensity of pixel (x, y) in image */
unsigned char GetPixelG(const IMAGE *image, unsigned int x,  unsigned int y)
{
	return image->G[x + (y * image->W)];	/* get index of pixel and return value */

}


/* Get the B intensity of pixel (x, y) in image */
unsigned char GetPixelB(const IMAGE *image, unsigned int x,  unsigned int y)
{
	return image->B[x + (y * image->W)];	/* get index of pixel and return value */

}


/* Set the R intensity of pixel (x, y) in image to r */
void SetPixelR(IMAGE *image, unsigned int x,  unsigned int y, unsigned char r)
{
	image->R[x + (y * image->W)] = r;

}


/* Set the G intensity of pixel (x, y) in image to g */
void SetPixelG(IMAGE *image, unsigned int x,  unsigned int y, unsigned char g)
{
	image->G[x + (y * image->W)] = g;

}


/* Set the B intensity of pixel (x, y) in image to b */
void SetPixelB(IMAGE *image, unsigned int x,  unsigned int y, unsigned char b)
{
	image->B[x + (y * image->W)] = b;

}


/* Allocate dynamic memory for the image structure and its R/G/B values */
/* Return the pointer to the image, or NULL in case of error */
IMAGE *CreateImage(unsigned int Width, unsigned int Height)
{
	IMAGE *image = NULL;		/* Creates an image pointer for a new image */
	unsigned char *r = NULL;	/* pointers for RGB channels */
	unsigned char *g = NULL;
	unsigned char *b = NULL;

	image = malloc(sizeof(IMAGE));
	
	if (!image)			/* Check if memory was allocated */
	{
		perror("Out of memory - ABORT\n");
		exit(42);
	}
	
	r = malloc(Width * Height * sizeof(unsigned char));	/* Allocate memory for char array */
	g = malloc(Width * Height * sizeof(unsigned char));	/* Allocate memory for char array */
	b = malloc(Width * Height * sizeof(unsigned char));	/* Allocate memory for char array */

	if (!r || !g || !b)		/* Check if memory was allocated */
	{
		perror("Out of memory - ABORT\n");
		exit(42);
	}

	image->W = Width;
	image->H = Height;

	image->R = r;	/* assign the pointers to the image */
	image->G = g;
	image->B = b;
	
	return image;

}


/* Free the memory for the R/G/B values and IMAGE structure */
void DeleteImage(IMAGE *image)
{
	/* Check if the pointer exists, free memory, and set pointer to null */
	
	assert(image->R);
	free(image->R);
	image->R = NULL;

	assert(image->G);
	free(image->G);
	image->G = NULL;

	assert(image->B);
	free(image->B);
	image->B = NULL;

	assert(image);	
	free(image);
	image = NULL;
	
}


/* Return the image's width in pixels */
unsigned int ImageWidth(const IMAGE *image)
{
	return image->W;
}


/* Return the image's height in pixels */
unsigned int ImageHeight(const IMAGE *image)
{
	return image->H;
}


/* EOF */
