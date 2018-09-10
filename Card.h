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
	void SetSuit(string passedSuit);
	void SetNumber(string passedNumber);

	// Getters
	const string GetCard();
	const string GetSuit();
	const string GetNumber();

private:
	// Private variables
	string card;
	string suit;
	string number;
};

#endif