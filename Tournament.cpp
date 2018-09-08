#include "Tournament.h"

Tournament::Tournament()
{
	humanPoints = 0;
	computerPoints = 0;
	round = 1;

}


Tournament::~Tournament()
{
}

void Tournament::PlayGame() {

	// The first round is player by if the human won the toin coss or not
	currentRound.PlayRound(TossCoin());

	do {
		// After the toin coss, it is the player whoever captured last
		currentRound.PlayRound(currentRound.GetLastCapture());

		humanPoints++;
		computerPoints++;

	} while (humanPoints < 21 && computerPoints < 21);

	// Checks the points of each player to see if someone won or it was a tie
	GameWon();
}

void Tournament::AddPoints() {

}

// Function for the coin toss at the beginning of a new game where a randomly generated number represents
// a coin being tossed and the player has to try and guess it to go first.
string Tournament::TossCoin() {
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
		return "human";
	}
	// Otherwise the computer will go first
	else {
		cout << "You were wrong. The computer goes first." << endl;
		return "computer";
	}
}

// Checks to see if a specific player won the game or if it was a tie.
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