#include "Tournament.h"
#include "Deck.h"
#include "Round.h"



Tournament::Tournament()
{
	humanPoints = 0;
	computerPoints = 0;
	firstPlayer = TossCoin();
	round = 1;
	Round currentRound = Round();

}


Tournament::~Tournament()
{
}

void Tournament::PlayGame() {

	do {
		cout << "Human plays" << endl;

		cout << "Computer plays" << endl;

		humanPoints++;
		computerPoints++;

	} while (humanPoints < 21 && computerPoints < 21);

	GameWon();
}

bool Tournament::TossCoin() {
	srand(time(NULL));

	// coin will either equal 0 for heads or 1 for tails
	int coin = rand() % 2;

	// Prompt the user for what they want to guess is the coin and validate if they typed in the correct letter
	string playerCoin;
	do {
		cout << "Enter 'h' for heads and 't' for tails." << endl;
		cin >> playerCoin;
	} while (toupper(playerCoin[0]) != 'H' && toupper(playerCoin[0]) != 'T');

	// If the human guesses the correct virtual coin toss, then they go first
	if (toupper(playerCoin[0]) == 'H' && coin == 0 || toupper(playerCoin[0]) == 'T' && coin == 1) {
		cout << "You were correct! You go first." << endl;
		return true;
	}
	// Otherwise the computer will go first
	else {
		cout << "You were wrong. The computer goes first." << endl;
		return false;
	}
}

void Tournament::GameWon() {

	// Human won
	if (humanPoints >= 21 && computerPoints < 21) {
		cout << "Congratulations! You won Casino!" << endl;
	}
	// Computer won
	else if (humanPoints < 21 && computerPoints >= 21) {
		cout << "The computer won Casino." << endl;
	}
	// Its a tie
	else {
		cout << "It's a tie!" << endl;
	}
}