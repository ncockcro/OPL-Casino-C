#include "Round.h"



Round::Round()
{
	player.push_back(&p1); // Human player
	player.push_back(&p2); // Computer player
}


Round::~Round()
{
}

// Responsible for playing a single round in the tournament
void Round::PlayRound(string firstPlayer) {

	if (firstPlayer == "human") {
		currentPlayer = 0;
	}
	else {
		currentPlayer = 1;
	}

	deckOfCards.PrintDeck();
	// At the beginning of a round, deal first four cards to player, next four to computer, and next four to the table
	DealCardsToPlayers();
	DealCardsToTable();
	deckOfCards.PrintDeck();
	system("pause");

	do {
		player[currentPlayer]->MakeMove();
		// Check move
		CheckMove();

		SwitchPlayer();

		player[currentPlayer]->MakeMove();
		CheckMove();

SwitchPlayer();

if (!deckOfCards.IsEmpty() && player[0]->IsEmpty() && player[1]->IsEmpty()) {
	DealCardsToPlayers();
}

	} while (!deckOfCards.IsEmpty() && !player[0]->IsEmpty() && !player[1]->IsEmpty()); // while there are still cards in the deck and cards in the player's hands

	lastCapture = "computer";
}

// Getter for getting the player who made the last capture.
const string Round::GetLastCapture() {
	return lastCapture;
}

// Switches the player from human to computer and computer to human.
void Round::SwitchPlayer() {
	if (currentPlayer == 0) {
		currentPlayer = 1;
	}
	else if (currentPlayer == 1) {
		currentPlayer = 0;
	}
	else {
		cout << "Error with switching players!" << endl;
	}
}

// Responsible for dealing four cards to each of the players once they run out of cards.
// Then it removes those cards from the full deck.
void Round::DealCardsToPlayers() {

	// Deal four cards to the human
	player[0]->SetHand(deckOfCards.GetDeck());
	// Remove four cards from the deck
	deckOfCards.RemoveFourCards();

	// Deal four cards to the computer 
	player[1]->SetHand(deckOfCards.GetDeck());
	// Remove four cards from the deck
	deckOfCards.RemoveFourCards();

}

// At the beginning of each round, this function is called to set the table and place four cards on it.
// This calls a function to add four cards to the table vector and removes four cards from the deck.
void Round::DealCardsToTable() {

	// Deal four cards to the table
	SetTable(deckOfCards.GetDeck());

	// Remove four cards from the deck
	deckOfCards.RemoveFourCards();
}

// This function pushes four cards onto the table vector of cards.
void Round::SetTable(vector<Card> deckOfCards) {

	table.push_back(deckOfCards[0]);
	table.push_back(deckOfCards[1]);
	table.push_back(deckOfCards[2]);
	table.push_back(deckOfCards[3]);
}

void Round::CheckMove() {

	// Getting the player card that they want to put on the build
	playerCard = player[currentPlayer]->GetPlayerCard();
	// Getting the card on the table that the player wants to use for a build
	playerBuildCards = player[currentPlayer]->GetBuildCards();

	int buildSize = playerBuildCards.size();
	int count = 0;

	// This is checking to make sure that the cards the user entered in to make a build are actually on the table
	for (size_t i = 0; i < table.size(); i++) {
		for (size_t j = 0; j < playerBuildCards.size(); j++) {
			if (table[i].GetCard() == playerBuildCards[j].GetCard()) {
				count++;
			}
		}
	}

	if (count != buildSize) {
		cout << "Error, the cards you entered for a build are not on the table" << endl;
		player[currentPlayer]->MakeMove();
	}
	else {
		cout << "You were correct with the build!" << endl;
	}

	CheckBuildNumbers(playerCard, playerBuildCards);
}

/*
Function Name: CheckBuildNumbers
Purpose: To figure out if the cards that a player wants to use to build adds up to something in their deck and 
if those cards they chose to build with are on the table.
Parameters:
playerCard, a card object, the card the player wants to build with
playerBuildCards, a vector of cards, card(s) the player wants to build with from the table
Return Value: Boolean
Local Variables:
aceAs1, an int for counting cards when ace is 1
aceAs14, an int for counts cards when ace is 14
playerHand, a vector of cards which holds the current cards in a players hand
hasRightCards, a boolean which is true if everything is valid, false otherwise
Algorithm:
Still working on!
Assistance Received: none
*/
bool Round::CheckBuildNumbers(Card playerCard, vector<Card> playerBuildCards) {

	int aceAs1 = 0;
	int aceAs14 = 0;
	vector<Card> playerHand = player[currentPlayer]->GetHand();
	bool hasRightCards = false;

	for (size_t i = 0; i < playerBuildCards.size(); i++) {
		if (playerBuildCards[i].GetNumber() == 'A') {
			aceAs1++;
			aceAs14 = aceAs14 + 14;
		}
		else {
			aceAs1 = aceAs1 + CardNumber(playerBuildCards[i].GetNumber());
			aceAs14 = aceAs14 + CardNumber(playerBuildCards[i].GetNumber());
		}
	}

	for (size_t i = 0; i < playerHand.size(); i++) {
		if (playerHand[i].GetNumber() == aceAs1 || playerHand[i].GetNumber() == aceAs14) {
			hasRightCards = true;
			return hasRightCards;
		}
	}

	return hasRightCards;
}

int Round::CardNumber(char number) {
	
	if (number == '2') {
		return 2;
	}
	else if (number == '3') {
		return 3;
	}
	else if (number == '4') {
		return 4;
	}
	else if (number == '5') {
		return 5;
	}
	else if (number == '6') {
		return 6;
	}
	else if (number == '7') {
		return 7;
	}
	else if (number == '8') {
		return 8;
	}
	else if (number == '9') {
		return 9;
	}
	else if (number == 'X') {
		return 10;
	}
	else if (number == 'J') {
		return 11;
	}
	else if (number == 'Q') {
		return 12;
	}
	else if (number == 'K') {
		return 13;
	}
	else {
		cout << "Error in the card number in the round class. Returning -1." << endl;
		return -1;
	}
}