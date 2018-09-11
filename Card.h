#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

using namespace std;

class Card
{
public:
	// Public functions
	Card();
	~Card();

	// Setters
	void SetCard(string passedCard);
	void SetSuit(char passedSuit);
	void SetNumber(char passedNumber);

	// Getters
	const string GetCard();
	const char GetSuit();
	const char GetNumber();

private:
	// Private variables
	string card;
	char suit;
	char number;
};

#endif