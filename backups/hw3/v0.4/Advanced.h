/*******************************************
 * Advanced DIP functions
 * 
 * Assignment 3
 * Jigar Hira
 * EECS 22
 * *****************************************/


#ifndef _Advanced_
#define _Advanced_

#include "Constants.h"


/* Limits the image to the range [0, 255] */
int FixValue(int value);


/* Set brightness of an image */
void Brightness(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int brightness);


/* Horizontally Mirror an image */
void HMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);


/* Performs a Hue rotation on the image */
void HueRotate(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], float angle);


#endif

/* EOF */
