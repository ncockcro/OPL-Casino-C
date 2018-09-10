#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm> // random_shuffle
#include <random>
#include "Card.h"

using namespace std;
class Deck
{
public:
	// Public functions
	Deck(); // Default constructor
	~Deck(); // Default destructor
	void PrintDeck(); // Prints the current deck of cards
	bool IsEmpty();
	const vector<Card> GetDeck();
	void RemoveFourCards();

private:
	// Private functions
	void ShuffleCards(); // Shuffles the deck if one was created

	// Private variables
	//Card::CardStruct card;
	vector<Card> deckOfCards;
};

#endif