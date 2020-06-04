/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* Movie.c: source file for basic movie manipulations                */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "Movie.h"

/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
MOVIE *CreateMovie(void)
{
	MOVIE *movie = NULL;
	
	movie = malloc(sizeof(MOVIE));	/* Allocate memotry for movie structure */

	/* Check if memory was allocated */
	if (!movie)
	{
		return NULL;
	}

	movie->Frames = NULL;

	return movie;
}

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie)
{
	assert(movie);
	
	free(movie->Frames);
	free(movie);
}

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie)
{
	int entities;		/* frame count */
	IENTRY *current = NULL;	/* current frame */
	YUVIMAGE *yuv = NULL;	/* YUV image */
	IMAGE *rgb = NULL;	/* new RGB image */
	
	int C, D, E;		/* Values for conversion calculation */

	
	entities= movie->Frames->Length;	/* Get the number of frames */

	current = movie->Frames->First;		/* Start at the first frame */

	/* iterate through all the frames */
	while(entities > 0)
	{
		yuv = current->YUVImage;	/* pointer to the yuv image */
		assert(yuv);			/* check that the yuv image exists */

		rgb = CreateImage(yuv->Width, yuv->Height);	/* create a new rgb image of the same resolution */

		/* iterate through all the pixels in the frame */
		for (i = 0; i < yuv->Width; i++)
		{
			for (j = 0; j < yuv->Height; j++)
			{
				/* Convert YUV to RGB */
				C = GetPixelY(yuv, i, j) - 16;
				D = GetPixelU(yuv, i, j) - 128;
				E = GetPixelV(yuv, i, j) - 128;

				SetPixelR(rgb, i, j, clip(((298 * C) + (409 * E) + 128) << 8));
				SetPixelG(rgb, i, j, clip(((298 * C) - (100 * D) - (208 * E) + 128) << 8));
				SetPixelB(rgb, i, j, clip(((298 * C) + (516 * D) + 128) << 8));
		
			}
		}

		DeleteYUVImage(yuv);		/* delete the original yuv image */
		current->YUVImage = NULL;	/* remove the yuv image pointer from the frame */
		current->RGBImage = rgb		/* add the rgb image to the frame */

	}

}

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(MOVIE *movie)
{

}

int MovieLength(const MOVIE *movie)
{
	return movie->Frames->Length;	/* Return the length of the image list */
}


int MovieHeight(const MOVIE *movie)
{
	/* Checks if the image is RGB or YUV format */
	if (movie->Frames->First->RGBImage)
	{
		return movie->Frames->First->RGBImage->Height;
	}
	else
	{
		return movie->Frames->First->YUVImage->Height;
	}
}

int MovieWidth(const MOVIE *movie)
{
	/* Checks if the image is RGB or YUV format */
	if (movie->Frames->First->RGBImage)
	{
		return movie->Frames->First->RGBImage->Width;
	}
	else
	{
		return movie->Frames->First->YUVImage->Width;
	}
}

/* EOF */
