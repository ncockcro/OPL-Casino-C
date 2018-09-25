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
	int GetOwner() const;
	void SetBuildOfCards(vector<Card> buildCards);
	vector<Card> GetBuildOfCards() const;
	void PrintBuild();
	bool CheckAndAddCardInBuild(Card cardToBeAdded, Card cardInBuild, int currentPlayer, vector<Card> playerHand);
	bool CanCaptureBuildOfCards(Card cardToBeCaptured, Card cardInBuild, vector<Card> playerHand);
	void SetValueOfBuild(int value);
	int GetValueOfBuild() const;

private:
	// Private functions
	int CardNumber(char number);

	// Owner of a specific build
	int owner;
	// The value of the card that is equal to the total value of a build
	int cardValueOfBuild;
	vector<Card> buildOfCards;
};

