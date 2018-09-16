#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include "Card.h"
#include "Deck.h"

using namespace std;

/*
Joseph Allen, in CMPS 366-01, helped answer some questions about inheritance and how it works for me.
I showed him some parts of my code such as the MakeMove() function in the player class as well as in
the human class so he can have an understanding of what I was trying to do and how he could explain it
to me. He looked at my code but I did not look at his.
*/

class Player
{
public:
	// Public functions
	Player();
	~Player();
	virtual void MakeMove(); // Virtual function so both types of players can share certain moves
	void SetHand(vector<Card> fourCards);
	bool IsEmpty();
	const vector<Card> GetHand();
	const Card GetPlayerCard();
	const vector<Card> GetBuildCards();
	const vector<Card> GetCaptureCards();
	const char GetNewOrExistingBuild();
	const Card GetExistingBuildCard();
	const char GetPlayerMove();
	void RemoveCard(Card card);

	void SetPile(vector<Card> passedPile);
	void AddToPile(vector<Card> passedPile);
	const vector<Card> GetPile();
	void PrintPile();
	const char GetPlayerWantSet();
	vector<Card> MakeSet();


protected:
	// Current hand and pile of the player
	vector<Card> hand;
	vector<Card> pile;

	Deck deck = Deck();
	vector<Card> uniqueCards = deck.GetDeck();

	Card playerCard;
	vector<Card> buildCards;
	char newOrExistingBuild;
	Card existingBuildCard;
	char playerMove;
	char playerWantSet;
	vector<Card> setCards;
	bool CheckCard(string card);

private:
	// Private functions


	// Private variables

};

#endif