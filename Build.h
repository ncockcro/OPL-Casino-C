#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Card.h"

using namespace std;

class Build
{
public:
	Build();
	~Build();

	void SetOwner(int passedOwner);
	const int GetOwner();
	void SetBuildOfCards(vector<Card> buildCards);
	const vector<Card> GetBuildOfCards();
	void PrintBuild();
	bool CheckAndAddCardInBuild(Card cardToBeAdded, Card cardInBuild, int currentPlayer, vector<Card> playerHand);

private:
	// Private functions
	int CardNumber(char number);

	int owner;
	vector<Card> buildOfCards;
};

