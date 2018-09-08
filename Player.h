#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Player
{
public:
	// Public functions
	Player();
	~Player();
	virtual void MakeMove(); // Virtual function so both types of players can share certain moves

private:
	// Private functions


	// Private variables
	vector<string> hand;
};

#endif