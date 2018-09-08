#ifndef ROUND_H
#define ROUND_H

#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "Human.h"
#include "Computer.h"


using namespace std;
class Round
{
public:
	// Public function
	Round();
	~Round();
	void PlayRound(string firstPlayer);
	string GetLastCapture();

private:
	// Private functions
	void SwitchPlayer();

	// Private variables
	string lastCapture;
	int currentPlayer;

	Human p1 = Human();
	Computer p2 = Computer();

	vector<Player*> player; // A vector of player objects which will act as one index for the player and the others as the computer
	

};

#endif