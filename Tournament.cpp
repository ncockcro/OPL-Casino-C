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

	string userInput;

	// Prompt the user for what they want to do
	initialDecision = StartMenu();

	// If the decision is "l", than we have to load a file
	if (initialDecision == "l") {
		LoadGame();
	}
	// If the user wants to exit, just return to main
	else if (initialDecision == "e") {
		cout << "Goodbye!" << endl;
		return;
	}

	// Passed general information about the round
	currentRound.SetRoundInfo(round, humanPoints, computerPoints);

	if(initialDecision == "n" && LoadDeck() == true) {
		currentRound.LoadDeck(loadedDeck);
	}
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
		currentRound2.SetRoundInfo(round, humanPoints, computerPoints);
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
		if (userInput.size() > 1) {
			cout << "Try again." << endl;
			userInput = "-1";
		}
	} while (userInput != "n" && userInput != "l" && userInput != "e");

	return userInput;
}

/* *********************************************************************
Function Name: LoadDeck
Purpose: Prompt the user if they want to load a deck or not, if so, handles reading in the file
Parameters: None
Return Value: Whether the user loaded in a deck of not, true or false, a boolean value
Local Variables: userInput, a string which gets the menu option from the player
Algorithm:
1) Prompt the user for what option they want to do
2) Return the option that the user picked
Assistance Received: none
********************************************************************* */
bool Tournament::LoadDeck() {
	string userInput;
	Card tempCard;
	ifstream inputFile;

// Prompting the user if they want to load a deck
do {
	cout << "Do you want to load in a deck? (y,n): ";
	cin >> userInput;

	if (userInput.size() > 1) {
		cout << "Try again." << endl;
		userInput = "-1";
	}
} while (tolower(userInput[0]) != 'y' && tolower(userInput[0]) != 'n');

if (tolower(userInput[0]) == 'n') {
	return false;
}

do {
	cout << "Enter the name of the file you want to load your deck from." << endl;
	cout << "Enter 'n' if you don't want to load a deck: ";
	cin >> userInput;

	inputFile.open(userInput);

	// If the user doesn't actually want to load from a file, then they can say no and start a new game
	if (userInput == "n" || userInput == "N") {
		return false;
	}

	// If the file they entered can't be opened, ask them for another file name
	if (!inputFile.is_open()) {
		cout << "Can not find file, try again." << endl;
	}
} while (!inputFile.is_open());

// Reading each line for a card and storing it into a vector of cards variable
while (inputFile.good()) {
	inputFile >> userInput;
	tempCard.SetCard(userInput);
	loadedDeck.push_back(tempCard);

}

return true;
}

/* *********************************************************************
Function Name: LoadGame
Purpose: Prompt the user for a text file and load a game for it to be picked up from
Parameters: None
Return Value: Whether the user loaded in a deck of not, true or false, a boolean value
Local Variables: userInput, a string which gets the menu option from the player
Algorithm:
1) Prompt the user for what file they want to load in
2) Return the option that the user picked
Assistance Received: none
********************************************************************* */
bool Tournament::LoadGame() {
	string userInput;
	Card tempCard;
	ifstream inputFile;

	do {
		cout << "Enter the name of the file you want to load your deck from." << endl;
		cout << "Enter 'n' if you just want to play a new game: ";
		cin >> userInput;

		inputFile.open(userInput);

		// If the user doesn't actually want to load from a file, then they can say no and start a new game
		if (userInput == "n" || userInput == "N") {
			return false;
		}

		// If the file they entered can't be opened, ask them for another file name
		if (!inputFile.is_open()) {
			cout << "Can not find file, try again." << endl;
		}
	} while (!inputFile.is_open());

	istringstream ss;

	// Reading each line for a card and storing it into a vector of cards variable
	while (inputFile.good()) {
		inputFile >> userInput;

		// Getting the round
		if (userInput == "Round:") {
			inputFile >> userInput;
			loadInfo.round = stoi(userInput);
		}

		inputFile >> userInput;
		inputFile >> userInput;

		// Getting the computer score
		if (userInput == "Score:") {
			inputFile >> userInput;
			loadInfo.computerScore = stoi(userInput);
		}

		inputFile >> userInput;

		// Getting the computer hand
		if (userInput == "Hand:") {
			inputFile >> userInput;
			while (userInput.size() == 2) {
				tempCard.SetCard(userInput);
				loadInfo.computerHand.push_back(tempCard);
				inputFile >> userInput;
			}
		}

		// Getting the computer pile
		if (userInput == "Pile:") {
			inputFile >> userInput;
			while (userInput.size() == 2) {
				tempCard.SetCard(userInput);
				loadInfo.computerPile.push_back(tempCard);
				inputFile >> userInput;
			}
		}

		inputFile >> userInput;

		// Getting the human score
		if (userInput == "Score:") {
			inputFile >> userInput;
			loadInfo.humanScore = stoi(userInput);
		}

		inputFile >> userInput;

		// Getting the human hand
		if (userInput == "Hand:") {
			inputFile >> userInput;
			while (userInput.size() == 2) {
				tempCard.SetCard(userInput);
				loadInfo.humanHand.push_back(tempCard);
				inputFile >> userInput;
			}
		}

		// Getting the human pile
		if (userInput == "Pile:") {
			inputFile >> userInput;
			while (userInput.size() == 2) {
				tempCard.SetCard(userInput);
				loadInfo.humanPile.push_back(tempCard);
				inputFile >> userInput;
			}
		}

		// Getting the table
		if (userInput == "Table:") {
			inputFile >> userInput;
			while (userInput != "Build" && userInput != "Deck:") {
				if (userInput.size() == 2) {
					tempCard.SetCard(userInput);
					loadInfo.table.push_back(tempCard);
				}
				inputFile >> userInput;
			}
		}

		// Handle builds here
		if (userInput == "Build") {
			inputFile >> userInput;
			inputFile >> userInput;
		}

		// Getting the deck
		if (userInput == "Deck:") {
			inputFile >> userInput;
			while (userInput.size() == 2) {
				tempCard.SetCard(userInput);
				loadInfo.deck.push_back(tempCard);
			}
		inputFile >> userInput;
		}

		// Getting the current player
		if (userInput == "Player:") {
			inputFile >> userInput;
			loadInfo.nextPlayer = userInput;
		}

		for (int i = 0; i < loadInfo.deck.size(); i++) {
			cout << loadInfo.deck[i].GetCard() << endl;
		}

	}

	return true;
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
		if (playerCoin.size() > 1) {
			cout << "Try again." << endl;
			playerCoin = "-1";
		}
	} while (tolower(playerCoin[0]) != 'h' && tolower(playerCoin[0]) != 't');

	// If the human guesses the correct virtual coin toss, then they go first
	if (tolower(playerCoin[0]) == 'h' && coin == 0 || tolower(playerCoin[0]) == 't' && coin == 1) {
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