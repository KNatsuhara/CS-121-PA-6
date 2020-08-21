#include "header.h"

/*
Function: intro_page
Date Created: 11/6/2019
Date Modified: 11/6/2019
Description: Prints out title and rules of battleship
Input Parameters: void
Returns: void
*/
void intro_page(void)
{
	printf("=======WELCOME TO BATTLESHIP!=======\n");
	printf("\n");
	printf("=======Rules of Battleship=======\n");
	printf("1. Place down all 5 of your ships!\n");
	printf("2. Take turns calling out coordinates!\n");
	printf("3. Call out if it is a miss or hit!\n");
	printf("4. First player to sink their opponents ships wins!\n");
	printf("=================================\n");
	printf("\n");
}

/*
Function: init_board
Date Created: 11/6/2019
Date Modified: 11/6/2019
Description: Initializes board and sets all the cells
Input Parameters: Cell board[][NUM_COLS_BOARD], int rows, int cols
Returns: void
*/
void init_board(Cell board[][NUM_COLS_BOARD], int rows, int cols)
{
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			board[i][j].vehicle = '\0';
			board[i][j].occupied = 0;
			board[i][j].shot = -1;
			board[i][j].location.row = i;
			board[i][j].location.col = j;
		}
	}
	for (int i = 0; i < cols; i++)
	{
		board[0][i].occupied = -1;
		board[0][i].shot = -2;
		board[i][0].occupied = -1;
		board[i][0].shot = -2;
	}
	board[0][0].occupied = 9;
	board[0][0].shot = 9;
}

/*
Function: print_ship_board
Date Created: 11/6/2019
Date Modified: 11/6/2019
Description: prints out the ship locations of each player
Input Parameters: Cell board[][NUM_COLS_BOARD], int rows, int cols
Returns: void
*/
void print_ship_board(Cell board[][NUM_COLS_BOARD], int rows, int cols)
{
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if (board[i][j].occupied == 1)
			{
				printf("%c", board[i][j].vehicle);
			}
			else if (board[i][j].occupied == 0)
			{
				printf("-");
			}
			else if (board[0][j].occupied == -1)
			{
				printf("%d", j-1);
			}
			else if (board[i][0].occupied == -1)
			{
				printf("%d", i-1);
			}
			else if (board[i][j].occupied == 9)
			{
				printf(" ");
			}
		}
		printf("\n");
	}
}

/*
Function: print_shot_board
Date Created: 11/6/2019
Date Modified: 11/6/2019
Description: prints out the shot locations and status of a player's board
Input Parameters: Cell board[][NUM_COLS_BOARD], int rows, int cols
Returns: void
*/
void print_shot_board(Cell board[][NUM_COLS_BOARD], int rows, int cols)
{
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if (board[i][j].shot == 1)
			{
				printf("X");
			}
			else if (board[i][j].shot == 0)
			{
				printf("O");
			}
			else if(board[i][j].shot == -1)
			{
				printf("-");
			}
			else if (board[0][j].shot == -2)
			{
				printf("%d", j - 1);
			}
			else if (board[i][0].shot == -2)
			{
				printf("%d", i - 1);
			}
			else if (board[i][j].shot == 9)
			{
				printf(" ");
			}
		}
		printf("\n");
	}
}

/*
Function: manually_place_ships
Date Created: 11/6/2019
Date Modified: 11/6/2019
Description: asks for ship orientation and then asks for a coordinate to place the ships
Input Parameters: Cell board[][NUM_COLS_BOARD], int rows, int cols
Returns: void
*/
void manually_place_ships(Cell board[][NUM_COLS_BOARD], int rows, int cols)
{
	int row = 0, col = 0;
	char orientation = '\0';

	printf("Placing the Carrier\n");
	orientation = get_orientation();

	if (orientation == 'H')
	{
		do
		{
			get_coordinates(board, &row, &col);
		} while (col > 5 || board[row][col].occupied == 1);

		for (int i = 0; i < 5; i++)
		{
			board[row + 1][col + i + 1].occupied = 1;
			board[row + 1][col + i + 1].vehicle = CARRIER;
		}
	}
	else if(orientation == 'V')
	{
		do
		{
			get_coordinates(board, &row, &col);
		} while (row > 5 || board[row][col].occupied == 1);
		for (int i = 0; i < 5; i++)
		{
			board[row + i + 1][col + 1].occupied = 1;
			board[row + i + 1][col + 1].vehicle = CARRIER;
		}
	}

	print_ship_board(board, NUM_ROWS_BOARD, NUM_COLS_BOARD);
	printf("Placing the Battleship\n");
	orientation = get_orientation();

	if (orientation == 'H')
	{
		do
		{
			get_coordinates(board, &row, &col);
		} while (col > 6 || board[row + 1][col + 1].occupied == 1 || board[row + 1][col + 2].occupied == 1 ||
			board[row + 1][col + 3].occupied == 1 || board[row + 1][col + 4].occupied == 1);

		for (int i = 0; i < 4; i++)
		{
			board[row + 1][col + i + 1].occupied = 1;
			board[row + 1][col + i + 1].vehicle = BATTLESHIP;
		}
	}
	else if (orientation == 'V')
	{
		do
		{
			get_coordinates(board, &row, &col);
		} while (row > 6 || board[row + 1][col + 1].occupied == 1 || board[row + 2][col + 1].occupied == 1 ||
			board[row + 3][col + 1].occupied == 1 || board[row + 4][col + 1].occupied == 1);

		for (int i = 0; i < 4; i++)
		{
			board[row + i + 1][col + 1].occupied = 1;
			board[row + i + 1][col + 1].vehicle = BATTLESHIP;
		}
	}

	print_ship_board(board, NUM_ROWS_BOARD, NUM_COLS_BOARD);
	printf("Placing the Cruiser\n");
	orientation = get_orientation();

	if (orientation == 'H')
	{
		do
		{
			get_coordinates(board, &row, &col);
		} while (col > 7 || board[row + 1][col + 1].occupied == 1 || board[row + 1][col + 2].occupied == 1 ||
			board[row + 1][col + 3].occupied == 1);

		for (int i = 0; i < 3; i++)
		{
			board[row + 1][col + i + 1].occupied = 1;
			board[row + 1][col + i + 1].vehicle = CRUSIER;
		}
	}
	else if (orientation == 'V')
	{
		do
		{
			get_coordinates(board, &row, &col);
		} while (row > 7 || board[row + 1][col + 1].occupied == 1 || board[row + 2][col + 1].occupied == 1 ||
			board[row + 3][col + 1].occupied == 1);

		for (int i = 0; i < 3; i++)
		{
			board[row + i + 1][col + 1].occupied = 1;
			board[row + i + 1][col + 1].vehicle = CRUSIER;
		}
	}

	print_ship_board(board, NUM_ROWS_BOARD, NUM_COLS_BOARD);
	printf("Placing the Submarine\n");
	orientation = get_orientation();

	if (orientation == 'H')
	{
		do
		{
			get_coordinates(board, &row, &col);
		} while (col > 7 || board[row + 1][col + 1].occupied == 1 || board[row + 1][col + 2].occupied == 1 ||
			board[row + 1][col + 3].occupied == 1);

		for (int i = 0; i < 3; i++)
		{
			board[row + 1][col + i + 1].occupied = 1;
			board[row + 1][col + i + 1].vehicle = SUBMARINE;
		}
	}
	else if (orientation == 'V')
	{
		do
		{
			get_coordinates(board, &row, &col);
		} while (row > 7 || board[row + 1][col + 1].occupied == 1 || board[row + 2][col + 1].occupied == 1 ||
			board[row + 3][col + 1].occupied == 1);

		for (int i = 0; i < 3; i++)
		{
			board[row + i + 1][col + 1].occupied = 1;
			board[row + i + 1][col + 1].vehicle = SUBMARINE;
		}
	}

	print_ship_board(board, NUM_ROWS_BOARD, NUM_COLS_BOARD);
	printf("Placing the Destroyer\n");
	orientation = get_orientation();

	if (orientation == 'H')
	{
		do
		{
			get_coordinates(board, &row, &col);
		} while (col > 8 || board[row + 1][col + 1].occupied == 1 || board[row + 1][col + 2].occupied == 1);

		for (int i = 0; i < 2; i++)
		{
			board[row + 1][col + i + 1].occupied = 1;
			board[row + 1][col + i + 1].vehicle = DESTORYER;
		}
	}
	else if (orientation == 'V')
	{
		do
		{
			get_coordinates(board, &row, &col);
		} while (row > 8 || board[row + 1][col + 1].occupied == 1 || board[row + 2][col + 1].occupied == 1);

		for (int i = 0; i < 2; i++)
		{
			board[row + i + 1][col + 1].occupied = 1;
			board[row + i + 1][col + 1].vehicle = DESTORYER;
		}
	}

	print_ship_board(board, NUM_ROWS_BOARD, NUM_COLS_BOARD);

	//1. carrier, 2. battleship, 3. Crusier, 4. Submarine, 5. Destroyer
	//ask horizontal or vertical
	//ask for specific coordinates (Restrict Coordinates respectively)
	//if ship overlaps, reask coordinates
	//			//depending on horizontal or vertical check how many spots the size of the ship is to see if the spots are occupied
	//change board occupation and vehicle
}

/*
Function: randomly_place_ships
Date Created: 11/6/2019
Date Modified: 11/6/2019
Description: randomizes ship orientation and then randomizes a coordinate to place the ships
Input Parameters: Cell board[][NUM_COLS_BOARD], int rows, int cols
Returns: void
*/
void randomly_place_ships(Cell board[][NUM_COLS_BOARD], int rows, int cols)
{
	int row = 0, col = 0;
	char orientation = '\0';

	orientation = get_random_orientation();

	if (orientation == 'H')
	{
		do
		{
			get_random_coordinates(board, &row, &col);
		} while (col > 5 || board[row][col].occupied == 1);

		for (int i = 0; i < 5; i++)
		{
			board[row + 1][col + i + 1].occupied = 1;
			board[row + 1][col + i + 1].vehicle = CARRIER;
		}
	}
	else if (orientation == 'V')
	{
		do
		{
			get_random_coordinates(board, &row, &col);
		} while (row > 5 || board[row][col].occupied == 1);
		for (int i = 0; i < 5; i++)
		{
			board[row + i + 1][col + 1].occupied = 1;
			board[row + i + 1][col + 1].vehicle = CARRIER;
		}
	}

	orientation = get_random_orientation();

	if (orientation == 'H')
	{
		do
		{
			get_random_coordinates(board, &row, &col);
		} while (col > 6 || board[row + 1][col + 1].occupied == 1 || board[row + 1][col + 2].occupied == 1 ||
			board[row + 1][col + 3].occupied == 1 || board[row + 1][col + 4].occupied == 1);

		for (int i = 0; i < 4; i++)
		{
			board[row + 1][col + i + 1].occupied = 1;
			board[row + 1][col + i + 1].vehicle = BATTLESHIP;
		}
	}
	else if (orientation == 'V')
	{
		do
		{
			get_random_coordinates(board, &row, &col);
		} while (row > 6 || board[row + 1][col + 1].occupied == 1 || board[row + 2][col + 1].occupied == 1 ||
			board[row + 3][col + 1].occupied == 1 || board[row + 4][col + 1].occupied == 1);

		for (int i = 0; i < 4; i++)
		{
			board[row + i + 1][col + 1].occupied = 1;
			board[row + i + 1][col + 1].vehicle = BATTLESHIP;
		}
	}

	orientation = get_random_orientation();

	if (orientation == 'H')
	{
		do
		{
			get_random_coordinates(board, &row, &col);
		} while (col > 7 || board[row + 1][col + 1].occupied == 1 || board[row + 1][col + 2].occupied == 1 ||
			board[row + 1][col + 3].occupied == 1);

		for (int i = 0; i < 3; i++)
		{
			board[row + 1][col + i + 1].occupied = 1;
			board[row + 1][col + i + 1].vehicle = CRUSIER;
		}
	}
	else if (orientation == 'V')
	{
		do
		{
			get_random_coordinates(board, &row, &col);
		} while (row > 7 || board[row + 1][col + 1].occupied == 1 || board[row + 2][col + 1].occupied == 1 ||
			board[row + 3][col + 1].occupied == 1);

		for (int i = 0; i < 3; i++)
		{
			board[row + i + 1][col + 1].occupied = 1;
			board[row + i + 1][col + 1].vehicle = CRUSIER;
		}
	}

	orientation = get_random_orientation();

	if (orientation == 'H')
	{
		do
		{
			get_random_coordinates(board, &row, &col);
		} while (col > 7 || board[row + 1][col + 1].occupied == 1 || board[row + 1][col + 2].occupied == 1 ||
			board[row + 1][col + 3].occupied == 1);

		for (int i = 0; i < 3; i++)
		{
			board[row + 1][col + i + 1].occupied = 1;
			board[row + 1][col + i + 1].vehicle = SUBMARINE;
		}
	}
	else if (orientation == 'V')
	{
		do
		{
			get_random_coordinates(board, &row, &col);
		} while (row > 7 || board[row + 1][col + 1].occupied == 1 || board[row + 2][col + 1].occupied == 1 ||
			board[row + 3][col + 1].occupied == 1);

		for (int i = 0; i < 3; i++)
		{
			board[row + i + 1][col + 1].occupied = 1;
			board[row + i + 1][col + 1].vehicle = SUBMARINE;
		}
	}

	orientation = get_random_orientation();

	if (orientation == 'H')
	{
		do
		{
			get_random_coordinates(board, &row, &col);
		} while (col > 8 || board[row + 1][col + 1].occupied == 1 || board[row + 1][col + 2].occupied == 1);

		for (int i = 0; i < 2; i++)
		{
			board[row + 1][col + i + 1].occupied = 1;
			board[row + 1][col + i + 1].vehicle = DESTORYER;
		}
	}
	else if (orientation == 'V')
	{
		do
		{
			get_random_coordinates(board, &row, &col);
		} while (row > 8 || board[row + 1][col + 1].occupied == 1 || board[row + 2][col + 1].occupied == 1);

		for (int i = 0; i < 2; i++)
		{
			board[row + i + 1][col + 1].occupied = 1;
			board[row + i + 1][col + 1].vehicle = DESTORYER;
		}
	}

	print_ship_board(board, NUM_ROWS_BOARD, NUM_COLS_BOARD);
}

/*
Function: pick_first
Date Created: 11/6/2019
Date Modified: 11/6/2019
Description: randomly selects a number between 0 and 1
Input Parameters: void
Returns: integer 0 or 1
*/
int pick_first(void)
{
	int x = 0;
	x = rand() % 2;
	return x;
}

/*
Function: get_coordinates
Date Created: 11/6/2019
Date Modified: 11/6/2019
Description: asks for 2 integers from user and then uses pointers to return the two integers the user inputted
Input Parameters: Cell board[][NUM_COLS_BOARD], int *xpos, int *ypos
Returns: void
*/
void get_coordinates(Cell board[][NUM_COLS_BOARD], int *xpos, int *ypos)
{
	int x = 0, y = 0;
	do
	{
		printf("Input a coordinate: ");
		scanf("%d%d", &x, &y);
	} while (0 > x || x > 9 || 0 > y || y > 9);
	*xpos = x;
	*ypos = y;
}

/*
Function: get_random_coordinates
Date Created: 11/6/2019
Date Modified: 11/6/2019
Description: produces 2 random integers for the user and then uses pointers to return the two integers
Input Parameters: Cell board[][NUM_COLS_BOARD], int *xpos, int *ypos
Returns: void
*/
void get_random_coordinates(Cell board[][NUM_COLS_BOARD], int* xpos, int* ypos)
{
	int x = 0, y = 0;
	do
	{
		x = rand() % 10;
		y = rand() % 10;
	} while (0 > x || x > 9 || 0 > y || y > 9);
	*xpos = x;
	*ypos = y;
}

/*
Function: get_orientation
Date Created: 11/6/2019
Date Modified: 11/6/2019
Description: asks for a character on whether or not the user wants their ship to be horizontal or vertical
Input Parameters: void
Returns: char either 'V' or 'H'
*/
char get_orientation(void)
{
	char c = '\0';
	printf("Do you want the ship to be horizontal or vertical (H/V)?: ");
	scanf(" %c", &c);
	return c;
}

/*
Function: get_random_orientation
Date Created: 11/6/2019
Date Modified: 11/6/2019
Description: produces a random character on whether or not the user wants their ship to be horizontal or vertical
Input Parameters: void
Returns: char either 'V' or 'H'
*/
char get_random_orientation(void)
{
	int x = 0;
	char c = '\0';
	x = rand() % 2;

	if (x == 0)
	{
		c = 'H';
	}
	else
	{
		c = 'V';
	}

	return c;
}

/*
Function: guess_shot
Date Created: 11/6/2019
Date Modified: 11/6/2019
Description: check the coordinates on the board and check whether or not the coordinate hit or missed
Input Parameters: Cell board[][NUM_COLS_BOARD], FILE* outfile
Returns: returns a character based on what the player hit or missed
*/
char guess_shot(Cell board[][NUM_COLS_BOARD], FILE* outfile)
{
	int x = 0, y = 0;

	do
	{
		printf("Where would you like to fire? ");
		get_coordinates(board, &x, &y);
	} while (board[x + 1][y + 1].shot != -1);
	

	if (board[x + 1][y + 1].occupied == 1)
	{
		printf("You hit a ship!\n");
		board[x + 1][y + 1].shot = 1;
		fprintf(outfile, "Player 1: %d,%d hit\n", x, y);
		if (board[x+1][y + 1].vehicle == CARRIER)
		{
			return CARRIER;
		}
		else if (board[x + 1][y + 1].vehicle == BATTLESHIP)
		{
			return BATTLESHIP;
		}
		else if (board[x + 1][y + 1].vehicle == CRUSIER)
		{
			return CRUSIER;
		}
		else if (board[x + 1][y + 1].vehicle == SUBMARINE)
		{
			return SUBMARINE;
		}
		else
		{
			return DESTORYER;
		}

	}
	else
	{
		printf("You missed!\n");
		board[x + 1][y + 1].shot = 0;
		fprintf(outfile, "Player 1: %d,%d missed\n", x, y);
		return 'm';
	}
}

/*
Function: random_guess_shot
Date Created: 11/6/2019
Date Modified: 11/6/2019
Description: randomly guess a coordinate on the board and check whether or not the coordinate hit or missed
Input Parameters: Cell board[][NUM_COLS_BOARD], FILE* outfile
Returns: returns a character based on what the player hit or missed
*/
char random_guess_shot(Cell board[][NUM_COLS_BOARD], FILE* outfile)
{
	int x = 0, y = 0;

	do
	{
		get_random_coordinates(board, &x, &y);
	} while (board[x + 1][y + 1].shot != -1);


	if (board[x + 1][y + 1].occupied == 1)
	{
		printf("Computer hit a ship!\n");
		board[x + 1][y + 1].shot = 1;
		fprintf(outfile, "Computer: %d,%d hit\n", x, y);
		if (board[x + 1][y + 1].vehicle == CARRIER)
		{
			return CARRIER;
		}
		else if (board[x + 1][y + 1].vehicle == BATTLESHIP)
		{
			return BATTLESHIP;
		}
		else if (board[x + 1][y + 1].vehicle == CRUSIER)
		{
			return CRUSIER;
		}
		else if (board[x + 1][y + 1].vehicle == SUBMARINE)
		{
			return SUBMARINE;
		}
		else
		{
			return DESTORYER;
		}

	}
	else
	{
		printf("Computer missed!\n");
		board[x + 1][y + 1].shot = 0;
		fprintf(outfile, "Computer: %d,%d missed\n", x, y);
		return 'm';
	}
}

/*
Function: get_yes_no
Date Created: 11/6/2019
Date Modified: 11/6/2019
Description: prompts the user for a Yes or no response
Input Parameters: void
Returns: returns a character either 'Y' or 'N'
*/
char get_yes_no(void)
{
	char c = '\0';
	scanf(" %c", &c);
	return c;
}

/*
Function: determine_shot
Date Created: 11/6/2019
Date Modified: 11/6/2019
Description: determines which ship is hit and returns the number of hits, misses and total number of shots through pointers
Input Parameters: char c, int c1, int b1, int r1, int s1, int 
d1, int h1, int m1, int t1, int* pc, int* pb, int* pr, int* ps, int* pd, int* ph, int* pm, int* total
Returns: void
*/
void determine_shot(char c, int c1, int b1, int r1, int s1, int d1, int h1, int m1, int t1, int* pc, 
	int* pb, int* pr, int* ps, int* pd, int* ph, int* pm, int* total)
{
	if (c == CARRIER)
	{
		*pc = c1 + 1;
		*ph = h1 + 1;
	}
	else if (c == BATTLESHIP)
	{
		*pb = b1 + 1;
		*ph = h1 + 1;
	}
	else if (c == CRUSIER)
	{
		*pr = r1 + 1;
		*ph = h1 + 1;
	}
	else if (c == SUBMARINE)
	{
		*ps = s1 + 1;
		*ph = h1 + 1;
	}
	else if (c == DESTORYER)
	{
		*pd = d1 + 1;
		*ph = h1 + 1;
	}
	else
	{
		*pm = m1 + 1;
	}
	*total = t1 + 1;
}

/*
Function: ship_sunk
Date Created: 11/6/2019
Date Modified: 11/6/2019
Description: checks if a ship is sunk and prints it out to the outfile
Input Parameters: int player, int carrier, int battle, int cruiser, int sub, int dest, int *pcarrier, int* pbattle, int*pcrusiser,
	int* psub, int* pdest, FILE* outfile
Returns: void
*/
void ship_sunk(int player, int carrier, int battle, int cruiser, int sub, int dest, int *pcarrier, int* pbattle, int*pcrusiser,
	int* psub, int* pdest, FILE* outfile)
{
	char name[100] = "Player 1";

	if (player == 2)
	{
		strcpy(name, "Computer");
	}

	if (carrier == 5 )
	{
		printf("Carrier is sunk!\n");
		fprintf(outfile, "%s: has sunk the carrier!\n", name);
		*pcarrier = 6;
	}
	else if (battle == 4)
	{
		printf("Battleship is sunk!\n");
		fprintf(outfile, "%s: has sunk the battleship!\n", name);
		*pbattle = 6;
	}
	else if (cruiser == 3)
	{
		printf("Cruiser is sunk!\n");
		fprintf(outfile, "%s: has sunk the cruiser!\n", name);
		*pcrusiser = 6;
	}
	else if (sub == 3)
	{
		printf("Submarine is sunk!\n");
		fprintf(outfile, "%s: has sunk the submarine!\n", name);
		*psub = 6;
	}
	else if (dest == 2)
	{
		printf("Destroyer is sunk!\n");
		fprintf(outfile, "%s: has sunk the destroyer!\n", name);
		*pdest = 6;
	}
}
