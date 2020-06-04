/*********************************************************************/
/* PhotoLab.c: assignment 2 for EECS 22, Fall 2018                   */
/*                                                                   */
/* modifications: Mihnea Chirila                         	     */
/* 09/27/17 RD	adjusted for lecture usage                           */
/* 10/1/18 MC	 adjusted for F18                          	     */
/*********************************************************************/
/* Enter your name, last name and UCInet ID below:
 *
 * *****************************
 * First Name :	Jigar
 * Last Name:	Hira
 * UCInet ID:	92549698
 *
 */

/*** header files ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*** global definitions ***/

#define SLEN 80 		/* maximum length of file names and string*/
#define SUCCESS 0		/* return code for success */
#define EXIT 7			/* menu item number for EXIT */
#define MAX_PIXEL 255		/* max pixel value */
#define MIN_PIXEL 0		/* min pixel value */
#define SHUFF_HEIGHT_DIV 4      /* Height division for shuffleing */
#define SHUFF_WIDTH_DIV 4       /* Width division for shuffleing */

const int WIDTH = 600;	/* image width */
const int HEIGHT = 400;	/* image height */

/*** function declarations ***/

/* Ensures the value is between 0 and 255 */
int FixPixel(int value);


/* Prompt user with menu */
int PrintMenu();

/* read image from a file */
int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT],
              unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* save a processed image */
int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT],
              unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* edge detection */
void Edge(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
          unsigned char B[WIDTH][HEIGHT]);

/* change color image to black & white */
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT]);

/* sharpen the image */
void Shuffle(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
             unsigned char B[WIDTH][HEIGHT]);

/* Test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
              unsigned char B[WIDTH][HEIGHT]);

/*** main program ***/

int main(void)
{
    unsigned char R[WIDTH][HEIGHT];
    unsigned char G[WIDTH][HEIGHT];
    unsigned char B[WIDTH][HEIGHT];

    int input; 			/* stores user input */
    char filename[SLEN];	/* name of file */

    while (input != EXIT)	/* Displays menu until user selects 7 for exit */
    {
    	input = PrintMenu();

	switch (input)		/* Menu loop */
	{
		case 1:		/* Load File */
			printf("%s", "Please enter file to load:	");	/* Prompts the user for filename */
			scanf("%s", filename);

			if (LoadImage(filename, R, G, B) != 0)			/* LoadImage() error notice */
			{
				printf("%s", "ERROR | Load not completed successfully\n");
			}

			break;
		
		case 2:		/* Save File */
			printf("%s", "Please enter filename for saving:	");	/* Prompts the user for filename */
			scanf("%s", filename);

			if (SaveImage(filename, R, G, B) != 0)			/* SaveImage() error notice */
			{
				printf("%s", "ERROR | Save not completed sucessfully\n");
			}

			break;

		case 3:		/* Black and White */
			BlackNWhite(R, G, B);
			break;
		
		case 4:		/* Edge Detection  */
			Edge(R, G, B);
			break;

		default:
		break;
	}

	printf("%s","\n\n");	/* Adds new lines */

    }
       
    
    // just a sample for loading an image
    // remove this if statement for your actual program
    // do not specify extension for loading or saving
    /*if (LoadImage("HSSOE", R, G, B) != 0)
        { return 10; }
	*/

    return 0;
} /* end of main */


/*** function definitions ***/

/* Fixes out of bounds for pixel value */
int FixPixel(int value)
{
	if (value < 0)
	{
		value = 0;	
	}
	else if (value > 255)
	{
		value = 255;
	}
	
	return value;
}


/* change color image to black & white */
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	for (int i = 0; i < WIDTH; i++)		/* Iterate columns */
	{
		for (int j = 0; j < HEIGHT; j++)	/* Iterate rows */
		{
			R[i][j] = (R[i][j] + G[i][j] + B[i][j]) / 3;	/* Set RGB to average of the three */
			G[i][j] = R[i][j];
			B[i][j] = R[i][j];
		}
	}
}


/* edge detection */
void Edge(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int R_new[WIDTH][HEIGHT];
	int G_new[WIDTH][HEIGHT];
	int B_new[WIDTH][HEIGHT];
	
	
	for (int i = 0; i < WIDTH; i++)			/* Iterates columns */
	{
		for (int j = 0; j < HEIGHT; j++)	/* Iterates rows */
		{			
			/* True if not an edge pixel */
			if ( (i != 0) && (i != (WIDTH - 1)) && (j != 0) && (j != (HEIGHT - 1)) )
			{

				R_new[i][j] = 8 * (int) R[i][j];		/* Multiplies every RGB value by 8 */
				G_new[i][j] = 8 * (int) G[i][j];
				B_new[i][j] = 8 * (int) B[i][j];

				for (int k = -1; k < 2; k++)		/* Iterates through all surrounding pixels */
				{
					for (int l = -1; l < 2; l++)
					{
						if (k == 0 && l == 0)	/* skips original square */
						{
							continue;
						}
						
						printf("Neighbor (%d, %d)\n", k, l);
						printf("R neighbor is %d\n", R[i + k][j + l]);
						printf("G neighbor is %d\n", G[i + k][j + l]);
						printf("B neighbor is %d\n", B[i + k][j + l]);
						
						R_new[i][j] -= (int) R[i + k][j + l];		/* Subtracts the surrounding RGB values */
						G_new[i][j] -= (int) G[i + k][j + l];
						B_new[i][j] -= (int) B[i + k][j + l];
								
					}
				}

			}
			else
			{
				/* Sets boarder pixels to black */
				R_new[i][j] = 0;
				G_new[i][j] = 0;
				B_new[i][j] = 0;

			}


		}
	}

	/* Update the original image*/
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HIEGHT; j++)
		{
			/* Corrects values to [0, 255] */
			R_new[i][j] = FixPixel(R_new[i][j]);
			G_new[i][j] = FixPixel(G_new[i][j]);
			B_new[i][j] = FixPixel(B_new[i][j]);
			
			printf("R is %d\n", R[i][j]);
			printf("G is %d\n", G[i][j]);
			printf("B is %d\n", B[i][j]);			
			
			R[i][j] = (char) R_new[i][j];	/* updates the original  */
			G[i][j] = (char) G_new[i][j];
			B[i][j] = (char) B_new[i][j];

			printf("R_new is %d\n", R[i][j]);
			printf("G_new is %d\n", G[i][j]);
			printf("B_new is %d\n", B[i][j]);

		}
	}
}







/* Prints the menu for choosing an operation and returns choice */
int PrintMenu()
{
	int input = EXIT;	/* user input */

	printf("%s","---------------------------------------------\n1: Load a PPM image\n2: Save an image in PPM and JPEG format\n3: Change a color image to Black & White\n4: Sketch the edge of an image\n5: Shuffle an image\n6: Test all functions\n7: Exit\nplease make your choice:	");

	scanf("%d",&input);

	return input;
}


/* read a photo from the specified file into the specified */
/* RGB data structure; returns 0 for success, >0 for error */


int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
        FILE           *File;
        char            Type[SLEN];
        int             Width, Height, MaxValue;
        int             x, y;
        char            ftype[] = ".ppm";
        char            fname_tmp[SLEN];
        strcpy(fname_tmp, fname);
        strcat(fname_tmp, ftype);

        File = fopen(fname_tmp, "r");
        if (!File) {
                printf("Cannot open file \"%s\" for reading!\n", fname);
                return 1;
                    }
        fscanf(File, "%79s", Type);
        if (Type[0] != 'P' || Type[1] != '6' || Type[2] != 0) {
                printf("\nUnsupported file format!\n");
                return 2;
                                                                }
        fscanf(File, "%d", &Width);
        if (Width != WIDTH) {
                printf("\nUnsupported image width %d!\n", Width);
                return 3;
                             }
        fscanf(File, "%d", &Height);
        if (Height != HEIGHT) {
                 printf("\nUnsupported image height %d!\n", Height);
                 return 4;
                              }
        fscanf(File, "%d", &MaxValue);
        if (MaxValue != 255) {
                 printf("\nUnsupported image maximum value %d!\n", MaxValue);
                 return 5;
                            }
        if ('\n' != fgetc(File)) {
                 printf("\nCarriage return expected!\n");
                 return 6;
                                }
        for (y = 0; y < HEIGHT; y++)
             for (x = 0; x < WIDTH; x++) {
                         R[x][y] = fgetc(File);
                         G[x][y] = fgetc(File);
                         B[x][y] = fgetc(File);
                                         }
        if (ferror(File)) {
             printf("\nFile error while reading from file!\n");
             return 7;
                           }
        printf("%s was read.\n", fname_tmp);
        fclose(File);
        return 0;
}

int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
        FILE    *File;
        int x, y;
        char    SysCmd[SLEN * 5];
        char    ftype[] = ".ppm";
        char    fname_tmp[SLEN];  /*avoid to modify on the original pointer, 11/10/10, X.Han*/
        char    fname_tmp2[SLEN];

        strcpy(fname_tmp, fname);
        strcpy(fname_tmp2, fname);
        strcat(fname_tmp2, ftype);

        File = fopen(fname_tmp2, "w");
        if (!File) {
                printf("Cannot open file \"%s\" for writing!\n", fname);
                return 1;
                   }
        fprintf(File, "P6\n");
        fprintf(File, "%d %d\n", WIDTH, HEIGHT);
        fprintf(File, "255\n");
        for (y = 0; y < HEIGHT; y++)
                 for (x = 0; x < WIDTH; x++) {
                               fputc(R[x][y], File);
                               fputc(G[x][y], File);
                               fputc(B[x][y], File);
                                              }
         if (ferror(File)) {
                  printf("\nFile error while writing to file!\n");
                  return 2;
                            }
         fclose(File);
         printf("%s was saved. \n", fname_tmp2);
   /*
     *      * rename file to image.ppm, convert it to ~/public_html/<fname>.jpg
     *           * and make it world readable
                                   *                */
        sprintf(SysCmd, "/users/grad2/doemer/eecs22/bin/pnmtojpeg_hw2.tcsh %s", fname_tmp2);
        if (system(SysCmd) != 0) {
        printf("\nError while converting to JPG:\nCommand \"%s\" failed!\n", SysCmd);
        return 3;
                                  }
        printf("%s.jpg was stored.\n", fname_tmp);
        return 0;
}








/*


        .
        .
        .
        .
        .



*/




/* EOF */
