#include "Set.h"



Set::Set()
{
}


Set::~Set()
{
}

/* *********************************************************************
Function Name: SetCardsOfSet
Purpose: To set a vector of cards into a set
Parameters:
cards, a vector of cards. It refers to the cards which make up a set
Return Value: Void
Local Variables: None
Algorithm:
1) Set the cardsOfSet variable to what was passed in
Assistance Received: none
********************************************************************* */
void Set::SetCardsOfSet(vector<Card> cards) {
	cardsOfSet = cards;
}

/* *********************************************************************
Function Name: GetCardsOfSet
Purpose: To retrieve the vector of cards of a set
Parameters: None
Return Value: The cards of a set, a vector of cards value
Local Variables: None
Algorithm:
1) Return the cardsOfSet
Assistance Received: none
********************************************************************* */
vector<Card> Set::GetCardsOfSet() const {
	return cardsOfSet;
}
