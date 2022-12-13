#include "Header.h"

int main(void)
{
	FILE* outfile = fopen("battleship.log", "w");
	int option = 0, player = 0, hit = 0;

	//hits, misses, total shots, hit/miss ratio
	PlayerStats players[2] = { {0, 0, 0, 0.0}, {0, 0, 0, 0.0} };
	//tracks parts of the ship destroyed
	short sunkShip[2][5] = { {5, 4, 3, 3, 2}, {5, 4, 3, 3, 2} };  

	Cell playerOneGameBoard[ROWS][COLS];
	Cell playerTwoGameBoard[ROWS][COLS];

	Coordinate target; 
	Coordinate targetAI;

	Ship ships[5] = { {'C', 5, "Carrier"}, {'B', 4, "Battleship"}, {'R', 3, "Cruiser"}, {'S', 3, "Submarine"}, {'D', 2, "Destroyer"} };

	int a = 1;

	// Set rand string
	srand((unsigned int)time(NULL));

	while (a) {
		a = gameplay_menu();
		if (a == -1) {
			printf("Bye bye!");
			return 0;
		}
	}

	initializeGameBoard(playerOneGameBoard);
	initializeGameBoard(playerTwoGameBoard);

	system("cls");

	printf("Please select from the following menu:\n");
	printf("[1] Manually\n");
	printf("[2] Randomly\n");
	scanf("%d", &option);

	do
	{
		if (option == 1) {
			manuallyPlaceShipsOnGameBoard(playerOneGameBoard, ships);
		}
		if (option == 2) {
			randomlyPlaceShipsOnGameBoard(playerOneGameBoard, ships);
		}
		else {
			printf("Invalid option. Please reenter: \n");
			scanf("%d", &option);
		}
	} while (option != 1 && option != 2);



	randomlyPlaceShipsOnGameBoard(playerTwoGameBoard, ships);
	printf("Player 2 (Computer's) board has been generated.\n");

	player = rand() % 2 + 1;
	printf("Player %d has been randomly selected to go first.\n", player);
	system("pause\n");
	system("cls");


	while (players[0].numHits < 17 || players[1].numHits < 17)
	{
		if (player == 2)
		{
			target.row = rand() % 10;
			target.column = rand() % 10;
			hit = updateGameBoard(playerOneGameBoard, target);
			
		}
		else
		{
			printf("Player 2's Board:\n");
			printGameBoard(playerTwoGameBoard, false);
			printf("Player 1's Turn:\n");

			// Prompts user to enter target
			do {
				target = getTarget();
				hit = updateGameBoard(playerTwoGameBoard, target);
				if (!checkSunkShip(sunkShip, 1, playerTwoGameBoard, outfile))
				{

					outputMove(player, target, hit, outfile);
				}
				if (hit == -1)
				{
					printf("Try inputting another target!\n");
				}
			} while (hit == -1);
		}
		players[player - 1].totalShots++;
			if (hit == 0) {
				players[player - 1].numMisses++;
			}
			else {
				players[player - 1].numHits++;
			}
		player = player % 2 + 1;
	}

	players[0].totalShots = players[0].numHits + players[0].numMisses;
	players[0].hitMissRatio = ((double)players[0].numHits / (double)players[0].numMisses) * 100;
	players[1].totalShots = players[1].numHits + players[1].numMisses;
	players[1].hitMissRatio = ((double)players[1].numHits / (double)players[1].numMisses) * 100;
	fprintf(outfile, "+===================================================\n");
	fprintf(outfile, "|                    PLAYER STATS                   \n");
	fprintf(outfile, "+---------------------------------------------------\n");
	fprintf(outfile, "| PLAYER 1 : %d hits                                \n", players[0].numHits);
	fprintf(outfile, "|            %d misses                              \n", players[0].numMisses);
	fprintf(outfile, "|            %d total shots                         \n", players[0].totalShots);
	fprintf(outfile, "|            %.2lf%% hit/miss ratio                 \n", players[0].hitMissRatio);
	fprintf(outfile, "| PLAYER 2 : %d hits                                \n", players[1].numHits);
	fprintf(outfile, "|            %d misses                              \n", players[1].numMisses);
	fprintf(outfile, "|            %d total shots                         \n", players[1].totalShots);
	fprintf(outfile, "|            %.2lf%% hit/miss ratio                 \n", players[1].hitMissRatio);
	fprintf(outfile, "+===================================================");

	fclose(outfile);
	printf("good game!");
	return 0;
}