/*
PROJ: PA 5
AUTH: Alan Sun
DATE LAST MODIFIED: OCT 18 2022
INSTR: Andy O'Fallon
COURSE: CPT-S 121
PURPOSE: To play the game Yahtzee with multiple players
*/

#include "Header.h"

int gameplay_menu(void)
{
	int option = 0, play_game = 0;

	printf("************************************************ Welcome to Battleship! ************************************************\n\n");
	 
	printf("Choose an option by entering the corresponding number:\n1. Print game rules\n2. Start a game of Battleship\n3. Exit\n");

	scanf("%d", &option);
	if (option == 1) {
		system("cls");
		printf("************************************************ Welcome to Battleship! ************************************************\n");

		print_game_rules();
		play_game = 1;
	}
	else if (option == 2)
	{
		return 0;
	}
	else if (option == 3) {
		play_game = -1;
	}
	else {
		system("cls");
		printf("Enter a valid response.\n");
	}
	return play_game;

}

/************************************************
*Fx: print_game_rules(void)
*Date Last Mod: 10-26-2022
*Purpose: prints game rules
*Precondition:
*Input:
*Output:
*************************************************/
void print_game_rules(void)
{
	printf("The object of Battleship is to try and sink all of the other player's before they sink all of your ships.\n");
	printf("All of the other player's ships are somewhere on the opponent's board.\n");
	printf("You try and hit them by calling out the coordinates of one of the squares on the board.\n");
	printf("The other player also tries to hit your ships by calling out coordinates.\n");
	printf("Neither you nor the other player can see the other's board so you must try to guess where they are.\n");
	printf("Each player places the 5 ships somewhere on their board.  The ships can only be placed vertically or horizontally.\n");
	printf("Diagonal placement is not allowed. No part of a ship may hang off the edge of the board.");
	printf("Ships may not overlap each other.  No ships may be placed on another ship.");
	printf("Once the guessing begins, the players may not move the ships.");
	printf("There are five different ships and you have one of each.\n");
	printf("\t Carrier - occupies 5 spaces\n");
	printf("\t Battleship - occupies 4 spaces\n");
	printf("\t Cruiser - occupies 3 spaces\n");
	printf("\t Submarine - occupies 3 spaces\n");
	printf("\t Destroyer - occupies 2 spaces\n");
	printf("Player's take turns guessing by calling out the coordinates.\n");
	printf("The opponent responds with hit or miss as appropriate.\n");
	printf("For example, if you call out F6 and your opponent does not have any ship located at F6,\n");
	printf("your opponent would respond with miss.\n");
	printf("When all of the squares that one your ships occupies have been hit, the ship will be sunk.\n");
	printf("The player whose ship was sunk should announce hit and sunk\n");
	printf("As soon as all of one player's ships have been sunk, the game ends.\n");
}

void initializeGameBoard(Cell gameBoard[][COLS]) {
	int i = 0, j = 0;

	for (i = 0; i < ROWS; i++)
		for (j = 0; j < COLS; j++) {
			gameBoard[i][j].symbol = WATER;
			gameBoard[i][j].position.row = i;
			gameBoard[i][j].position.column = j;
		}
}

void printGameBoard(Cell gameBoard[][COLS], bool isOwner) {
	int i = 0, j = 0;
	
	printf("\t ________________________\n");
	printf("\t | 1 2 3 4 5 6 7 8 9 10 | \n");

	for (i = 0; i < ROWS; i++) 
	{
		printf("%d\t | ", i + 1);

		for (j = 0; j < COLS; j++)
		{
			if (isOwner)
			{
				printf("%c ", gameBoard[i][j].symbol);
			}
			else 
			{
				switch (gameBoard[i][j].symbol) 
				{
				case HIT:   printf("%c ", HIT);   break;
				case MISS:  printf("%c ", MISS);  break;
				case WATER:
				default:    printf("%c ", WATER); break;
				}
			}
		}

		printf(" | ");
		putchar('\n');
	}

	printf("\t ________________________\n");
}

void putShipOnGameBoard(Cell gameBoard[][COLS], Ship ship, Coordinate position, bool isHorizontal) 
{
	if (isHorizontal) 
	{ 
		for (int i = 0; i < ship.length; i++)
		{
			gameBoard[position.row][position.column + i].symbol = ship.symbol;
		}

	}
	else
	{
		for (int i = 0; i < ship.length; i++)
		{
			gameBoard[position.row + i][position.column].symbol = ship.symbol;
		}
	}
}

void manuallyPlaceShipsOnGameBoard(Cell gameBoard[][COLS], Ship ships[]) {
	int x = 0, y = 0, temp;
	bool isHorizontal;

	Coordinate position[5];
	bool isValid = false;

	for (int i = 0; i < 5; i++) {

		while (true) {
			system("cls");
			printGameBoard(gameBoard, true);
			printf("Please enter whether the %s (%d) is vertical or horizontal (0 for vertical, 1 for horizontal): \n", ships[i].ship_type, ships[i].length);
			scanf("%d", &temp);

			while (temp != 0 && temp != 1)
			{
				printf("Invalid input. Please input 0 for vertrical, 1 for horizontal: \n");
				scanf("%d", &temp);
			}

			//swapped
			isHorizontal = temp;
			
			printf("Please enter the top/leftmost cell to place the %s across (x y) or input -1 for either to restart: \n", ships[i].ship_type);
			scanf("%d %d", &x, &y);

			if (x == -1 || y == -1)
			{
				continue;
			}

			for (int j = 0; j < ships[i].length; j++)
			{
				if (gameBoard[y - 1][x - 1].symbol != WATER) {
					printf("%s is overlapping another ship. Please reinput coordinates: \n", ships[i].ship_type);
					scanf("%d %d", &x, &y);
					j = 0;
				}
			}

			if (isHorizontal)
			{

				while (x - 1 > 10 - ships[i].length || (y > 10 && y < 1))
				{
					printf("%s is hanging off board. Please reinput coordinates: \n", ships[i].ship_type);
					scanf("%d %d", &x, &y);
				}
			}
			else
			{
				while (y - 1 > 10 - ships[i].length || (x > 10 && x < 1))
				{
					printf("%s is hanging off board. Please reinput coordinates: \n", ships[i].ship_type);
					scanf("%d %d", &x, &y);
				}
			}
			position[i].row = y - 1;
			position[i].column = x - 1;

			putShipOnGameBoard(gameBoard, ships[i], position[i], isHorizontal);
			break;
		}
		printGameBoard(gameBoard, true);
	}
}

void randomlyPlaceShipsOnGameBoard(Cell gameBoard[][COLS], Ship ships[]) {
	Coordinate position;
	int x = 0, y = 0, isHorizontal;
	bool isValid = true;

	//loop through ships
	for (int i = 0; i < 5; i++) {
		//generate until valid
		while (true)
		{
			isHorizontal = rand() % 2;
			if (isHorizontal)
			{
				//generate x/y coordinates
				x = rand() % (11 - ships[i].length);
				y = rand() % 10;

				//validate each coordinate
				for (int j = 0; j < ships[i].length; j++)
				{
					//if invalid, generate new coordinates and reset j
					if (gameBoard[y][x + j].symbol != WATER)
					{
						isValid = false;
						break;
					}
				}
			}
			else
			{
				//generate x/y coordinates
				y = rand() % (11 - ships[i].length);
				x = rand() % 10;
				//validate each coordinate
				for (int j = 0; j < ships[i].length; j++)
				{
					//if invalid, generate new coordinates and reset j
					if (gameBoard[y + j][x].symbol != WATER)
					{
						isValid = false;
						break;
					}
				}
			}
			if (!isValid)
			{
				continue;
			} else 
			{
				//once valid, save position and exit loop
				position.row = y;
				position.column = x;
				break;
			}
		}
		//place ship on board
		putShipOnGameBoard(gameBoard, ships[i], position, isHorizontal);
	}
}

int updateGameBoard(Cell gameBoard[][COLS], Coordinate target) {
	switch (gameBoard[target.row][target.column].symbol) {
		//miss
	case WATER:
		gameBoard[target.row][target.column].symbol = MISS;
		return 0;
		//hit
	case 'C':
	case 'B':
	case 'R':
	case 'S':
	case 'D':
		gameBoard[target.row][target.column].symbol = HIT;
		return 1;
		//invalid input
	default:
		return -1;
	}
}

Coordinate getTarget(void) 
{
	Coordinate target;

	printf("Enter coordinate to target (x y): ");
	scanf("%d %d", &target.row, &target.column);

	return target;
}

void outputMove(int player, Coordinate target, int hit, FILE* outfile) 
{
	char* str = hit == 1 ? "hit" : "missed";
	fprintf(outfile, "Player %d %s at (%d, %d)!\n", player, str, target.row, target.column);
}

bool checkSunkShip(int sunkShip[][5], int player, char shipSymbol, FILE* stream) 
{
	bool sank = false;

	switch (shipSymbol) 
	{
	case 'C':
		if (--sunkShip[player][0] == 0) 
		{
			printf("> Player %d's Carrier sank!\n", player);

			/* Write to battleship.log */
			fprintf(stream, "Player %d's Carrier sank!\n", player);

			sank = true;
		}
		break;

	case 'B':
		if (--sunkShip[player][1] == 0)
		{
			printf("> Player %d's Battleship sank!\n", player);
			
			/* Write to battleship.log */
			fprintf(stream, "Player %d's Battleship sank!\n", player);

			sank = true;
		}
		break;

	case 'R':
		if (--sunkShip[player][2] == 0)
		{
			printf("> Player %d's Cruiser sank!\n", player);

			/* Write to battleship.log */
			fprintf(stream, "Player %d's Cruiser sank!\n", player);

			sank = true;
		}
		break;

	case 'S':
		if (--sunkShip[player][3] == 0) {
			printf("> Player %d's Submarine sank!\n", player);

			/* Write to battleship.log */
			fprintf(stream, "Player %d's Submarine sank!\n", player);
		   
			sank = true;
		}
		break;

	case 'D':
		if (--sunkShip[player][4] == 0) {
			printf("> Player %d's Destroyer sank!\n", player);

			/* Write to battleship.log */
			fprintf(stream, "Player %d's Destroyer sank!\n", player);

			sank = true;
		}
		break;
	}

	return true;
}