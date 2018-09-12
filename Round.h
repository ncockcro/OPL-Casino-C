#ifndef ROUND_H
#define ROUND_H

#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include "Deck.h"
#include "Card.h"
#include "Build.h"


using namespace std;
class Round
{
public:
	// Public function
	Round();
	~Round();
	void PlayRound(string firstPlayer);
	const string GetLastCapture();

private:
	// Private functions
	void SwitchPlayer();
	void DealCardsToPlayers();
	void DealCardsToTable();
	void SetTable(vector<Card> deckOfCards);
	bool CheckMove(char move);
	bool CheckBuild();
	bool CheckBuildNumbers(Card playerCard, vector<Card> playerBuildCards); // Checks the number in a players hand and the number they are trying to add up to in a build
	int CardNumber(char number);
	void CreatePlayerBuild();
	void RemoveTableCards();
	void PrintHandAndTable();
	void PrintTable();

	bool CheckCapture();
	bool PlayerHasCaptureCard();
	bool CaptureCardsOnTable();

	bool CheckTrail();
	void AddTrail();

	// Private variables
	string lastCapture;
	int currentPlayer;

	Deck deckOfCards = Deck();

	Human p1 = Human();
	Computer p2 = Computer();

	vector<Player*> player; // A vector of player objects which will act as one index for the player and the others as the computer
	vector<Card> table;
	
	// Used if the player is making a build
	Card playerHandBuildCard;
	vector<Card> playerTableBuildCards;

	vector<Build> tableBuilds;
	int buildCounter;

	Card playerHandCaptureCard;
	vector<Card> playerTableCaptureCards;
};

#endif