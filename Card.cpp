#include "Card.h"



Card::Card()
{
}


Card::~Card()
{
}


void Card::SetCard(string passedCard) {
	if (passedCard.size() == 2) {
		card = passedCard;
	}
	else {
		cout << "Error in setting the card in the card class." << endl;
	}
}

void Card::SetSuit(char passedSuit) {
	if (passedSuit == 'C' || passedSuit == 'D' || passedSuit == 'H' || passedSuit == 'S') {
		suit = passedSuit;
	}
	else {
		cout << "Error in setting the suit in the card class." << endl;
	}
}
void Card::SetNumber(char passedNumber) {
	if (passedNumber == '2' || passedNumber == '3' || passedNumber == '4' || passedNumber == '5' || passedNumber == '6' ||
		passedNumber == '7' || passedNumber == '8' || passedNumber == '9' || passedNumber == 'X' || passedNumber == 'J' ||
		passedNumber == 'Q' || passedNumber == 'K' || passedNumber == 'A') {
		number = passedNumber;
	}
	else {
		cout << "Error in setting the number in the card class." << endl;
	}
}

const string Card::GetCard() {
	return card;
}
const char Card::GetSuit() {
	return suit;
}
const char Card::GetNumber() {
	return number;
}
