#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Card.h"

using namespace std;

class Build
{
public:
	Build();
	~Build();

	void SetOwner(string passedOwner);
	const string GetOwner();
	void SetBuildOfCards(vector<Card> buildCards);
	const vector<Card> GetBuildOfCards();
	void PrintBuild();

private:
	string owner;
	vector<Card> buildOfCards;
};

