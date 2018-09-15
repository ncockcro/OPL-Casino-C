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
Function Name: SetSuit
Purpose: Setting a character to be the value of 
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
/*void Card::SetSuit(char passedSuit) {
	if (CheckSuit(passedSuit)) {
		suit = passedSuit;
	}
	else {
		cerr << "Error in setting the suit in the card class." << endl;
	}
}
void Card::SetNumber(char passedNumber) {
	if (CheckNumber(passedNumber)) {
		number = passedNumber;
	}
	else {
		cerr << "Error in setting the number in the card class." << endl;
	}
}*/

const string Card::GetCard() {
	return card;
}
const char Card::GetSuit() {
	return suit;
}
const char Card::GetNumber() {
	return number;
}

bool Card::CheckSuit(char passedSuit) {
	if (passedSuit == 'C' || passedSuit == 'D' || passedSuit == 'H' || passedSuit == 'S') {
		return true;
	}
	else {
		return false;
	}

}
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