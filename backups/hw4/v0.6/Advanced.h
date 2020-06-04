#ifndef ADVANCED_H_INCLUDED_
#define ADVANCED_H_INCLUDED_

#include "Constants.h"
#include "Image.h"

/* Adjust the brightness of an image */
IMAGE *Brightness(IMAGE *image, int brightness);

/* Mirror an image horizontally */
IMAGE *HMirror(IMAGE *image);

void matrix_3_3multiplyVector_3(float vector[3], const float matrix[3][3]);

IMAGE *HueRotate(IMAGE *image, float angle);


/* New DIP Operations */

/* Rotate or Flip an image */
IMAGE *Rotate(IMAGE *image, int option);

/* Fix the bounds of a value*/
int FixBounds(int value);

/* Resize an image */
IMAGE *Resize(IMAGE *image, int percentage);

/* Adjust the saturation of an image */
IMAGE *Saturate(IMAGE *image, float percent);



#endif /* ADVANCED_H_INCLUDED_ */

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
