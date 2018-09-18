#include "Card.h"



Card::Card()
{
}


Card::~Card()
{
}

/* *********************************************************************
Function Name: SetCard
Purpose: Setting a string to be the value of a card
Parameters:
passedCard, a string passed by value. It holds the string they want to set as the card
Return Value: Void
Local Variables: None
Algorithm:
1) Check to make sure the card is a valid card by checking suit and number
2) If it is, set the card to what was passed in
3) Otherwise, output an error message
Assistance Received: none
********************************************************************* */
void Card::SetCard(string passedCard) {
	if (CheckSuit(passedCard[0]) && CheckNumber(passedCard[1])) {
		card = passedCard;
		suit = passedCard[0];
		number = passedCard[1];
	}
	else {
		cerr << "Error in setting the card in the card class." << endl;
	}
}

/* *********************************************************************
Function Name: GetCard
Purpose: Retrieving the string which contains the card
Parameters: None
Return Value: Returns the 2 character card, a string value
Local Variables: None
Algorithm:
1) Return the card
Assistance Received: none
********************************************************************* */
string Card::GetCard() const {
	return card;
}

/* *********************************************************************
Function Name: GetSuit
Purpose: Retrieving the char which contains the suit
Parameters: None
Return Value: Returns either club, diamond, heart, or spade, a char
Local Variables: None
Algorithm:
1) Return the suit
Assistance Received: none
********************************************************************* */
char Card::GetSuit() const {
	return suit;
}

/* *********************************************************************
Function Name: GetNumber
Purpose: Retrieving the char which contains the number of a card
Parameters: None
Return Value: Returns the character that represents a cards number, a char
Local Variables: None
Algorithm:
1) Return the number
Assistance Received: none
********************************************************************* */
char Card::GetNumber() const {
	return number;
}

/* *********************************************************************
Function Name: CheckSuit
Purpose: Checks if a suit is a valid suit in a deck of cards
Parameters: None
Return Value: Returns true if a valid suit, false otherwise, a boolean value
Local Variables: None
Algorithm:
1) If the suit passed in matches an actual suit, return true
2) Otherwise, return false
Assistance Received: none
********************************************************************* */
bool Card::CheckSuit(char passedSuit) {
	if (passedSuit == 'C' || passedSuit == 'D' || passedSuit == 'H' || passedSuit == 'S') {
		return true;
	}
	else {
		return false;
	}

}

/* *********************************************************************
Function Name: CheckNumber
Purpose: Checks if a number is a valid number in a deck of cards
Parameters: None
Return Value: Returns true if a valid number, false otherwise, a boolean value
Local Variables: None
Algorithm:
1) If the suit passed in matches an actual number, return true
2) Otherwise, return false
Assistance Received: none
********************************************************************* */
bool Card::CheckNumber(char passedNumber) {
	if (passedNumber == '2' || passedNumber == '3' || passedNumber == '4' || passedNumber == '5' || passedNumber == '6' ||
		passedNumber == '7' || passedNumber == '8' || passedNumber == '9' || passedNumber == 'X' || passedNumber == 'J' ||
		passedNumber == 'Q' || passedNumber == 'K' || passedNumber == 'A') {
		return true;
	}
	else {
		return false;
	}
}