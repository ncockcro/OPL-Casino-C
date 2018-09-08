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

	do {
		player[currentPlayer]->MakeMove();

		SwitchPlayer();

		player[currentPlayer]->MakeMove();

		SwitchPlayer();

	} while (1); // while there are still cards in the deck and cards in the player's hands
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