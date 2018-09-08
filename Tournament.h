#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Tournament
{
public:
	// Public functions
	Tournament();
	~Tournament();
	void PlayGame();
	void AddPoints(int points);

private:
	// Private functions
	bool TossCoin();
	void GameWon();

	// Private variables
	int humanPoints;
	int computerPoints;
	bool firstPlayer;
	int round;
};

#endif