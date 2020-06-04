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
	ILIST *frames = NULL;
	
	movie = malloc(sizeof(MOVIE));	/* Allocate memory for movie structure */

	/* Check if memory was allocated */
	if (!movie)
	{
		return NULL;
	}

	frames = CreateImageList();	/* Allocate memory for frame list */

	if (!frames)
	{
		return NULL;
	}

	movie->Frames = frames;

	return movie;
}

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie)
{
	assert(movie);

	
	DeleteImageList(movie->Frames);	
	movie->Frames = NULL;

	free(movie);
	movie = NULL;
}

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie)
{
	int entities;		/* frame count */
	IENTRY *current = NULL;	/* current frame */
	YUVIMAGE *yuv = NULL;	/* YUV image */
	IMAGE *rgb = NULL;	/* new RGB image */
	
	int C, D, E;		/* Values for conversion calculation */

	
	entities= movie->Frames->length;	/* Get the number of frames */

	current = movie->Frames->First;		/* Start at the first frame */

	/* iterate through all the frames */
	while(entities > 0)
	{
		yuv = current->YUVImage;	/* pointer to the yuv image */
		assert(yuv);			/* check that the yuv image exists */

		rgb = CreateImage(yuv->W, yuv->H);	/* create a new rgb image of the same resolution */

		/* iterate through all the pixels in the frame */
		int i, j;		
		for (i = 0; i < yuv->W; i++)
		{
			for (j = 0; j < yuv->H; j++)
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
		current->RGBImage = rgb;	/* add the rgb image to the frame */

	}

}

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(MOVIE *movie)
{
	int entities;		/* frame count */
	IENTRY *current = NULL;	/* current frame */
	YUVIMAGE *yuv = NULL;	/* new YUV image */
	IMAGE *rgb = NULL;	/* RGB image */
	
	int R, G, B;		/* RGB values */
		
	entities= movie->Frames->length;	/* Get the number of frames */

	current = movie->Frames->First;		/* Start at the first frame */

	/* iterate through all the frames */
	while(entities > 0)
	{
		rgb = current->RGBImage;	/* pointer to the original rgb image */
		assert(rgb);			/* check that the yuv image exists */

		yuv = CreateYUVImage(rgb->W, rgb->H);	/* create a new rgb image of the same resolution */

		/* iterate through all the pixels in the frame */
		int i, j;
		for (i = 0; i < rgb->W; i++)
		{
			for (j = 0; j < rgb->H; j++)
			{
				/* Convert RGB to YUV */
				R = GetPixelR(rgb, i, j);
				G = GetPixelG(rgb, i, j);
				B = GetPixelB(rgb, i, j);

				SetPixelY(yuv, i, j, clip(((((66 * R) + (129 * G) + (25 * B)) + 128) >> 8) + 16));
				SetPixelU(yuv, i, j, clip(((((-38 * R) + (-74 * G) + (112 * B)) + 128) >> 8) + 128));
				SetPixelV(yuv, i, j, clip(((((112 * R) + (-94 * G) + (-18 * B)) + 128) >> 8) + 128));

			}
		}

		DeleteImage(rgb);		/* delete the original rgb image */
		current->YUVImage = yuv;	/* remove the yuv image pointer from the frame */
		current->RGBImage = NULL;	/* add the rgb image to the frame */

		current = current->Next;	/* move on to the next entry */

		entities--;

	}

}

int MovieLength(const MOVIE *movie)
{
	return movie->Frames->length;	/* Return the length of the image list */
}


int MovieHeight(const MOVIE *movie)
{
	/* Checks if the image is RGB or YUV format */
	if (movie->Frames->First->RGBImage)
	{
		return movie->Frames->First->RGBImage->H;
	}
	else
	{
		return movie->Frames->First->YUVImage->H;
	}
}

int MovieWidth(const MOVIE *movie)
{
	/* Checks if the image is RGB or YUV format */
	if (movie->Frames->First->RGBImage)
	{
		return movie->Frames->First->RGBImage->W;
	}
	else
	{
		return movie->Frames->First->YUVImage->W;
	}
}

/* EOF */
