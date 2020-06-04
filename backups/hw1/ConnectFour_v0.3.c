/********DO NOT MODIFY THIS SECTION************
 * 
 * EECS 22 : Advanced C Programming
 * Fall 2018, Prof. Quoc-Viet Dang
 * 
 * HW1  : ConnectFour game
 * Template file : ConnectFour.c
 * 
 * Created on September 26, 2018, 12:06 AM by Ali Nickparsa <anickpar@uci.edu>
 */
/**********************************************
 
// Enter your name, last name and UCInet ID below://
 * 
 * *****************************
 * First Name : Jigar 
 * Last Name: Hira
 * UCInet ID: hiraj
 *
 */

#include <stdio.h>

/************************************************************
 * ----- Revision History -----
 *
 *  2018/10/05	JH	added win checking algorithim
 *  2018/10/04	JH	added print graphics
 *  2018/10/03	JH	added menu funtion and modified game functions
 *  2018/10/02	JH	added welcome menu and regular game function
 ************************************************************/

/*Declare your function definitions in the section below*/
/*Mandatory Options : 1-DisplayMenu 2- RegularGame 3-AnvilGame 4-CheckConnect 5-PrintBoard*/
/*You may add other functions if needed*/
/*********************************************************/

int DisplayMenu();
int RegularGame();
int AnvilGame();
int CheckConnect();
void PrintBoard();

int Turn(int);
char ElementToChar(int);

/*********************************************************/

/*Declare your global variables below (if any)*/
/**************************************************/

int board[7][9] = {{0}};			/*game board (2D integer array)*/
int column_open[9] = {6,6,6,6,6,6,6,6,6};	/* open position of each column */

/**************************************************/

/*Colors (you can add or remove from this list*/
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"


/*Main function*/
int main(int argc, char** argv)
{
	int game_type;	/*game type that the user selects (1 or 2)*/
	
	game_type = DisplayMenu();

	if (game_type == 1)
	{
		RegularGame();
	}	
	
	return 0;
}


/*Game Menu function*/
int DisplayMenu()
{
	int input;	/*stores the user input*/

	/*Welcome Menu*/
	printf("%s","\n|--------------------------------|\n|Connect 4: EECS 22 by Jigar Hira|\n|--------------------------------|\n\nChoose Game Type:\n1-Regular\n2-ANVIL Mode\n\nEnter 1 or 2:	");
	scanf("%d", &input);

	return input;
}

/* Converts board integer to char for print out */
char ElementToChar(int element)
{
	switch (element)
	{
		case 0:			/* Empty slot */
			return ' ';
		
		case 1:			/* Player one chip (red) */
			return 'R';

		case 2:			/* Player two chip (yellow) */
			return 'Y';

		case 3:			/* Anvil Chip */	
			return 'A';	
		
		default:
			return ' ';
	}
}


void PrintBoard()
{
	char chip;	/* Char for chip */

	printf("%s","\n 0 1 2 3 4 5 6 7 8 \n");	/* Column labels */

	/* Iterates through board and prints chips */	
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			chip = ElementToChar(board[i][j]);
			printf("|%c", chip);	
		}
		
		printf("%s","|\n");
	}
	
	printf("%s","\n");
} 

/* Player turn */
int Turn(int player)
{
	int col;
	int row;
	
	/* Checks for valid entry */
	do
	{
		printf("%s%d%s","Player ", player, " | Enter column for next chip (0-8)	:");
		scanf("%d",&col);

	} while (col < 0 || col > 8);

	/* checks if column is already full */
	if (column_open[col] < 0 )
	{
		printf("%s","ERROR | Column is full\n");
		return 0;
	}

	row = column_open[col];

	board[row][col] = player;	/* Places a chip in the next availible slot in the chosen column */

	column_open[col]-- ;

	return CheckConnect(row, col);
	
}

/* Checks for win condition */
int CheckConnect(int row, int col)
{
	int connect_count = 0;	/* counts the number of connections */	
	int x, y;		/* search coords on board */
	int chip_type;		/* type of chip to match */
	
	chip_type = board[row][col];
	x = col;
	y = row;

	/* loops through all combinations of possible win direcitons */
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			x = col + i;	/* resets search coords*/
			y = row + j;			
			
			/* Skips checking original box */	
			if (i == 0 && j == 0)
			{
				continue;
			}

			/* Checks for index out of bounds */
			if ( !(x < 0 || x > 8 || y < 0 || y > 6) )
			{
				while (board[y][x] == chip_type)
				{
					connect_count++;
					
					if (connect_count == 3)		/* win condition */
					{
						return 1;
					}
					
					x += i;		/* progresses to next box */
					y += j;
					
					/* Checks for inde out of bounds again */
					if (x < 0 || x > 8 || y < 0 || y > 6)
					{
						break;
					}
				}
			}

			connect_count = 0;	/* Resets connect count for next direction */							
		}
	}	

	return 0;
}

/* Regular Game function*/
int RegularGame()
{
	int win = 0;
	int player = 1;	/* Player 1 gets the first turn */ 

	while (!win)	/* runs until win condition */
	{
		PrintBoard();
		
		win = Turn(player);		/* Player turn */
		
		player = (1 + 2) - player;	/* switches between player 1 and 2*/

		win = 2;			/* Checks if the board is completely full */
		for (int i = 0; i < 9; i++)
		{
			if (column_open[i] > -1)
			{
				win = 0;	
			}	
		}
		
		if (win == 2)
		{
			PrintBoard();
			printf("%s","\n--DRAW GAME--\n\n");
			
			return 0;
		}
	}

	PrintBoard();

	printf("%s%d%s", "\nPLAYER ", (1 + 2) - player, " WINS!\n\n");

	return 0;
}

/* EOF */
