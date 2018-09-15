#include "Tournament.h"

// Default constructor
Tournament::Tournament()
{
	humanPoints = 0;
	computerPoints = 0;
	round = 1;

}

// Default destructor
Tournament::~Tournament()
{
}

/* *********************************************************************
Function Name: PlayGame
Purpose: The main game loop of Casino which runs the tournament 
Parameters: None
Return Value: Void
Local Variables:
currentRound2, a new Round object for each round after the first one
Algorithm:
1) Call the StartMenu function to find out what the player wants to do
2) Play the first round and toss a coin to see who goes first
3) Save the player that captured last, increment the round counter, and calculate the points that were made
4) Repeat this process until the first player reaches 21 points
5) Then output the winner
Assistance Received: none
********************************************************************* */
void Tournament::PlayGame() {

	initialDecision = StartMenu();

	// The first round is played by if the human won the toin coss or not
	currentRound.PlayRound(TossCoin());

	// Then we save the person who captured the last card and increment the round counter
	SaveLastCaptured(currentRound.GetLastCapture());
	IncrementRound();

	CalculatePoints();

	// The rest of the game is continued onwards until one person has scored the correct amount of points
	do {
		
		currentRound = Round();
		// After the toin coss, it is the player whoever captured last
		Round currentRound2 = Round();
		currentRound2.PlayRound(lastCaptured);

		CalculatePoints();

	} while (humanPoints < 21 && computerPoints < 21);

	// Checks the points of each player to see if someone won or it was a tie
	GameWon();
}

/* *********************************************************************
Function Name: StartMenu
Purpose: Prompt the user when the program is first run with different options
Parameters: None
Return Value: The option the player chose, a string
Local Variables: userInput, a string which gets the menu option from the player
Algorithm:
1) Prompt the user for what option they want to do
2) Return the option that the user picked
Assistance Received: none
********************************************************************* */
string Tournament::StartMenu() {

	string userInput;

	cout << "Welcome to the game of Casino!" << endl;
	cout << endl;

	do {
		cout << "'n' for new game: " << endl;
		cout << "'l' for load game: " << endl;
		cout << "'e' to exit: ";
		cin >> userInput;
	} while (userInput != "n" && userInput != "l" && userInput != "e");

	return userInput;
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
		cout << "Enter 'h' for heads and 't' for tails: ";
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

// Increases the round counter.
void Tournament::IncrementRound() {
	round++;
}

void Tournament::SaveLastCaptured(string capturer) {

	if (capturer == "human" || capturer == "computer") {
		lastCaptured = capturer;
	}
	else {
		cout << "Error in saving the last captured player." << endl;
	}
}

void Tournament::CalculatePoints() {

	vector<Card> humanPile = currentRound.GetPlayerPile();
	vector<Card> computerPile = currentRound.GetComputerPile();
	int humanRoundPoints = 0;
	int computerRoundPoints = 0;
	int humanSpadeCount = 0;
	int computerSpadeCount = 0;

	// Checking for specific cards through the human pile
	for (size_t i = 0; i < humanPile.size(); i++) {

		if (humanPile[i].GetSuit() == 'S') {
			humanSpadeCount++;
		}
		if (humanPile[i].GetCard() == "S2") {
			humanRoundPoints++;
		}
		if (humanPile[i].GetCard() == "DX") {
			humanRoundPoints += 2;
		}
		if (humanPile[i].GetNumber() == 'A') {
			humanRoundPoints++;
		}
	}

	// Checking for specific cards through the computer pile
	for (size_t i = 0; i < computerPile.size(); i++) {

		if (computerPile[i].GetSuit() == 'S') {
			humanSpadeCount++;
		}
		if (computerPile[i].GetCard() == "S2") {
			computerRoundPoints++;
		}
		if (computerPile[i].GetCard() == "DX") {
			computerRoundPoints += 2;
		}
		if (computerPile[i].GetNumber() == 'A') {
			computerRoundPoints++;
		}
	}

	// Checking if one player has more cards than the other
	if (humanPile.size() > computerPile.size()) {
		humanRoundPoints += 3;
	}
	else if (humanPile.size() < computerPile.size()) {
		computerRoundPoints += 3;
	}

	// Checking if one player has more spades than the other
	if (humanSpadeCount > computerSpadeCount) {
		humanRoundPoints++;
	}
	else if (humanSpadeCount < computerSpadeCount) {
		computerRoundPoints++;
	}

	// Add the round points to the total count of each player's points
	humanPoints += humanRoundPoints;
	computerPoints += computerRoundPoints;

	// Outputting score information at the end of a round
	cout << "Total number of cards by the player: " << humanPile.size() << endl;
	cout << "Total number of cards by the computer: " << computerPile.size() << endl;
	cout << endl;

	cout << "Total number of spades by the player: " << humanSpadeCount << endl;
	cout << "Total number of spades by the computer: " << computerSpadeCount << endl;
	cout << endl;

	cout << "Total amount of points earned by the player this round: " << humanRoundPoints << endl;
	cout << "Total amount of points earned by the computer this round: " << computerRoundPoints << endl;

	cout << "Total player points: " << humanPoints << endl;
	cout << "Total computer points: " << computerPoints << endl;
}