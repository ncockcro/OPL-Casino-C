#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include "Card.h"

using namespace std;
class Player
{
public:
	// Public functions
	Player();
	~Player();
	virtual void MakeMove(); // Virtual function so both types of players can share certain moves
	void SetHand(const vector<Card> fourCards);
	bool IsEmpty();

protected:
	vector<Card> hand;

private:
	// Private functions


	// Private variables

};

#endif