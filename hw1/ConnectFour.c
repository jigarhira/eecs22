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
 *  2018/10/11	JH	completed anvil game functionality
 *  2018/10/09	JH	new win condition algorithim *
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
int CheckConnect(int, int);
void PrintBoard();

int Turn();
int TurnAnvil();
void PrintChip(int);
int PromptColumn(int);

/*********************************************************/

/*Declare your global variables below (if any)*/
/**************************************************/
 
int board[7][9] = {{0}};			/* game board (2D integer array) */
int column_open[9] = {6,6,6,6,6,6,6,6,6};	/* open position of each column */
int color;					/* color game boolean */
int anvil_player[2] = {1, 1};			/* gives each player one anvil */
int player = 1;					/* player one goes first */

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


/*Main function which executes first*/
int main(int argc, char** argv)
{
	int game_type;	/*game type that the user selects (1 or 2)*/
	
	game_type = DisplayMenu();

	/* runs either the regular or anvil game */
	if (game_type == 1)
	{
		RegularGame();
	}
	else
	{
		AnvilGame();
	}	
	
	return 0;
}


/*Game Menu function*/
int DisplayMenu()
{
	int input;	/*stores the user input*/

	/*Welcome Menu*/
	printf("%s","\n|--------------------------------|\n|Connect 4: EECS 22 by Jigar Hira|\n|--------------------------------|\n\nChoose Game Type:\n1-Regular\n2-ANVIL Mode\n\nEnter 1 or 2:    ");
	scanf("%d", &input);

	/* Color game prompt*/
	printf("Chose game mode:\n1-Normal\n2-%sC%so%sl%so%sr%se%sd%s\n\nEnter 1 or 2:    ", KRED, KGRN, KYEL, KRED, KGRN, KYEL, KRED, KNRM);
	scanf("%d", &color);

	return input;
}


/* Prints the correct ascii character based on the chip element */
void PrintChip(int element)
{
	if (color == 2)		/* checks if color option was selected */
	{
		/* Set color */
		switch (element)
		{
			case 1:			/* Player one chip (red) */
				printf("%s", KRED);
				break;
			case 2:			/* Player two chip (yellow) */
				printf("%s", KYEL);
				break;
			case 3:			/* Anvil Chip */	
				printf("%s", KWHT);	
				break;
			default:
				break;
		}
	}

	/* Prints correct character */
	switch (element)
	{
		case 0:			/* Empty slot */
			printf("%s", " ");
			break;		
		case 1:			/* Player one chip (red) */
			printf("%s", "R");
			break;
		case 2:			/* Player two chip (yellow) */
			printf("%s", "Y");
			break;
		case 3:			/* Anvil Chip */	
			printf("%s", "A");
			break;
		default:
			printf("%s", " ");
	}

	printf("%s", KNRM);	/* Return Color to normal */
}


void PrintBoard()
{
	printf("%s","\n 0 1 2 3 4 5 6 7 8 \n");	/* Column labels */

	/* Iterates through board and prints chips */	
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			printf("%s", "|");		/* Formatting for ascii display */
			PrintChip(board[i][j]);	
		}
		
		printf("%s","|\n");
	}
	
	printf("%s","\n");
} 

/* Player turn */
int Turn()
{
	int col;
	int row;
	
	/* Checks for valid entry */
	do
	{
		printf("%s%d%s","Player ", player, " | Enter column for next chip (0-8):	");
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

	column_open[col]-- ;		/* saves the value of the next open slot */

	return CheckConnect(row, col);	/* Checks for win condition*/
	
}

/* Prompt the user for a column choice */
int PromptColumn(int player)
{
	int col;
	
	/* Checks for valid entry */
	do
	{
		printf("%s%d%s","Player ", player, " | Enter column for next chip (0-8):	");
		scanf("%d",&col);

	} while (col < 0 || col > 8);

	return col;
}


/*Anvil Game player turn */
int TurnAnvil()
{
	int col;
	int row;
	
	int anvil;	/* anvil input */
	
	if (anvil_player[player - 1] == 1)	/* Checks if the player has used an anvil */
	{
		printf("%s%d%s", "Player ", player, " | Use Anvil? (1-yes 0-no):	");
		scanf("%d", &anvil);

		if (anvil == 1)		/* If the player wants to use an anvil */
		{
			col = PromptColumn(player);	/* Prompts the user for a column */
	
			/* checks if column is already full */
			if (column_open[col] < -1 )
			{
				printf("%s","ERROR | Column is full\n");
				player = (1 + 2) - player;
				return 0;
			}

			if (board[6][col] == 3)		/* Checks if an anvil has already been played */
			{
				row = 5;		/* Will place new anvil on top of existing anvil */
				column_open[col] = 4;
			}
			else
			{
				row = 6;		/* Will place anvil at the bottom of the column */
				column_open[col] = 5;
			}

			for (int i = 0; i < row; i++)
			{
				board[i][col] = 0;	/* Clears all the chips above the anvil */
			}

			board[row][col] = 3;		/* Places anvil */
			anvil_player[player - 1] = 0;	/* Ensure each player can only use anvil once */

			return 0;
		}
	}

	col = PromptColumn(player);
	
	/* checks if column is already full */
	if (column_open[col] < 0 )
	{
		printf("%s","ERROR | Column is full\n");
		player = (1 + 2) - player;
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

	/* loops through directions of possible win */
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{		
			
			/* Skips checking original box */	
			if (i == 0 && j == 0)
			{
				continue;
			}

			/* iterates twice, k = +- 1 for both forward and backward directions */
			for (int k = -1; k < 2; k += 2)
			{
				x = col + (k * i);	/* Resets the search coords to the first node in search direction */
				y = row + (k * j);

				/* Loops when index is in range and chip is matched */
				while( !(
					(x < 0 || x > 8 || y < 0 || y > 6) ||	/* Checks index out of bounds */
					(board[y][x] != chip_type) 		/* Checks for chip mismatch */
					))
				{
					connect_count++;	/* Increments the connect counter */
					
					x += (k * i);	/* traverses search direction one step farther */
					y += (k * j);
				}
			}

			if (connect_count > 2)		/* Win condition */
			{
				return 1;
			}

			connect_count = 0;	/* Resets connect counter */
		}
	}	

	return 0;
}

/* Regular Game function*/
int RegularGame()
{
	int win = 0;
	
	while (!win)	/* runs until win condition */
	{
		PrintBoard();
		
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

		win = Turn(player);		/* Player turn */
		
		player = (1 + 2) - player;	/* switches between player 1 and 2 */
		
	}

	PrintBoard();

	printf("%s%d%s", "\nPLAYER ", (1 + 2) - player, " WINS!\n\n");

	return 0;
}


/* Anvil Game function */
int AnvilGame()
{
	int win = 0;
	
	while (!win)	/* runs until win condition */
	{
		PrintBoard();
		
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

		win = TurnAnvil(player);		/* Player turn */
		
		player = (1 + 2) - player;	/* switches between player 1 and 2 */
		
	}

	PrintBoard();

	printf("%s%d%s", "\nPLAYER ", (1 + 2) - player, " WINS!\n\n");

	return 0;
}


/* EOF */
