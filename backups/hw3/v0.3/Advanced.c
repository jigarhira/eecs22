/*******************************************
 * Advanced DIP functions
 * 
 * Assignment 3
 * Jigar Hira
 * EECS 22
 * *****************************************/


#include <math.h>

#include "Advanced.h"


/* Limits the image to the range [0, 255] */
int FixValue(int value)
{
	if (value > 255)	/* Checks if the value is too high */
	{
		value = 255;
	}
	else if (value < 0)	/* Checks if the value is too low */
	{
		value = 0;
	}
	
	return value;
}


/* Set brightness of an image */
void Brightness(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int brightness)
{
	/* Iterate thorugh all the pixels */
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			/* Adds the brightness value to each pixel value and ensures the value remains from [0, 255] */
			R[i][j] = (unsigned char) FixValue(((int) R[i][j]) + brightness);
			G[i][j] = (unsigned char) FixValue(((int) G[i][j]) + brightness);
			B[i][j] = (unsigned char) FixValue(((int) B[i][j]) + brightness);

		}
	}
}


/* Horizontally Mirror an image */
void HMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	/* Iterate through half of the pixels */
	for (int i = 0; i < (WIDTH / 2); i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			/* Maps each pixel from the left side to the mirrored index on the right side */
			R[(WIDTH - 1) - i][j] = R[i][j]; 
			G[(WIDTH - 1) - i][j] = G[i][j]; 
			B[(WIDTH - 1) - i][j] = B[i][j]; 

		}
	}
}


/* Performs a Hue rotation on the image */
void HueRotate(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], float angle)
{
	float R_norm, G_norm, B_norm;	/* normalized values of R, G, B */
	float Y, I, Q;			/* Color wheel values */

	/* Iterate through all the pixels in the image */
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			/* Normalizes the R, G, B */
			R_norm = R[i][j] / (float) 255;
			G_norm = G[i][j] / (float) 255;
			B_norm = B[i][j] / (float) 255;

			/* Convert the RGB values to color wheel values*/
			Y = (0.299 * R_norm) + (0.587 * G_norm) + (0.114 * B_norm);
			I = (0.596 * R_norm) + (-0.274 * G_norm) + (-0.321 * B_norm);
			Q = (0.211 * R_norm) + (-0.523 * G_norm) + (0.311 * B_norm);

			/* Apply rotation transformation */
			I = (I * cos(angle)) - (Q * sin(angle));
			Q = (I * sin(angle)) + (Q * cos(angle));

			/* Convert color wheel values back to RGB */
			R_norm = (Y) + (0.956 * I) + (0.621 * Q);
			G_norm = (Y) + (-0.272 * I) + (-0.647 * Q);
			B_norm = (Y) + (-1.107 * I) + (1.705 * Q);
			
			/* Denormalize the RGB values */
			/* First multiplies value by 255f and then casts as int (no longer needs decimal precision) */
			/* Then uses FixValue() to ensure the pixel values are from [0, 255] */
			R[i][j] = (unsigned char) FixValue((int) (R_norm * (float) 255));
			G[i][j] = (unsigned char) FixValue((int) (G_norm * (float) 255));
			B[i][j] = (unsigned char) FixValue((int) (B_norm * (float) 255));

		}
	}
}



/* EOF */
