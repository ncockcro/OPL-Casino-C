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
	const vector<Card> GetPlayerPile();
	const vector<Card> GetComputerPile();

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
	bool AddToExistingBuild();
	bool CaptureExistingBuild();
	void RemoveTableCards(vector<Card> cards);
	void AddCardsToTable(vector<Card> cards);
	void PrintHandPileAndTable();

	bool CheckCapture();

	void PrintPlayerPiles();

	// Trailing
	bool CheckTrail();

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

	// Used if the player is making a capture
	Card playerHandCaptureCard;
	vector<Card> playerTableCaptureCards;

	// Used if the player is making a trail
	Card playerHandTrailCard;
};

#endif