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

		SwitchPlayer();

		player[currentPlayer]->MakeMove();

		SwitchPlayer();

		if (!deckOfCards.IsEmpty() && player[0]->IsEmpty() && player[1]->IsEmpty()) {
			DealCardsToPlayers();
		}

	} while (!deckOfCards.IsEmpty() && !player[0]->IsEmpty() && !player[1]->IsEmpty()); // while there are still cards in the deck and cards in the player's hands

	lastCapture = "computer";
}

// Getter for getting the player who made the last capture.
string Round::GetLastCapture() {
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

void Round::DealCardsToTable() {

	// Deal four cards to the table
	SetTable(deckOfCards.GetDeck());

	// Remove four cards from the deck
	deckOfCards.RemoveFourCards();
}

void Round::SetTable(vector<string> deckOfCards) {

	table.push_back(deckOfCards[0]);
	table.push_back(deckOfCards[1]);
	table.push_back(deckOfCards[2]);
	table.push_back(deckOfCards[3]);
}