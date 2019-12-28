#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
//#include<libgen.h>


void shuffle(game);

#define DECKSIZE 52
#define NCARDS 13
#define PASSES 8192

typedef struct
{
	int t;
	int np;
	int nd;
	int d[];
}game;


void main()
{
	int option;
	int shuf;
	game *g = malloc(sizeof(g));

	srand(time(NULL));

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
			scanf("%d", &g->np);
		} while (g->np < 2 || g->np > 4);

		do {
			printf("\nPlayer 1, enter number of decks: ");
			scanf("%d", &g->nd);
			printf("\n");
		} while (g->nd < 1 || g->nd > 4);

		for (int i = 0; i < DECKSIZE * g->nd; ++i)
		{
			g->d[i] = (i % NCARDS) + 2;
			printf("%d ", g->d[i]);
			if (g->d[i] == 14) {
				printf("\n");
			}
		}

		shuffle(g);
		do {
			printf("\n\nShuffle Again Yes or No(0 or 1): ");
			scanf("%d", &shuf);

			if (shuf == 0) {
				shuffle(g);
			}
		} while (shuf != 1);

		printf("\n\nDeck Shuffled");
	}
	else // Load Game
	{
		
	}

	_getch();
}

void shuffle(game *g)
{
	int i;
	int j;
	int tmp;
	int n = PASSES;

	printf("\n\n");


	while (n--)
	{
		i = rand() % (DECKSIZE);
		j = rand() % (DECKSIZE);

		tmp = g->d[i];
		g->d[i] = g->d[j];
		g->d[j] = tmp;
	}

	j = 1;
	for (i = 0; i < DECKSIZE; ++i)
	{
		++j;
		printf("%2d ", g->d[i]);
		if (j % 14 == 0) {
			printf("\n");
			j = 1;
		}
	}
}