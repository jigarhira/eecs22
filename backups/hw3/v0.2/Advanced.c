/*******************************************
 * Advanced DIP functions
 * 
 * Assignment 3
 * Jigar Hira
 * EECS 22
 * *****************************************/


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

}


/* Performs a Hue rotation on the image */
void HueRotate(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], float angle)
{

}



/* EOF */
