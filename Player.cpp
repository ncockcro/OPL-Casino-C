#include "Player.h"


// Default constructor
Player::Player()
{
}

// Default destructor
Player::~Player()
{
}

// Virtual function for a player to make the move in the game of Casino. There will also be further
// code in each of the child classes to further specify how each player makes a move.
void Player::MakeMove() {
	hand.pop_back();
	hand.pop_back();
	hand.pop_back();
	hand.pop_back();

}

// When a player is out of cards, this function will be called to add four more cards to a players hand.
void Player::SetHand(const vector<Card> fourCards) {

	hand.push_back(fourCards[0]);
	hand.push_back(fourCards[1]);
	hand.push_back(fourCards[2]);
	hand.push_back(fourCards[3]);
}

bool Player::IsEmpty() {

	if (hand.empty()) {
		return true;
	}
	else {
		return false;
	}
}

const vector<Card> Player::GetHand() {
	return hand;
}

const Card Player::GetPlayerCard() {
	return playerCard;
}

const vector<Card> Player::GetBuildCards(){
	return buildCards;
}

const vector<Card> Player::GetCaptureCards() {
	return captureCards;
}

const char Player::GetPlayerMove() {
	return playerMove;
}

void Player::RemoveCard(Card card) {
	bool notFound = false;
	for (int i = 0; i < hand.size(); i++) {
		if (hand[i].GetCard() == card.GetCard()) {
			hand.erase(hand.begin() + i);
			notFound = true;
		}
	}

	if (notFound == false) {
		cerr << "Error in removing a card in the player class." << endl;
	}
}

void Player::SetPile(vector<Card> passedPile) {
	int count = 0;
	for (int i = 0; i < passedPile.size(); i++) {
		if (passedPile[i].GetCard().size() == 2) {
			count++;
		}
	}

	if (count == passedPile.size()) {
		pile = passedPile;
	}
}
void Player::AddToPile(vector<Card> passedPile) {
	
	for (int i = 0; i < passedPile.size(); i++) {
		if (passedPile[i].GetCard().size() == 2) {
			pile.push_back(passedPile[i]);
		}
	}
}
const vector<Card> Player::GetPile() {
	return pile;
}

void Player::PrintPile() {
	for (int i = 0; i < pile.size(); i++) {
		cout << pile[i].GetCard() << " ";
	}
	cout << endl;
}

const char Player::GetPlayerWantSet() {
	return playerWantSet;
}

vector<Card> Player::MakeSet() {
	string userInput;
	int count = 0;

	do {
		cout << "Enter the two cards that make up a set for you to capture: ";
		cin >> userInput;

		if (CheckCard(userInput)) {
			setCards.push_back(Card());
			setCards[count].SetCard(userInput);
			setCards[count].SetSuit(userInput[0]);
			setCards[count].SetNumber(userInput[1]);
			count++;
		}

	} while (count < 2);

	return setCards;
}

bool Player::CheckCard(string card) {

	bool validCard = false;

	for (int i = 0; i < uniqueCards.size(); i++) {
		if (uniqueCards[i].GetCard() == card) {
			validCard = true;
		}
	}

	return validCard;
}