#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Card.h"
#include "Deck.h"
#include "Build.h"
#include "Set.h"

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
	virtual void MakeMove(bool falseMove, vector<Card> table, vector<Build> buildTable); // Virtual function so both types of players can share certain moves
	void SetHand(vector<Card> fourCards);
	bool IsEmpty();
	vector<Card> GetHand() const;
	Card GetPlayerCard() const;
	vector<Card> GetBuildCards() const;
	char GetNewOrExistingBuild() const;
	Card GetExistingBuildCard() const;
	char GetPlayerMove() const;
	void RemoveCard(Card card);

	void SetPile(vector<Card> passedPile);
	void AddToPile(vector<Card> passedPile);
	vector<Card> GetPile() const;
	void AddToPlayerBuildCards(Card buildCard);
	vector<Card> GetPlayerBuildCards() const;
	void RemovePlayerBuildCard(Card card);
	void PrintPile();
	char GetPlayerWantBuild() const;
	void SetPlayerWantBuild(char choice);
	char GetPlayerWantSet() const;
	vector<Card> GetPlayerSetCards() const;
	vector<Set> GetPlayerOfSetCards() const;
	bool GetPlayerWantSave() const;
	vector<Card> MakeSet();


protected:
	// Protected functions
	bool AICheckForBuild(vector<Card> playerHand, vector<Card> table, vector<Build> tableBuilds);
	bool AICheckForCapture(vector<Card> playerHand, vector<Card> table, vector<Build>tableBuilds);
	void AIMakeTrail(vector<Card> playerHand);
	int CardNumber(char number);
	void AskForHelp();

	// Protected varaibles
	// Current hand and pile of the player
	vector<Card> hand;
	vector<Card> pile;
	vector<Card> playerBuildCards;
	vector<Card> playerSetCards;
	vector<Set> playerOfSetCards;

	Deck deck = Deck();
	vector<Card> uniqueCards = deck.GetDeck();
	bool playerWantSave;

	Card playerCard;
	vector<Card> buildCards;
	char newOrExistingBuild;
	Card existingBuildCard;
	char playerMove;
	char playerWantBuild;
	char playerWantSet;
	bool CheckCard(string card);
};

#endif