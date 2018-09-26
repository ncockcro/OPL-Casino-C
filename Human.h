#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"
#include <string>
#include <vector>

using namespace std;
class Human: public Player
{
public:
	Human();
	~Human();

	// Public functions
	void MakeMove(vector<Card> table, vector<Build> buildTable);
	void PrintMove();
	void MakePlay();
	void MakeBuild();
	void MakeCapture();
	void MakeTrail();

private:
	// Private function
};

#endif