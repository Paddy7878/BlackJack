#include<stdio.h>
#include<conio.h>

void main()
{
	int option, numOfPlayers, numOfDecks;

	printf("============================================\n");
	printf("=           WELCOME TO BLACKJACK           =\n");
	printf("============================================\n");

	do {
		printf("\n1. New Game\n");
		printf("2. Load Game\n");
		printf("Option: ");
		scanf("%d", &option);
	} while (option != 1 && option != 2);

	if (option == 1) // New Game
	{
		do {
			printf("\nEnter number of players (2-4)? ");
			scanf("%d", &numOfPlayers);
		} while (numOfPlayers < 2 || numOfPlayers > 4);

		do {
			printf("\nPlayer 1, enter number of decks: ");
			scanf("%d", &numOfDecks);
		} while (numOfDecks < 1 || numOfDecks > 4);
	}
	else if (option == 2) // Load Game
	{

	}

	getch();
}