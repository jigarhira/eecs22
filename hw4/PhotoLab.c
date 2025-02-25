/*********************************************************************/
/* PhotoLab.c: homework assignment #4, for EECS 22,  Fall 2017       */
/* Jigar Hira							     */
/*********************************************************************/

#include <stdio.h>
#include <string.h>

#include "DIPs.h"
#include "Advanced.h"
#include "FileIO.h"
#include "Constants.h"
#include "Image.h"
#include "Test.h"

/*** function declarations ***/

/* print a menu */
void PrintMenu();


int main()
{
	IMAGE *rc;
	rc = NULL;

#ifdef DEBUG
	AutoTest();

#else
	IMAGE *image = NULL;		/* stores image */
	
	int option;			/* user input option */
	char fname[SLEN];		/* input file name */
	int brightness = -256;
	float angle;
	int optionRotate;
	int percentage;
	float percent;

	PrintMenu();
	printf("Please make your choice: ");
	scanf("%d", &option);

	while (option != EXIT) {
		if (option == 1) {
			printf("Please input the file name to load: ");
			scanf("%s", fname);
			
			if (image) /* checks if an image already exists */
			{
				DeleteImage(image);
			}
			image = LoadImage(fname);
			rc = image;
		}

		/* menu item 2 - 8 requires image is loaded first */
		else if (option >= 2 && option <= 11) {
			if (!rc)	 {
				printf("No image is read.\n");
			}
			/* now image is loaded */
			else {
				switch (option) {
					case 2:
						printf("Please input the file name to save: ");
						scanf("%s", fname);
						SaveImage(fname, image);
						break;
					case 3:
						image = BlackNWhite(image);
						printf("\"Black & White\" operation is done!\n");
						break;
					case 4:
						image = Edge(image);
						printf("\"Edge\" operation is done!\n");
						break;
					case 5:
						image = Shuffle(image);
						printf("\"Shuffle\" operation is done!\n");
						break;
					case 6:
						while(brightness > 255 || brightness < -255){
							printf("Enter brightness value (between -255 and 255):");
							scanf("%d", &brightness);
						}
						image = Brightness(image, brightness);
						printf("\"brightness\" operation is done!\n");
						break;
					case 7:
						image = HMirror(image);
						printf("\"Horizontally Mirror\" operation is done!\n");
						break;
					case 8:
						printf("Enter hue rotation angle:");
						scanf("%f", &angle);
						image = HueRotate(image, angle);
						printf("\"HueRotate\" operation is done!\n");
						break;
					case 9:
						printf("Enter option (1-Horizontal Flip, 2-Vertical Flip, 3-Rotate Right, 4-Rotate Left):");
						scanf("%d", &optionRotate);
						image = Rotate(image, optionRotate);
						printf("\"Rotate\" operation is done!\n");
						break;
					case 10:
						printf("Enter resize percentage:");
						scanf("%d", &percentage);
						image = Resize(image, percentage);
						printf("\"Resize\" operation is done!\n");
						break;
					case 11:
						printf("Enter saturation percentage:");
						scanf("%f", &percent);
						image = Saturate(image, percent);
						printf("\"Saturate\" operation is done!\n");
						break;
					case 12:
						AutoTest();
						break;

					default:
						break;

					}
				}
		}

		else if (option == 12) {
			AutoTest();
		}
		else {
			printf("Invalid selection!\n");
		}

		/* Process finished, waiting for another input */
		PrintMenu();
		printf("Please make your choice: ");
		scanf("%d", &option);
	}

	if (image)	/* checks if there is an image to free */
	{
		DeleteImage(image);
	}

	printf("You exit the program.\n");
	#endif

	return 0;
}


/*******************************************/
/* Function implementations should go here */
/*******************************************/

/* Menu */
void PrintMenu() {
    printf("\n----------------------------\n");
    printf(" 1: Load a PPM image\n");
    printf(" 2: Save an image in PPM and JPEG format\n");
    printf(" 3: Change a color image to Black & White\n");
    printf(" 4: Sketch the edge of an image\n");
    printf(" 5: Shuffle an image\n");
    printf(" 6: Adjust the brightness of an image\n");
    printf(" 7: Mirror an image horizontally\n");
    printf(" 8: Adjust the hue of an image\n");
    printf(" 9: Rotate or flip the image\n");
    printf(" 10:Resize the image\n");
    printf(" 11:Saturate the image\n");
    printf(" 12:Test all functions\n");
    printf(" 13:Exit\n");
}

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
