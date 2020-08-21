#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define NUM_ROWS_BOARD 11
#define NUM_COLS_BOARD 11
#define SIZE_CARRIER 5
#define SIZE_BATTLESHIP 4
#define SIZE_CRUSIER 3
#define SIZE_SUBMARINE 3
#define SIZE_DESTORYER 2
#define CARRIER 'c'
#define BATTLESHIP 'b'
#define CRUSIER 'r'
#define SUBMARINE 's'
#define DESTORYER 'd'

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

typedef struct position
{
	int row;
	int col;
} Position;

typedef struct cell
{
	char vehicle;
	int occupied;
	int shot;
	Position location;
} Cell;

void intro_page(void);

void init_board(Cell board[][NUM_COLS_BOARD],
	int rows, int cols);

void print_ship_board(Cell board[][NUM_COLS_BOARD],
	int rows, int cols);

void print_shot_board(Cell board[][NUM_COLS_BOARD],
	int rows, int cols);

void manually_place_ships(Cell board[][NUM_COLS_BOARD],
	int rows, int cols);

void randomly_place_ships(Cell board[][NUM_COLS_BOARD],
	int rows, int cols);

int pick_first(void);

void get_coordinates(Cell board[][NUM_COLS_BOARD], int* xpos, int* ypos);

void get_random_coordinates(Cell board[][NUM_COLS_BOARD], int* xpos, int* ypos);

char get_orientation(void);

char get_random_orientation(void);

char guess_shot(Cell board[][NUM_COLS_BOARD], FILE* outfile);

char random_guess_shot(Cell board[][NUM_COLS_BOARD], FILE* outfile);

char get_yes_no(void);

void determine_shot(char c, int c1, int b1, int r1, int s1,
	int d1, int h1, int m1, int t1, int* pc, int* pb, int* pr, int* ps, int* pd, int* ph, int* pm, int* total);

void ship_sunk(int player, int carrier, int battle, int cruiser, int sub, int dest, int* pcarrier, int* pbattle, int* pcrusiser,
	int* psub, int* pdest, FILE* outfile);
