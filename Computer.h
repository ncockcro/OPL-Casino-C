#ifndef COMPUTER_H
#define COMPUTER_H

#include "Player.h"
#include <string>
#include <vector>

using namespace std;

class Computer: public Player
{
public:
	Computer();

	void MakeMove(vector<Card> table, vector<Build> tableBuilds);
	void PrintMove();
};

#endif