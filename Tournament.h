#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <iostream>
#include <string>
#include <ctime>
#include "Deck.h"
#include "Round.h"

using namespace std;

class Tournament
{
public:
	// Public functions
	Tournament();
	~Tournament();
	void PlayGame();
	void AddPoints();

private:
	// Private functions
	string StartMenu();
	string TossCoin();
	void GameWon();
	void IncrementRound();
	void SaveLastCaptured(string capturer);

	// Private variables
	string initialDecision;
	int humanPoints;
	int computerPoints;
	string firstPlayer;
	int round;
	Round currentRound = Round();
	string lastCaptured;
};

#endif