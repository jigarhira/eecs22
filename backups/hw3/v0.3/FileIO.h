/*******************************************
 * File reading and writing functions
 * 
 * Assignment 3
 * Jigar Hira
 * EECS 22
 * *****************************************/


#ifndef _FileIO_
#define _FileIO_

#include "Constants.h"


/* load image from a file */
int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* save a processed image */
int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);


#endif

/* EOF */
