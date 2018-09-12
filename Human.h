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

	void MakeMove();
	void MakeBuild();
	void MakeCapture();
	void MakeTrail();
};

#endif