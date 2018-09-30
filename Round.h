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
	void DealCardsToPlayers();
	void DealCardsToTable();
	void SetTable(vector<Card> deckOfCards);
	void PrintHandPileAndTable();
	void SaveGame();
	bool CheckMove(char move);
	bool CheckBuild();
	bool CheckBuildNumbers(Card playerCard, vector<Card> playerBuildCards);
	int CardNumber(char number);
	void CreatePlayerBuild();
	void RemoveTableCards(vector<Card> cards);
	bool CheckCapture();
	bool CheckIfPlayerCanCaptureBuild(Card playerHandCaptureCard, vector<Card> playerHand);
	bool CheckTrail();
	void AddCardsToTable(vector<Card> cards);
	void SwitchPlayer();
	void PrintPlayerPiles();
	void GiveTableCards();

	// Private variables
	vector<Card> computerPile;
	int humanScore;
	vector<Card> humanHand;
	vector<Card> humanPile;
	vector<Card> table;
	vector<Card> buildCards;
	vector<Build> builds;
	vector<Card> deck;
	string nextPlayer;
	string lastCapture;
	int currentPlayer;
	Deck deckOfCards;
	Human p1 = Human();
	Computer p2 = Computer();
	bool playTrue;
	vector<Player*> player;
	
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