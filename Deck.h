#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm> // random_shuffle
#include <random>

using namespace std;
class Deck
{
public:
	// Public functions
	Deck(); // Default constructor
	~Deck(); // Default destructor
	void PrintDeck(); // Prints the current deck of cards

private:
	// Private functions
	void ShuffleCards(); // Shuffles the deck if one was created

	// Private variables
	vector<string> deckOfCards;
};

#endif