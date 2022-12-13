#pragma once
/*
PROJ: PA 6
AUTH: Alan Sun
DATE LAST MODIFIED: NOV 11 2022
INSTR: Andy O'Fallon
COURSE: CPT-S 121
PURPOSE: To play the game Battleship with multiple players
*/
#ifndef HEADER_H
#define HEADER_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//Constant Macros
#define ROWS 10
#define COLS 10

#define WATER         '~'
#define HIT           'H'
#define MISS          'M'

//Struct Definitions
typedef struct playerstats
{
	int numHits;
	int numMisses;
	int totalShots;
	double hitMissRatio;
} PlayerStats;

typedef struct ship
{
	char symbol;
	int length;
	char *ship_type;
} Ship;

typedef struct coordinate 
{
	int row;
	int column;
} Coordinate;

typedef struct cell 
{
	char symbol;
	Coordinate position;
} Cell;

//Function Prototypes
int gameplay_menu(void);
void print_game_rules(void);
void initializeGameBoard(Cell gameBoard[][COLS]);
void printGameBoard(Cell gameBoard[][COLS], bool isOwner);
void putShipOnGameBoard(Cell gameBoard[][COLS], Ship ship, Coordinate position, bool isHorizontal);
void manuallyPlaceShipsOnGameBoard(Cell gameBoard[][COLS], Ship ships[]);
void randomlyPlaceShipsOnGameBoard(Cell gameBoard[][COLS], Ship ships[]);
int updateGameBoard(Cell gameBoard[][COLS], Coordinate target);
Coordinate getTarget(void);
void outputMove(int player, Coordinate target, int hit, FILE* outfile);
bool checkSunkShip(int sunkShip[][5], int player, char shipSymbol, FILE* stream);

#endif