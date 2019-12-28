#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
//#include<libgen.h>


void shuffle(game);
void deal(game, player);

#define DECKSIZE 52
#define NCARDS 13
#define PASSES 8192
#define PLAYERS 4

typedef struct
{
	int t;
	int np;
	int nd;
	int d[];
}game;

typedef struct
{
	int h[5];
}player;


void main()
{
	int option;
	int shuf;
	game *g = malloc(sizeof(g));
	//player *p = malloc(sizeof(p));
	player players[3];

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
			/*printf("%d ", g->d[i]);
			if (g->d[i] == 14) {
				printf("\n");
			}*/
		}

		shuffle(g);
		deal(g, players);

		/*do {
			printf("\n\nShuffle Again Yes or No(0 or 1): ");
			scanf("%d", &shuf);

			if (shuf == 0) {
				shuffle(g);
			}
		} while (shuf != 1);*/

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

	while (n--)
	{
		i = rand() % (DECKSIZE * g->nd);
		j = rand() % (DECKSIZE * g->nd);

		tmp = g->d[i];
		g->d[i] = g->d[j];
		g->d[j] = tmp;
	}

	j = 1;
	for (i = 0; i < DECKSIZE * g->nd; ++i)
	{
		++j;
		/*printf("%2d ", g->d[i]);
		if (j % 14 == 0) {
			printf("\n");
			j = 1;
		}*/
	}
}

void deal(game *g, player players[])
{
	int card = 0;
    players[3];
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < g->np; i++)
		{
			players[i].h[j] = g->d[card];
			g->d[card] = 0;
			card++;
		}
	}

	printf("\nDealer got %d and %d\n", players[0].h[0], players[0].h[1]);
	for (int i = 1; i < g->np; i++)
	{
		printf("\nPlayer %d got %d and %d\n", i, players[i].h[0], players[i].h[1]);
	}
}