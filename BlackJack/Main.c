#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

// created a struct for Game
typedef struct
{
	int t; // turn
	int np; // num players
	int nd; // num decks
	int r; // round
	int d[]; // deck of cards
}Game;

// created a struct for players
typedef struct
{
	int h[5]; // hand
	int h1[5]; // second hand if split
	int points; // points of player
	int cardNo; // amount of cards in hand
	int w; // wins
	int b; // bust
	int ace; 
	int bj; // blackjack
	int split;
}player;

// prototype all functions
Game * init(player players[]);
void shuffle(Game *g);
void deal(Game *g, player players[]);
int getFace(int card);
int getSuit(Game *g, int card);
void printCard(Game *g, int card);
void delay(int numSeconds);
void hitMe(Game *g, player players[]);
void split(Game *g, player players[]);
void playGame(Game *g, player players[]);
int calculatePoints(Game *g, player players[]);
void hitMe(Game *g, player players[]);
int getPoint(int point);
void checkForBlackJack(Game *g, player players[]);
void winners(Game *g, player players[]);
void save(Game *g, player players[]);
void loadGame(Game *g, player players[]);

// declare constants
#define DECKSIZE 52
#define NCARDS 13
#define PASSES 8192
#define SAVEFILE "save.txt"

// main method
int main(int argc,
	char *argv[])
{
	int option;
	Game *g = NULL; // initialise pointer *g to NULL
	player players[4]; // create array for players
	srand(time(NULL)); // intialise the PRNG

	// opening header of game
	printf("============================================\n");
	printf("=           WELCOME TO BLACKJACK           =\n");
	printf("============================================\n");

	// do/while to find out whether to start new game or load game
	do {
		printf("\n1. New Game\n");
		printf("2. Load Game\n");
		printf("Option: ");
		scanf("%d", &option);
	} while (option != 1 && option != 2);

	if (option == 1)
	{
		g = init(players); // initialise a new game
	}
	else {
		loadGame(g, players); // load the game from save
	}

	playGame(g, players); // play game after game has been loaded or initialised

	free(g); // free memory allocated

	return EXIT_SUCCESS; // exit success
}

// initialise game
Game * init(player players[])
{
	Game *g = malloc(sizeof(g)); // allocate memory to Game *g

	// check I have enough memory
	if (!g) {
		printf("\nError: Insufficient Memory\n");
	}

	// ask for the number of players and validate
	do {
		printf("\nEnter number of players (2-4)? ");
		scanf("%d", &g->np);
	} while (g->np < 2 || g->np > 4);

	// ask for number of decks and validate
	do {
		printf("\nPlayer 1, enter number of decks: ");
		scanf("%d", &g->nd);
		printf("\n");
	} while (g->nd < 1 || g->nd > 4);

	// create deck from 0 - 51
	for (int i = 0; i < DECKSIZE * g->nd; ++i)
	{
		g->d[i] = i;
	}

	printf("Starting new game.");
	for (int i = 0; i < 2; ++i)
	{
		delay(1);
		printf(".");
	}

	printf("\n");

	// initialise a few variables in the structs
	for (int i = 0; i < g->np; i++)
	{
		players[i].bj = 0;
		players[i].cardNo = 2;
		players[i].ace = 0;
		players[i].b = 0;
		players[i].w = 0;
	}
	g->r = 1; // round 1
	g->t = 0; // turn 0

	return g; // return the game g
}

// play the game
void playGame(Game *g, player players[])
{
	int option;
	if (g->r > 0) // Round Header
	{
		printf("\n============================================\n");
		printf("=                 Round %d                 =\n", g->r);
		printf("============================================\n");
	}

	// dealer shuffles every round
	printf("\n\nDealer shuffles the deck");
	for (int i = 0; i < 2; ++i)
	{
		delay(1);
		printf(".");
	}
	shuffle(g);
	delay(1);

	// dealer calls the deal function
	printf("\n\nDealer deals the cards to the players");
	for (int i = 0; i < 3; ++i)
	{
		delay(1);
		printf(".");
	}
	deal(g, players);
	delay(1);

	// don't show the hole card
	printf("\n\nThe Dealer gets the hole card and places it face down");
	delay(1);
	// show the face up card
	printf("\nThe Dealers face up card is the ");
	printCard(g, players[0].h[1]);

	// if dealer has an ace or picture card, he must check for BlackJack
	if (getPoint(players[0].h[1]) == 10 || getPoint(players[0].h[1]) == 11)
	{
		printf("\nDealer peeks at his facedown card");
		checkForBlackJack(g, players); // checks for BlackJack
	}

	// calculate points for each player after deal
	for (int j = 0; j < g->np; j++)
	{
		g->t = j;
		players[j].points = calculatePoints(g, players);
		if (players[j].points == 21)
		{
			checkForBlackJack(g, players); // check for BlackJack
		}
	}

	delay(1);
	// if the dealer did not get a BlackJack we will play on
	if (players[0].points != 21)
	{
		// for loop to go through each players turn
		for (g->t = 1; g->t < g->np; g->t++)
		{
			// players go until they choose not to hit 
			do
			{
				delay(2);
				// players go header
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n============================================\n");
				printf("=             Player %d's go                =\n", g->t);
				printf("============================================\n");
				printf("     Points");
				printf("                    Cards\n       %2d", players[g->t].points); // display player points
				// display the players cards everytime its their turn
				for (int i = 0; i < players[g->t].cardNo; i++)
				{
					if (i == 0) {
						printf("                   ");
					}
					else {
						printf("                            ");
					}
					printCard(g, players[g->t].h[i]);
				}

				printf("\n1. Stand"); // option to stand
				printf("\n2. Hit"); // get another card
				printf("\n3. Split"); // split your hand into two hands
				printf("\n4. Save and Exit"); // save and exit
				printf("\nOption: ");
				scanf("%d", &option);

				if (option == 1) // stand
				{
					printf("\nYou choose to Stand.");
					break;
				}
				else if (option == 2) // hit
				{
					hitMe(g, players);
					if (players[g->t].points > 21)
					{
						break; // break out of loop
					}
				}
				else if (option == 3) // split
				{
					split(g, players);
					break;
				}
				else if (option == 4) // save and exit
				{
					save(g, players);
				}
			} while (option == 2);
		}

		g->t = 0;
		delay(3);
		// dealers header
		printf("\n\n\n\n\n============================================\n");
		printf("=                  Dealer                  =\n");
		printf("============================================\n");
		printf("     Points");
		printf("                    Cards\n       %2d", players[g->t].points); // display points
		// show the dealers hole card and other card(s)
		for (int i = 1; i >= 0; i--)
		{
			if (i == 1) {
				printf("                   ");
			}
			else {
				printf("                            ");
			}
			printCard(g, players[g->t].h[i]);
		}

		// if dealer has soft 17 he can get hit again
		if (players[0].points == 17)
		{
			for (int j = 0; j < players[0].cardNo; j++)
			{
				if (getFace(players[0].h[j] == 12))
				{
					delay(1);
					printf("\nDealer got a soft 17");

					while (players[0].points <= 17)
					{
						delay(1);
						if (players[0].cardNo == 2)
						{
							printf("\nDealer choses to get hit!\n");
						}
						else {
							printf("\nDealer choses to get hit again!\n");
						}
						hitMe(g, players); // call hit me function
					}
				}
			}
		}
		// if dealer has 16 or less points he can get hit again
		if (players[0].points <= 16)
		{
			delay(1);
			printf("\nDealer is only on %d points", players[0].points);
		}
		while (players[0].points <= 16)
		{
			delay(1);
			if (players[0].cardNo == 2)
			{
				printf("\nDealer choses to get hit!\n");
			}
			else {
				printf("\nDealer choses to get hit again!\n");
			}
			hitMe(g, players); // call hit me function
		}
	}
	winners(g, players); // call winners function to  display winners
}

// deal 2 cards to each player
void deal(Game *g, player players[])
{
	int card = 0;

	for (int j = 0; j < 2; j++) // deal everyone one card at a time
	{
		for (int i = 0; i < g->np; i++)
		{
			players[i].h[j] = g->d[card]; // player gets card from deck
			g->d[card] = 0; // set card to 0 so its not used again
			card++; // increment card to give out next card next time
		}
	}
}

// get the face value of card in deck
int getFace(int card)
{
	return card % NCARDS; // returns the card num from 0-12
}

// get the suit value of card in deck
int getSuit(Game *g, int card)
{
	return card / (NCARDS * g->nd); // returns the card suit from 0-3
}

// prints out the card as text
void printCard(Game *g, int card)
{
	// two char arrays of the suits and faces
	static char *suits[4] = { "Spades", "Hearts", "Diamonds", "Clubs" };
	static char *faces[13] = { "2", "3", "4", "5", "6", "7", "8", "9", "10",
							"Jack", "Queen", "King", "Ace" };

	// prints the face and suit whenever function is called
	printf("%s of %s\n", faces[getFace(card)], suits[getSuit(g, card)]);
}

// delay function to add delays to different things
void delay(int numSeconds)
{
	// converting time into milliseconds 
	int milliSeconds = 1000 * numSeconds;

	// storing start time 
	clock_t startTime = clock();

	// looping till required time is not achieved 
	while (clock() < startTime + milliSeconds);
}

// shuffle function
void shuffle(Game *g)
{
	int i;
	int j;
	int tmp;
	int n = PASSES;

	while (n--) // while loop runs until PASSES decrements fully
	{
		// i and j are both given random numbers from 0-51
		i = rand() % (DECKSIZE * g->nd);
		j = rand() % (DECKSIZE * g->nd);

		// use these random numbers to switch random cards in the deck
		tmp = g->d[i];
		g->d[i] = g->d[j];
		g->d[j] = tmp;
	}
}

// hit me function
void hitMe(Game *g, player players[])
{
	int nextCard, j = 4;
	int cardNo = players[g->t].cardNo;
	// do while until card is not 0
	do
	{
		nextCard = g->d[j];
		g->d[j] = 0;
		j++;
	} while (nextCard == 0);

	// assign card to the players hand
	players[g->t].h[cardNo] = nextCard;
	players[g->t].cardNo++; // increment the number of cards player has
	players[g->t].points += getPoint(nextCard); // update players points

	// check if player got an ace
	if (getPoint(nextCard) == 11)
	{
		players[g->t].ace = 1;
	}
	// if its the dealers turn display the card he got
	if (g->t == 0)
	{
		delay(1);
		printf("\nDealer got the ");
		printCard(g, nextCard);
	}
	// otherwise display the card the player got
	else {
		delay(1);
		printf("\nYou got the ");
		printCard(g, nextCard);
	}
	// if the player has an ace and is going to go bust, player uses their ace as 1
	if (players[g->t].ace == 1 && players[g->t].points > 21)
	{
		delay(1);
		players[g->t].points -= 10;
		printf("\nYou choose to use your Ace as 1, you are now on %d points", players[g->t].points);
		players[g->t].ace = 0; // set the players ace to 0 as they have changed their ace to 1 point
	}
	// if player goes over 21 they are bust
	if (players[g->t].points > 21)
	{
		delay(1);
		printf("\nYou are now on %d points", players[g->t].points);
		printf("\nYou are Bust!");
		players[g->t].b = 1; // set players bust variable to 1
	}
}

// calculate points function
int calculatePoints(Game *g, player players[])
{
	int points = 0;
	int pointTotal = 0;
	int face;

	// calculate points for the first 2 cards dealt
	for (int i = 0; i < 2; i++)
	{
		face = getFace(players[g->t].h[i]); // get face value
		switch (face) // switch the face values, to find out how many points the card is worth
		{
		case 0:
			points = 2;
			break;
		case 1:
			points = 3;
			break;
		case 2:
			points = 4;
			break;
		case 3:
			points = 5;
			break;
		case 4:
			points = 6;
			break;
		case 5:
			points = 7;
			break;
		case 6:
			points = 8;
			break;
		case 7:
			points = 9;
			break;
		case 8:
			points = 10;
			break;
		case 9:
			points = 10;
			break;
		case 10:
			points = 10;
			break;
		case 11:
			points = 10;
			break;
		case 12:
			points = 11;
			players[g->t].ace = 1; // if player was dealt an ace, set the ace variable to 1
			break;
		}
		pointTotal += points; // add the points on to the pointTotal
	}
	return pointTotal; // return the pointTotal
}

// getPoint function
int getPoint(int card)
{
	int points = 0;
	int face;
	face = getFace(card);
	switch (face)
	{
		case 0:
			points = 2;
			break;
		case 1:
			points = 3;
			break;
		case 2:
			points = 4;
			break;
		case 3:
			points = 5;
			break;
		case 4:
			points = 6;
			break;
		case 5:
			points = 7;
			break;
		case 6:
			points = 8;
			break;
		case 7:
			points = 9;
			break;
		case 8:
			points = 10;
			break;
		case 9:
			points = 10;
			break;
		case 10:
			points = 10;
			break;
		case 11:
			points = 10;
			break;
		case 12:
			points = 11;
			break;
	}
	return points; // return points
}

// checkForBlackJack function
void checkForBlackJack(Game *g, player players[])
{
	delay(1);
	// check if dealer got blackjack
	if (players[0].points == 21 && players[0].cardNo == 2)
	{
		printf("\nDealer got BlackJack!");
		players[0].bj = 1; // set dealers blackjack variable to 1
		winners(g, players); // call winners function
	}
	else if (g->t == 0) // dealer didn't get blackjack
	{
		printf("\nDealer did not get BlackJack!");
	}
	// check if a player got BlackJack
	if (players[g->t].points == 21 && players[g->t].cardNo == 2 && g->t != 0)
	{
		printf("\n\nPlayer %d got BlackJack!", g->t);
		players[g->t].bj = 1; // set players blackjack variable to 1
		winners(g, players); // call winners function
	}
}

// split function
void split(Game *g, player players[])
{
	delay(1);
	printf("\nFeature not ready yet\n");
	/*int tenPoints = 0;
	int card1, card2;
	int pair = 0;
	int pairCard1, pairCard2;
	int temp[5];

	for (int i = 0; i < players[g->t].cardNo; i++)
	{
		// check if player has two 10 value cards 
		if (players[g->t].h[i] == 10)
		{
			tenPoints++;
			if (tenPoints == 1)
			{
				card1 = i;
			}
			else {
				card2 = i;
			}
		}

		// check if player has a pair
		pairCard1 = players[g->t].h[i];
		for (int j = 0; j < players[g->t].cardNo; j++)
		{
			if (players[g->t].h[j+1] == pairCard1 && (j + 1) != i)
			{
				pairCard2 = players[g->t].h[j + 1];
				players[g->t].h[j + 1] = '0';
				pair++;
			}
		}
	}

	// if player has two 10 value cards then split their hands into two
	if (tenPoints == 20)
	{
		players[g->t].h1[0] = card1;
		temp[0] = players[g->t].h[0];
		players[g->t].h[0] = card2;
	
	}*/
}

// winners function
void winners(Game *g, player players[])
{
	int points;
	int highestPoints;
	int winner;
	int choice;
	int bjCount = 0;

	delay(3);
	// winners header
	printf("\n\n\n\n\n\n============================================\n");
	printf("=                  Winner                  =\n");
	printf("============================================");

	// dealer got blackjack
	if (players[0].bj == 1)
	{
		for (int i = 1; i <= g->np; i++)
		{
			if (players[i].bj == 1) // check if any other players got blackjack
			{
				delay(1);
				printf("\n\nPlayer %d also has a BlackJack", i);
				bjCount++; // increment bjCount if player got blackjack
			}
		}
		delay(1);
		if (bjCount > 0) // draw if more than one got blackjack
		{
			printf("\nDealer draws with %d player", bjCount);
		}
		else // dealer wins with a blackjack
		{
			printf("\nDealer wins with a ");
			printCard(g, players[0].h[0]);
			printf(" and a ");
			printCard(g, players[0].h[1]);
			printf("\n");
			players[0].w++; // increment dealers wins
		}
	}

	// dealer got bust
	if (players[0].b == 1)
	{
		for (int i = 1; i < g->np; i++)
		{
			if (players[i].b != 1) // all players who are not bust win
			{
				delay(1);
				printf("\nPlayer %d wins with %d points!", i, players[i].points);
			}
		}
	}
	// dealer didnt bust
	else if (players[0].b != 1)
	{
		points = players[0].points;
		highestPoints = points;
		winner = 0;

		// check to see who got the highest points and wins
		for (int i = 1; i < g->np; i++)
		{
			if (players[i].b != 1)
			{
				points = players[i].points;
				if (points > highestPoints)
				{
					highestPoints = points; // update highest points
					winner = i; // update winner
				}
			}
		}

		for (int i = 1; i < g->np; i++) // check for a draw
		{
			if (players[i].points == highestPoints && i != winner)
			{
				if (players[i].cardNo > players[winner].cardNo)
				{
					winner = i;
				}
			}
		}
		
		delay(1);
		// dealer wins the round with highest points
		if (winner == 0 && players[0].bj != 1)
		{
			printf("\n\nThe Dealer won this round with %d points", players[winner].points);
			players[0].w++; // increment wins
		}
		else { // player wins the round with highest points
			printf("\n\nThe Winner of round %d is Player %d with\n%d points using %d cards", g->r, winner, players[winner].points, players[winner].cardNo);
			players[winner].w++; // increment wins
		}
	}

	delay(1);
	do // do while to check if user would like to play another round or exit
	{
		printf("\n\n\n\nWould you like to play another round?");
		printf("\n1. Yes");
		printf("\n2. Save and Exit");
		printf("\nOption: ");
		scanf("%d", &choice);
	} while (choice != 1 && choice != 2); // validate

	// play another round
	if (choice == 1)
	{
		g->r++; // increment round
		playGame(g, players); // call playGame function
	}
	else // save and exit
	{
		printf("\n\Saving Game...");
		save(g, players);
	}
}

// save function
void save(Game *g, player players[])
{
	FILE *fptr; // file pointer

	fptr = fopen("save.txt", "w"); // open file
	fprintf(fptr, "%d %d %d %d\n", g->nd, g->np, g->r, g->t); // output game stats to file
	for (int i = 0; i < DECKSIZE * g->nd; i++) // output the current deck to file
	{
		fprintf(fptr, "%d ", g->d[i]);
	}
	for (int j = 0; j < g->np; j++)
	{
		// output player stats to file
		fprintf(fptr, "\n%d %d %d %d %d\n", players[j].points, players[j].cardNo, players[j].w, players[j].b, players[j].ace);
		for (int i = 0; i < players[j].cardNo; i++)
		{
			fprintf(fptr, "%d ", players[j].h[i]); // output players hands to file
		}
	}
	fclose(fptr); // close file
}

// loadGame function
void loadGame(Game *g, player players[])
{
	FILE *fptr; // file pointer
	fptr = fopen("save.txt", "r"); // open file

	if (fptr == NULL) { // check for errors reading file
		printf("\nError reading file!\n");
	}
	else {
		fscanf(fptr, "%d %d %d %d", &g->nd, &g->np, &g->r, &g->t); // read in game variables
		for (int i = 0; i < DECKSIZE * g->nd; i++) // read in deck
		{
			fscanf(fptr, "%d ", &g->d[i]);
		}
		for (int j = 0; j < g->np; j++)
		{
			// read in player variables
			fscanf(fptr, "%d %d %d %d %d", &players[j].points, &players[j].cardNo, &players[j].w, &players[j].b, &players[j].ace);
			for (int i = 0; i < players[j].cardNo; i++) // read in player hands
			{
				fscanf(fptr, "%d ", &players[j].h[i]);
			}
		}
	}
	fclose(fptr); // close file
}