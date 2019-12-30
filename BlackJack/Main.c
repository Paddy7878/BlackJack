#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>

void shuffle(game);
void deal(game, player);
int getFace(int card);
int getSuit(int card);
int createCard(int face, int suit);
void printCard(int card);
void delay(int numSeconds);
void playGame(game, player);
int calculatePoints(player, int j);
void hitMe(player);

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
	int points;
}player;


void main()
{
	int option;
	int shuf;
	game *g = malloc(sizeof(g));
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

		printf("Starting new game.");
		for (int i = 0; i < 3; ++i)
		{
			delay(1);
			printf(".");
		}

		for (int i = 0; i <= DECKSIZE * g->nd; ++i)
		{
			g->d[i] = i;
		}

		printf("\n\nDealer shuffles the deck");
		for (int i = 0; i < 3; ++i)
		{
			delay(1);
			printf(".");
		}
		shuffle(g);
		delay(1);
		printf("\n\nDealer deals the cards to the players");
		for (int i = 0; i < 3; ++i)
		{
			delay(1);
			printf(".");
		}
		deal(g, players);
		delay(1);
		printf("\n\nThe Dealer gets the hole card and places it face down\n");
		delay(1);
		printf("\nThe Dealers face up card is the");
		printCard(players[0].h[1]);
		for (int i = 1; i < g->np; i++)
		{
			delay(2);
			printf("\n\nPlayer %d gets their cards");
		}

		playGame(g, players);

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
}

int getFace(int card)
{
	return card % 13;
}

int getSuit(int card)
{
	return card / 13;
}

int createCard(int face, int suit)
{
	return face * suit;
}

void printCard(int card)
{
	static char *suits[4] = { "Spades", "Hearts", "Diamonds", "Clubs" };
	static char *faces[13] = { "2", "3", "4", "5", "6", "7", "8", "9", "10",
							"Jack", "Queen", "King", "Ace" };

	printf(" %s of %s", faces[getFace(card)], suits[getSuit(card)]);
}

void delay(int numSeconds)
{
	// Converting time into milli_seconds 
	int milliSeconds = 1000 * numSeconds;

	// Storing start time 
	clock_t startTime = clock();

	// looping till required time is not achieved 
	while (clock() < startTime + milliSeconds);
}

void playGame(game *g, player players[])
{
	int points = 0;
	int option;

	for (int j = 0; j < 4; j++)
	{
		calculatePoints(players, j);
	}


	for (int i = 1; i < g->np; i++)
	{
		do
		{
			delay(1);
			printf("\n\nPlayer %d's go", i);
			printf("\n1. Stand");
			printf("\n2. Hit");
			printf("\n3. Split");
			scanf("%d", &option);

			switch (option)
			{
				case 2:
					hitMe(players[4]);
					break;
			}
		} while (option == 2);
	}
}

void hitMe(player players)
{

}

int calculatePoints(player players[], int p)
{
	int points;
	int face;
	
	
	for (int i = 0; i < 5; i++)
	{
		face = getFace(players[p].h[i]);
		printf("");
		switch (face)
		{

		}
	}

	return points;
}