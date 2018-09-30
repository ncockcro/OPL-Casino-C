#ifndef SET_H
#define SET_H

#include <string>
#include <vector>
#include "Card.h"

using namespace std;

class Set
{
public:
	Set();

	void SetCardsOfSet(vector<Card> cards);
	vector<Card> GetCardsOfSet() const;

private:
	vector<Card> cardsOfSet;
};

#endif