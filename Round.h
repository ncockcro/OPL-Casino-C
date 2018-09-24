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
#include "Set.h"


using namespace std;
class Round
{
public:
	// Public function
	Round();
	~Round();
	void PlayRound(string firstPlayer);
	string GetLastCapture() const;
	vector<Card> GetPlayerPile() const;
	vector<Card> GetComputerPile() const;
	void SetRoundInfo(int round, int humanScore, int computerScore);
	void LoadDeck(vector<Card> loadedDeck);
	void LoadRound(vector<Card> loadComputerHand, vector<Card> loadComputerPile, vector<Card> loadHumanHand, vector<Card> loadHumanPile,
		vector<Card> loadTable, vector<Build> loadBuilds, vector<Card> loadDeck);

private:
	// Private functions
	void SwitchPlayer();
	void DealCardsToPlayers();
	void DealCardsToTable();
	void SetTable(vector<Card> deckOfCards);

	// Used for validating a player's move
	bool CheckMove(char move);
	bool CheckBuild();
	bool CheckBuildNumbers(Card playerCard, vector<Card> playerBuildCards); // Checks the number in a players hand and the number they are trying to add up to in a build
	int CardNumber(char number);
	void CreatePlayerBuild();
	bool AddToExistingBuild();
	void RemoveTableCards(vector<Card> cards);
	void AddCardsToTable(vector<Card> cards);
	void PrintHandPileAndTable();

	bool CheckCapture();
	bool CheckIfPlayerCanCaptureBuild(Card playerHandCaptureCard, vector<Card> playerHand);

	void PrintPlayerPiles();

	// Trailing
	bool CheckTrail();

	void SaveGame();

	vector<Card> computerPile;
	int humanScore;
	vector<Card> humanHand;
	vector<Card> humanPile;
	vector<Card> table;
	vector<Card> buildCards;
	vector<Build> builds;
	vector<Card> deck;
	string nextPlayer;

	// Private variables
	string lastCapture;
	int currentPlayer;
	Deck deckOfCards;
	Human p1 = Human();
	Computer p2 = Computer();
	bool playTrue;

	vector<Player*> player; // A vector of player objects which will act as one index for the player and the others as the computer
	
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

	int currentRound;
	int humanPoints;
	int computerPoints;

	bool loadGame;
};

#endif