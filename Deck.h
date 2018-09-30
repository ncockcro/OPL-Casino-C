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
	Deck();
	Deck(vector<Card> cards);
	void PrintDeck();
	bool IsEmpty();
	vector<Card> GetDeck() const;
	void RemoveFourCards();

private:
	// Private functions
	void ShuffleCards();

	// Private variables
	vector<Card> deckOfCards;
};

#endif