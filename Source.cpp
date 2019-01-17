/*
I have neither given nor received unauthorized aid in completing this work, nor have I presented someone else's work as my own.
Mary Cody
*/

#include <iostream>
#include <random>
#include <time.h>
#include <iomanip>
#include <string>
#include <Windows.h>
#include <stdio.h>


using namespace std;

void gotoxy(int h, int w);
void winner(int hands[]);
void header();
void printTotal(int hands[]);
void dealOne(int &count, int &loop, int player, int deck[], char suit[], int hands[]);
void dealHand(int &count, int deck[], char suit[], int hands[]);
void shuffleDeck(int deck[52]);
void readDeck(int deckRaw[], int deck[], char suit[]);

int main()
{
	int deckRaw[52]; //palce to stre the raw numbers when "shuffling" the deck
	int deck[52]; //stores the card value in the "shuffled" deck
	char suit[52]; //stores the card suit in the "shuffled" deck
	int count;
	char play = 'Y'; //do you want to play?
	char newCard = 'Y'; //do you want a new card?
	int player;

	system("color 37");
	
	srand(time(NULL));

	while (play = 'Y')
	{
		int hands[8]= { 0 };

		count = 0;
		
		shuffleDeck(deckRaw); //assignes the values to the deck and suit cards based on random number generatioon
		readDeck(deckRaw, deck, suit); //reads out the values in the raw deck to populate the value and suit arrays
		
		header();
		
		dealHand(count, deck, suit, hands); //deals first hand to all players

		printTotal(hands); //displays the total in each player's hand

		int loop = 3;
		for (int z = 0; z <= 7; z++)
		{
			if (z == 0) //deals a hand to the dealer each round while the dealer's hand is less than 16
			{	
				while (hands[z] <= 16)
				{
					dealOne(count, loop, z, deck, suit, hands);
					loop++;
				}
				printTotal(hands);
			}
			else //for the plyers
			{
				while (hands[z] <= 21) //if the hand is still less than 21 offers choice to deal another card
				{
					gotoxy(0, 16);
					cout << "Player " << z << ", Would you like another card? Y/N";
					cin >> newCard;
					if (newCard == 'Y')
					{
						dealOne(count, loop, z, deck, suit, hands);
						printTotal(hands);
						loop++;
					}
					else
						break;
				}
			}
		}

		winner(hands);//determines who won

		gotoxy(0, 18); //asks if you would like another game and updates play
		cout << "Would you like to play again? Y/N";
		cin >> play;
		system("cls");
	}
	
	
	
	return 0;
}

//reads the deck into values and suits
void readDeck(int deckRaw[], int deck[], char suit[])
{
	for (int i = 0; i < 53; i++)
	{
		if ((deckRaw[i] % 13) + 1 > 10)
		{
			deck[i] = 10;
		}
		else
		{
			deck[i] = (deckRaw[i] % 13) + 1;
		}
		suit[i] = (deckRaw[i] / 13) + 3;
	}
	return;
}

//randomizes the order of the cards in the deck
void shuffleDeck(int deck[52])
{
	int j;
	int picked[52] = { 0 };
	for (int i = 0; i < 51; i++)
	{
		j = rand() % 52 + 1;

		while (picked[j])
		{
			j = rand() % 52 + 1;
		}

		deck[i] = j;

		picked[j] = 1;

	}
	return;
}

//deals the initial hand to all players
void dealHand(int &count, int deck[], char suit[], int hands[])
{
	
	for (int i = 1; i <= 2; i++)
	{
		cout << endl << right;
		for (int x = 0; x <= 7; x++)
		{
			gotoxy(x * 10, i);
			cout << deck[count] << suit[count];
			hands[x] = hands[x] + deck[count];
			count++;
		}
	}
	return;
}

//deals a single card
void dealOne(int &count, int &loop, int player, int deck[], char suit[], int hands[])
{
	hands[player] = hands[player] + deck[count];
	gotoxy(player * 10, loop);
	cout << right << deck[count] << suit[count];
	count++;
	return;
}

//prints the total vlaue of a hand
void printTotal(int hands[])
{
	gotoxy(0, 14);
	cout << "Totals:";
	for (int x = 0; x < 8; x++)
	{
		gotoxy(x * 10, 15);
		cout << hands[x];
	}
	return;
}

//creates the header for the game
void header()
{
	gotoxy(0, 0);
	cout << "Dealer";
	gotoxy(10, 0);
	cout << "Player 1";
	gotoxy(20, 0);
	cout << "Player 2";
	gotoxy(30, 0);
	cout << "Player 3";
	gotoxy(40, 0);
	cout << "Player 4";
	gotoxy(50, 0);
	cout << "Player 5";
	gotoxy(60, 0);
	cout << "Player 6";
	gotoxy(70, 0);
	cout << "Player 7";
	return;
}

//calculates the winning hand(s) of the game
void winner(int hands[])
{
	gotoxy(0, 16);
	cout << "                                                            ";
	int beat = hands[0];
	if (beat > 21)
	{
		for (int i = 1;  i < 8; i++)
		{
			gotoxy(i*10, 16);
			cout << "Win";
		}
	}
	else
	{
		for (int i = 1; i <= 7; i++)
		{
			if (hands[i] > 21)
			{
				gotoxy(i*10, 16);
				cout << "Bust";
			}
			else if (beat > hands[i])
			{
				gotoxy(i*10, 16);
				cout << "Loose";
			}
			else if (beat == hands[i])
			{
				gotoxy(i*10, 16);
				cout << "Tie";
			}
			else
			{
				gotoxy(i*10, 16);
				cout << "Win";
			}
		}
	}
	cout << endl;
	system("pause");
	return;
}

//sends the cursor to a specific place
void gotoxy(int h, int w)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (INVALID_HANDLE_VALUE != hConsole)
	{
		COORD pos = { h, w };
		SetConsoleCursorPosition(hConsole, pos);
	}
	return;
}