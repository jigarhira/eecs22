/*******************************************
 * Header for original DIP functions
 * 
 * Assignment 3
 * Jigar Hira
 * EECS 22
 * *****************************************/

#ifndef _DIPs_
#define _DIPs_

#include "Constants.h"


/* edge detection */
void Edge(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* change color image to black & white */
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* shuffle the image */
void Shuffle(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);



#endif

/* EOF */
