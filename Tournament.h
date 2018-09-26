#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
#include "Deck.h"
#include "Round.h"
#include "Build.h"

using namespace std;

class Tournament
{
public:
	// Public functions
	Tournament();
	~Tournament();
	void PlayGame();

	struct LoadGameInfo {
		int round;
		int computerScore;
		vector<Card> computerHand;
		vector<Card> computerPile;
		int humanScore;
		vector<Card> humanHand;
		vector<Card> humanPile;
		vector<Card> table;
		vector<Card> buildCards;
		vector<Build> builds;
		vector<Card> deck;
		string nextPlayer;
	};

private:
	// Private functions
	string StartMenu();
	bool LoadGame();
	bool LoadDeck();
	void SaveLastCaptured(string capturer);
	void IncrementRound();
	void CalculatePoints();
	string TossCoin();
	void GameWon();

	// Private variables
	string initialDecision;
	int humanPoints;
	int computerPoints;
	string firstPlayer;
	int round;
	Round currentRound = Round();
	string lastCaptured;
	vector<Card> loadedDeck;

	LoadGameInfo loadInfo;
};

#endif