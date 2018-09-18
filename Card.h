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

	// Getters
	string GetCard() const;
	char GetSuit() const;
	char GetNumber() const;

private:
	//Private functions
	bool CheckSuit(char passedSuit);
	bool CheckNumber(char passedNumber);
	// Private variables
	string card;
	char suit;
	char number;

};

#endif