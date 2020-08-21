#include "header.h"

/*
	Name: Koji Natsuhara

	Date: 11/6/2019

	Description: The purpose of the PA6 is to Write a program that simulates the game of Battleship. The game 
	will be completely text-based (see Sample Execution). Battleship is a two player Navy game. The objective 
	of the game is to sink all ships in your enemy's fleet. The Player to sink his/her enemy's fleet first wins. 
	Both players' fleets consist of 5 ships that are hidden from the enemy. Each ship may be differentiated by 
	its "size" (besides the Cruiser and Submarine) or number of cells it expands on the game board. The Carrier 
	has 5 cells, Battleship has 4 cells, Cruiser has 3 cells, Submarine has 3 cells, and the Destroyer has 2 cells.

	IN THIS PROGRAM I WILL HAVE TO:
	1. Open and close files
	2. Read, write to, and update files
	3. Apply standard library functions: fopen (), fclose (), fscanf (), and fprintf ()
	4. Compose decision statements ("if" conditional statements)
	5. Create and utilize compound conditions
	6. Be able to include while(), do-while(), and for() loops
	7. Implement and apply 2-dimenional arrays
	8. Define and apply structs in C
*/

int main(void)
{
	int c1 = 0, b1 = 0, r1 = 0, s1 = 0, d1 = 0, h1 = 0, m1 = 0, t1 = 0;
	int c2 = 0, b2 = 0, r2 = 0, s2 = 0, d2 = 0, h2 = 0, m2 = 0, t2 = 0;
	double ratio1 = 0.0, ratio2 = 0.0;
	int first = 0;
	char place = '\0', ship1 = '\0', ship2 = '\0';
	srand(time(NULL));

	FILE* outfile = NULL;
	outfile = fopen("output.log", "w");

	Cell board1[NUM_ROWS_BOARD][NUM_COLS_BOARD] = { {{'\0', 0, 0, {0, 0}}} };
	Cell board2[NUM_ROWS_BOARD][NUM_COLS_BOARD] = { {{'\0', 0, 0, {0, 0}}} };

	init_board(board1, NUM_ROWS_BOARD, NUM_COLS_BOARD);
	init_board(board2, NUM_ROWS_BOARD, NUM_COLS_BOARD);
	//START GAME
	intro_page();
	
	//PLACING SHIPS
	printf("Would you like to place your ships manually? (Y/N): ");
	place = get_yes_no();

	if (place == 'Y')
	{
		manually_place_ships(board1, NUM_ROWS_BOARD, NUM_COLS_BOARD);
	}
	else
	{
		printf("======Player 1: Ship Board======\n");
		randomly_place_ships(board1, NUM_ROWS_BOARD, NUM_COLS_BOARD);
	}

	printf("======Computer: Ship Board======\n");
	randomly_place_ships(board2, NUM_ROWS_BOARD, NUM_COLS_BOARD);

	system("pause");
	system("cls");
	//WHO GOES FIRST
	first = pick_first();


	//GUESSING AND SHOOTING
	if (first == 0)
	{
		printf("Player 1 goes first!\n");
		while (h1 < 17 && h2 < 17)
		{
			//PLAYER 1 GOES FIRST
			print_shot_board(board2, NUM_ROWS_BOARD, NUM_COLS_BOARD);
			ship1 = guess_shot(board2, outfile);
			determine_shot(ship1, c2, b2, r2, s2, d2, h1, m1, t1, &c2, &b2, &r2, &s2, &d2, &h1, &m1, &t1);
			ship_sunk(1, c2, b2, r2, s2, d2, &c2, &b2, &r2, &s2, &d2, outfile);
			print_shot_board(board2, NUM_ROWS_BOARD, NUM_COLS_BOARD);
			ship2 = random_guess_shot(board1, outfile);
			determine_shot(ship2, c1, b1, r1, s1, d1, h2, m2, t2, &c1, &b1, &r1, &s1, &d1, &h2, &m2, &t2);
			ship_sunk(2, c1, b1, r1, s1, d1, &c1, &b1, &r1, &s1, &d1, outfile);
			system("pause");
			system("cls");
		}
	}
	else
	{
		//COMPUTER GOES FIRST
		printf("Computer goes first!\n");
		while (h1 < 17 && h2 < 17)
		{
			ship2 = random_guess_shot(board1, outfile);
			determine_shot(ship2, c1, b1, r1, s1, d1, h2, m2, t2, &c1, &b1, &r1, &s1, &d1, &h2, &m2, &t2);
			ship_sunk(2, c1, b1, r1, s1, d1, &c1, &b1, &r1, &s1, &d1, outfile);
			print_shot_board(board2, NUM_ROWS_BOARD, NUM_COLS_BOARD);
			ship1 = guess_shot(board2, outfile);
			determine_shot(ship1, c2, b2, r2, s2, d2, h1, m1, t1, &c2, &b2, &r2, &s2, &d2, &h1, &m1, &t1);
			ship_sunk(1, c2, b2, r2, s2, d2, &c2, &b2, &r2, &s2, &d2, outfile);
			print_shot_board(board2, NUM_ROWS_BOARD, NUM_COLS_BOARD);
			system("pause");
			system("cls");
		}
	}

	//DETERMINE WINNER AND PRINT TO LOGFILE
	if (h1 > h2)
	{
		printf("Player 1 has won the game!\n");
		fprintf(outfile, "Player 1 wins, Computer loses\n");
	}
	else
	{
		printf("Computer has won the game!\n");
		fprintf(outfile, "Computer wins, Player 1 loses\n");
	}

	//CALCULATE hit/miss ratio
	ratio1 = ((double)h1 / m1);
	ratio2 = ((double)h2 / m2);

	//PRINT STATS TO LOGFILE

	fprintf(outfile, "-------Player 1 Stats------- \n");
	fprintf(outfile, "Number of Hits: %d\n", h1);
	fprintf(outfile, "Number of Misses: %d\n", m1);
	fprintf(outfile, "Total Shots: %d\n", t1);
	fprintf(outfile, "Hit/Miss Ratio: %.2lf\n", ratio1);

	fprintf(outfile, "-------Computer Stats------- \n");
	fprintf(outfile, "Number of Hits: %d\n", h2);
	fprintf(outfile, "Number of Misses: %d\n", m2);
	fprintf(outfile, "Total Shots: %d\n", t2);
	fprintf(outfile, "Hit/Miss Ratio: %.2lf\n", ratio2);


	fclose(outfile);

	return 0;
}