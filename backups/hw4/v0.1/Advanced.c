#include "Advanced.h"


#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

/* Adjust the brightness of an image */
void Brightness(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int brightness) {
	for (int i=0; i<WIDTH; i++){
		for (int j=0; j<HEIGHT; j++){
			if (R[i][j] + brightness > 255){
				R[i][j] = 255;
			}else if(R[i][j] + brightness < 0){
				R[i][j] = 0;
			}else{
				R[i][j] += brightness;
			}

			if (G[i][j] + brightness > 255){
				G[i][j] = 255;
			}else if(G[i][j] + brightness < 0){
				G[i][j] = 0;
			}else{
				G[i][j] += brightness;
			}

			if (B[i][j] + brightness > 255){
				B[i][j] = 255;
			}else if(B[i][j] + brightness < 0){
				B[i][j] = 0;
			}else{
				B[i][j] += brightness;
			}
		}
	}
}

/* Mirror an image horizontally */
void HMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {

	int x, y;
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH / 2; x++) {
					R[WIDTH-1-x][y] = R[x][y];
					G[WIDTH-1-x][y] = G[x][y];
					B[WIDTH-1-x][y] = B[x][y];
		}
	}
}

void matrix_3_3multiplyVector_3(float vector[3], const float matrix[3][3])
{
	/* Memory for result */
	float result[3] = {0, 0, 0};

	/* Perform multiplication */
	result[0] = matrix[0][0]*vector[0] + matrix[0][1]*vector[1] + matrix[0][2]*vector[2];
	result[1] = matrix[1][0]*vector[0] + matrix[1][1]*vector[1] + matrix[1][2]*vector[2];
	result[2] = matrix[2][0]*vector[0] + matrix[2][1]*vector[1] + matrix[2][2]*vector[2];

	/* Copy result into other stack's memory */
	vector[0] = result[0];
	vector[1] = result[1];
	vector[2] = result[2];
}

void HueRotate(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], float angle)
{
	/* Matrix to transform normalized
	// RGB color vector from the RGB
	// color space to the YIQ color space */
	static const float RGBtoYIQMatrix[3][3] = {{0.299,  0.587,  0.114},
								  			   {0.596, -0.274, -0.321},
								  			   {0.211, -0.523,  0.311}};

	/* Matrix to transform normalized
	// YIQ color vector from the YIQ
	// color space to the RGB color space */
	static const float YIQtoRGBMatrix[3][3] = {{1.000,  0.956,  0.621},
								  			   {1.000, -0.272, -0.647},
								  			   {1.000, -1.107,  1.705}};

	const float cs = cos(angle), ss = sin(angle);

	/* Matrix to perform a hue
	// rotation on a normalized
	// YIQ color vector*/
	const float XYPlaneVectorRotateMatrix[3][3] = {{1.000, 0.000, 0.000},
												   {0.000, cs, -ss},
												   {0.000, ss, cs}};

	/* Image variables */
	float temp[3];

	for(unsigned int i = 0; i < WIDTH; i++)
	{
		for(unsigned int j = 0; j < HEIGHT; j++)
		{
			/* Create a normalized RGB color
			// vector fro the current pixel
			// in the image */
			temp[0] = (float)R[i][j]/255;
			temp[1] = (float)G[i][j]/255;
			temp[2] = (float)B[i][j]/255;

			/* Transform the RGB vector
			// to a YIQ vector */
			matrix_3_3multiplyVector_3(temp, RGBtoYIQMatrix);

			/* Perform the DIP */
			matrix_3_3multiplyVector_3(temp, XYPlaneVectorRotateMatrix);

			/* Transform back to RGB */
			matrix_3_3multiplyVector_3(temp, YIQtoRGBMatrix);

			/* Denormalize and store back into the image */
			temp[0] = temp[0] * 255;
			temp[0] = temp[0] < 0 ? 0 : temp[0];
			temp[0] = temp[0] > 255 ? 255 : temp[0];
			temp[1] = temp[1] * 255;
			temp[1] = temp[1] < 0 ? 0 : temp[1];
			temp[1] = temp[1] > 255 ? 255 : temp[1];
			temp[2] = temp[2] * 255;
			temp[2] = temp[2] < 0 ? 0 : temp[2];
			temp[2] = temp[2] > 255 ? 255 : temp[2];

			R[i][j] = (unsigned char)temp[0];
			G[i][j] = (unsigned char)temp[1];
			B[i][j] = (unsigned char)temp[2];
		}
	}
}

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
