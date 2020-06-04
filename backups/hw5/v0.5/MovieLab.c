/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/* Modified by Mihnea Chirila for EECS 22 Fall 2018                                                            */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* MovieLab.c: source file for the main function                     */
/*                                                                   */
/* Please use this template for your HW5.                            */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileIO.h"
#include "DIPs.h"
#include "Movie.h"
#include "Constants.h"
#include "Image.h"
#include "MovieIO.h"
#include "IterativeFilter.h"

int main(int argc, char *argv[])
{

	int inputType;		/* type of input: 0=image, 1=movie */
	char *inputFName;	/* file name of the input */
	char *outputFName;	/* file name of the output */
	float start, end, step;	/* parameters for creating movie from image */
	int filterType;		/* type of filter: 0=hue, 1=saturation, 2=reverse */
	int frames;		/* number of frames */
	int width, height;	/* width and hieght */


	/* iterate through all the command line arguments */
	int i;
	for (i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-i") == 0)
		{
			i++;
			inputType = 0;	/* set the input type to image */
			if (i < argc) /* make sure there is an argument after the command */
			{
				inputFName = argv[i]; 	/* set the input file name */
			}
			else
			{
				printf("%s", "ERROR | No input image file given!\n");
				exit(0);
			}

		}
		if (strcmp(argv[i], "-m") == 0)
		{
			i++;
			inputType = 1;	/* set the input type to movie */
			if (i < argc) /* make sure there is an argument after the command */
			{
				inputFName = argv[i]; 	/* set the input file name */
			}
			else
			{
				printf("%s", "ERROR | No input movie file given!\n");
				exit(0);
			}

		}
		if (strcmp(argv[i], "-o") == 0)
		{
			i++;
			if (i < argc)	/* make sure there is an argument after the command */
			{
				outputFName = argv[i];
			}
			else
			{
				printf("%s", "ERROR | No output file name given!");
				exit(0);
			}
			
		}
		if (strcmp(argv[i], "-start=") == 0)
		{
			i++;
			if (i < argc)	/* make sure there is an argument after the command */
			{
				start = atof(argv[i]);
			}
			else
			{
				printf("%s", "ERROR | No start value given!");
				exit(0);
			}
		}
		if (strcmp(argv[i], "-end=") == 0)
		{
			i++;
			if (i < argc)	/* make sure there is an argument after the command */
			{
				end = atof(argv[i]);
			}
			else
			{
				printf("%s", "ERROR | No end value given!");
				exit(0);
			}
	
		}
		if (strcmp(argv[i], "-step=") == 0)
		{
			i++;
			if (i < argc)	/* make sure there is an argument after the command */
			{
				step = atof(argv[i]);
			}
			else
			{
				printf("%s", "ERROR | No step value given!");
				exit(0);
			}
	
		}
		if (strcmp(argv[i], "-hue") == 0)
		{
			filterType = 0;	/* set filter to hue rotation */

		}
		if (strcmp(argv[i], "-saturate") == 0)
		{
			filterType = 1;	/* set filter to saturation */
	
		}
		if (strcmp(argv[i], "-f") == 0)
		{
			i++;
			if (i < argc)	/* make sure there is an argument after the command */
			{
				frames = atoi(argv[i]);
			}
			else
			{
				printf("%s", "ERROR | No frames value given!");
				exit(0);
			}
	
		}
		if (strcmp(argv[i], "-s") == 0)
		{
			char *token;	/* token character pointer */

			i++;
			if (i < argc)	/* make sure there is an argument after the command */
			{
				token = strtok(argv[i], "x,X");	/* tokenize the resultion */
				width = atoi(token);		/* save the width */
				token = strtok(NULL, "x,X");	/* iterate to the next token */
				height = atoi(token);		/* save the height */
			}
			else
			{
				printf("%s", "ERROR | No resolution given!");
				exit(0);
			}
	
		}
		if (strcmp(argv[i], "-reverse") == 0)
		{
			filterType = 2;	/* set filter to reverse */
		}

	}

	/* Begin processing */
	if (inputType == 0)	/* Turn image to movie */
	{
		IMAGE *image = NULL;		/* orignal image pointer */
		MOVIE *movie = NULL;		/* movie result */
		iterableFilter filter = NULL;	/* filter function pointer */

		image = LoadImage(inputFName);	/* loads image from file */

		/* set the function pointer for the filter */
		if (filterType == 0)
		{
			filter = &HueRotate;
		}
		else if (filterType == 1)
		{
			/* filter = &Saturate */;	
		}

		/* Generate the movie structure */
		movie = doIterativeFilter(image, filter, start, end, step);

		/* Convert the RGB images in the movie to YUV */
		RGB2YUVMovie(movie);

		if (SaveMovie(outputFName, movie))
		{
			printf("%s", "ERROR | Unable to save movie to file!");
		}

		/* delete the image and movie */
		DeleteImage(image);
		DeleteMovie(movie);


	}
	else if (inputType == 1)	/* Perform filter on movie */
	{
		MOVIE *movie = NULL;	/* original movie */
		
		/* loads the original movie from file */
		movie = LoadMovie(outputFName, frames, width, height);

		if (filterType == 2)
		{
			/* reverse the frame list */
			ReverseImageList(movie->Frames);

		}

		/* Save Movie */
		if (SaveMovie(outputFName, movie))
		{
			printf("%s", "ERROR | Unable to save movie to file!");
		}

		/* delete the movie */
		DeleteMovie(movie);


	}


}

/* EOF */
