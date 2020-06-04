/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2018                     */
/*                                                                   */
/* Author: Jordan Bonecutter                                         */
/*                                                                   */
/* IterativeFilter.c: file for iterative filters                     */
/*                                                                   */
/*********************************************************************/

#include <assert.h>

#include "IterativeFilter.h"

/* turns image to a movie */
MOVIE *doIterativeFilter(IMAGE *image, iterableFilter filter, float start, float end, float change)
{	
	/* check that there is an image */
	assert(image);

	/* check for correct bounds */
	if (!(start < end))
	{
		return NULL;
	}
	
	IMAGE *newImage = NULL;	/* IMAGE struct to store the image after it is transformed */

	/* create the movie */
	MOVIE *movie = NULL;
	movie = CreateMovie();
	movie->Frames = CreateImageList();	/* create a list to store all the frames */

	/* Step through all of the values including the end */
	float i;
	for (i = start; i <= end; i += change);
	{
		newImage = CopyImage(image);	/* make a copy of the image */
		newImage = filter(newImage, i);	/* apply the filter and update the image */

		/* Add the image to the list */
		AppendRGBImage(movie->Frames, newImage);
	}

	return movie;
}
