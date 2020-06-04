/*********************************************************************/
/* PhotoLab.c: assignment 2 for EECS 22, Fall 2018                 */
/*                                                                   */
/* modifications: Mihnea Chirila                            */
/* 09/27/17 RD	adjusted for lecture usage                           */
/* 10/1/18 MC	 adjusted for F18                           */
/*********************************************************************/
/* Enter your name, last name and UCInet ID below:
 *
 * *****************************
 * First Name :	Jigar
 * Last Name:	Hira
 * UCInet ID:	92549698
 *
 */


#include <stdio.h>
#include <string.h>

#include "FileIO.h"
#include "Constants.h"
#include "DIPs.h"


void PrintMenu();

/* Test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

int main() {
    unsigned char   R[WIDTH][HEIGHT];	/* use three 2-D arrays to store R, G, B components */
    unsigned char   G[WIDTH][HEIGHT];
    unsigned char   B[WIDTH][HEIGHT];

    int option;			/* user input option */
    char fname[SLEN];		/* input file name */

    PrintMenu();
    printf("Please make your choice: ");
    scanf("%d", &option);

    int rc = -1;			/* return code of LoadImage() */

    while (option != EXIT) {
        if (option == 1) {
            printf("Please input the file name to load: ");
            scanf("%s", fname);
            rc = LoadImage(fname, R, G, B);
        }
        /* menu item 2 - 10 requires image is loaded first */
        else if (option >= 2 && option <= 5) {
            if (rc != SUCCESS)	 {
                printf("No image is read.\n");
            }
            /* now image is loaded */
            else {
                switch(option) {
                    case 2:
                        printf("Please input the file name to save: ");
                        scanf("%s", fname);
                        SaveImage(fname, R, G, B);
                        break;
                    case 3:
                        BlackNWhite(R, G, B);
                        printf("\"Black & White\" operation is done!\n");
                        break;
                    case 4:
                        Edge(R, G, B);
                        printf("\"Edge\" operation is done!\n");
                        break;
                    case 5:
                        Shuffle(R, G, B);
                        printf("\"Shuffle\" operation is done!\n");
                        break;
                    default:
                        break;
                }
            }
        }
        else if (option == 6) {
            AutoTest(R, G, B);
            rc = SUCCESS;	/* set returned code SUCCESS, since image is loaded */
        }
        else {
            printf("Invalid selection!\n");
        }

        /* Process finished, waiting for another input */
        PrintMenu();
        printf("Please make your choice: ");
        scanf("%d", &option);
    }
    printf("You exit the program.\n");
    return 0;
}

void PrintMenu() {
    printf("\n----------------------------\n");
    printf(" 1: Load a PPM image\n");
    printf(" 2: Save an image in PPM and JPEG format\n");
    printf(" 3: Change a color image to Black & White\n");
    printf(" 4: Sketch the edge of an image\n");
    printf(" 5: Shuffle an image\n");
    printf(" 6: Test all functions\n");
    printf(" 7: Exit\n");
}

/* Test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
    char fname[SLEN] = "HSSOE";
    char sname[SLEN];

    LoadImage(fname, R, G, B);
    BlackNWhite(R, G, B);
    strcpy(sname, "bw");
    SaveImage(sname, R, G, B);
    printf("Black & White tested!\n\n");

    LoadImage(fname, R, G, B);
    Edge(R, G, B);
    strcpy(sname, "edge");
    SaveImage(sname, R, G, B);
    printf("Edge Detection tested!\n\n");

    LoadImage(fname, R, G, B);
    Shuffle(R, G, B);
    strcpy(sname, "shuffle");
    SaveImage(sname, R, G, B);
    printf("Shuffle tested!\n\n");

}

/* EOF */
