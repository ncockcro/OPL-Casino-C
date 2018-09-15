#include "Round.h"



Round::Round()
{
	player.push_back(&p1); // Human player
	player.push_back(&p2); // Computer player

	buildCounter = 0;
}


Round::~Round()
{
}

/* *********************************************************************
Function Name: PlayRound
Purpose: Playing a single round in the tournament
Parameters:
firstplayer, a string passed by value. It holds the player who goes first
Return Value: void
Local Variables: None
Algorithm:
1) WORK IN PROGRESS
Assistance Received: none
********************************************************************* */
void Round::PlayRound(string firstPlayer) {

	if (firstPlayer == "human") {
		currentPlayer = 0;
	}
	else {
		currentPlayer = 1;
	}

	// At the beginning of a round, deal first four cards to player, next four to computer, and next four to the table
	DealCardsToPlayers();
	DealCardsToTable();

	do {
		// Print hand, table, and have the player make a move
		PrintHandAndTable();
		PrintTable();

		// If they make an error in making a move, they will be prompted again to make a correct move
		do {
			player[currentPlayer]->MakeMove();
		} while (CheckMove(player[currentPlayer]->GetPlayerMove()) == false);

		// Switch players
		SwitchPlayer();

		// Print table and have the other player make a move
		PrintHandAndTable();
		PrintTable();
		player[currentPlayer]->MakeMove();
		CheckMove(player[currentPlayer]->GetPlayerMove());

		// Switch again before the loop ends
		SwitchPlayer();

		// So long as there are still cards in the deck and both of the player's hands are empty, deal more cards
		if (!deckOfCards.IsEmpty() && player[0]->IsEmpty() && player[1]->IsEmpty()) {
			DealCardsToPlayers();
		}

	} while (!deckOfCards.IsEmpty() && !player[0]->IsEmpty() && !player[1]->IsEmpty()); // while there are still cards in the deck and cards in the player's hands

	// Print out the player's piles at the end of the round
	PrintPlayerPiles();

}

/* *********************************************************************
Function Name: GetLastCapture
Purpose: Getter for getting the player who made the last capture
Parameters: None
Return Value: const string
Local Variables: None
Algorithm:
1) Returns lastCapture
Assistance Received: none
********************************************************************* */
const string Round::GetLastCapture() {
	return lastCapture;
}

/* *********************************************************************
Function Name: GetPlayerPile
Purpose: Getter for getting the human player's pile at the end of a round
Parameters: None
Return Value: const vector<Card>
Local Variables: None
Algorithm:
1) Returns the human player's pile
Assistance Received: none
********************************************************************* */
const vector<Card> Round::GetPlayerPile() {
	return player[0]->GetPile();
}

/* *********************************************************************
Function Name: GetComputerPile
Purpose: Getter for getting the computer player's pile at the end of a round
Parameters: None
Return Value: const vector<Card>
Local Variables: None
Algorithm:
1) Returns the computer player's pile
Assistance Received: none
********************************************************************* */
const vector<Card> Round::GetComputerPile() {
	return player[1]->GetPile();
}

/* *********************************************************************
Function Name: SwitchPlayer
Purpose: If the player is human, switches to computer and vice versa
Parameters: None
Return Value: void
Local Variables: None
Algorithm:
1) If currentPlayer is 0 (human), switch it to 1 (computer) and vice versa
Assistance Received: none
********************************************************************* */
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

/* *********************************************************************
Function Name: DealCardsToPlayers
Purpose: At the beginning of round, deals four cards to each of the players
Parameters:
firstplayer, a string passed by value. It holds the player who goes first
Return Value: void
Local Variables: None
Algorithm:
1) Sets the humans hand with four cards from the deck
2) Deletes four cards from the deck
3) Sets the comuter hand with four cards from the deck
4) Deletes four cards from the deck
Assistance Received: none
********************************************************************* */
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

/* *********************************************************************
Function Name: DealCardsToTable()
Purpose: Deals four cards to the table at the beginning of a round
Parameters: None
Return Value: void
Local Variables: None
Algorithm:
1) Deals four cards to the table
2) Deletes four cards from the deck
Assistance Received: none
********************************************************************* */
void Round::DealCardsToTable() {

	// Deal four cards to the table
	SetTable(deckOfCards.GetDeck());

	// Remove four cards from the deck
	deckOfCards.RemoveFourCards();
}

/* *********************************************************************
Function Name: SetTable
Purpose: Add four cards to the table
Parameters:
deckOfCards, a vector of cards passed by value. It holds the four cards to be placed on the table
Return Value: void
Local Variables: None
Algorithm:
1) Push four cards onto the table vector of cards
Assistance Received: none
********************************************************************* */
void Round::SetTable(vector<Card> deckOfCards) {

	// Put four cards onto the table after four cards were dealt to the human and computer
	table.push_back(deckOfCards[0]);
	table.push_back(deckOfCards[1]);
	table.push_back(deckOfCards[2]);
	table.push_back(deckOfCards[3]);
}

/* *********************************************************************
Function Name: CheckMove
Purpose: Depending on the move of a player, it will call a function to check if it is valid
Parameters:
move, a char passed by value. It holds the move the player or computer is trying to make
Return Value: A boolean, true if the player can make the move or false if they cant
Local Variables: None
Algorithm:
1) If the move is a build, check the build
2) If the move is a capture, check the capture
3) If the move is a trail, check the trail
Assistance Received: none
********************************************************************* */
bool Round::CheckMove(char move) {

	// If the user wants to build...
	if (move == 'b') {
		if (CheckBuild() == true) {
			return true;
		}
		else {
			return false;
		}
	}

	// If the user wants to capture...
	else if (move == 'c') {
		if (CheckCapture() == true) {
			return true;
		}
		else {
			return false;
		}
	}

	// If the user wants to trail...
	else if (move == 't') {
		if (CheckTrail() == true) {
			return true;
		}
		else {
			return false;
		}
	}

	// Error message if something went wrong and didnt get the correct move character
	else {
		cerr << "Error in checking the move in the round class." << endl;
		return false;
	}
}

/* *********************************************************************
Function Name: CheckBuild
Purpose: To check if the user is able to make a build based on the cards they entered
Parameters: None
Return Value: Whether the player was able to build or not, a boolean value
Local Variables:
buildSize, an integer used for holding how many cards the user wants to build with
count, an integer used for making sure the cards the user entered are on the table
Algorithm:
1) Get the player's hand card used for the build and the cards from the table they want to build with
2) Go through the table cards and make sure the cards they entered are on the table
3) Have an if statement to check and make sure that if the cards add up to be able to make a build
4) If the cards are able to make a build, call another function to handle removing cards from the 
player's hand and table and add them to the player's pile
Assistance Received: none
********************************************************************* */
bool Round::CheckBuild() {

	// Getting the player card that they want to put on the build
	playerHandBuildCard = player[currentPlayer]->GetPlayerCard();
	// Getting the card on the table that the player wants to use for a build
	playerTableBuildCards = player[currentPlayer]->GetBuildCards();

	int buildSize = playerTableBuildCards.size();
	int count = 0;

	// This is checking to make sure that the cards the user entered in to make a build are actually on the table
	for (size_t i = 0; i < table.size(); i++) {
		for (size_t j = 0; j < playerTableBuildCards.size(); j++) {
			if (table[i].GetCard() == playerTableBuildCards[j].GetCard()) {
				count++;
			}
		}
	}

	// If one of the cards the player entered did not match any on the table, they entered a wrong card
	if (count != buildSize) {
		cout << "Error, the cards you entered for a build are not on the table" << endl;
		return false;
	}
	else {
		cout << "You were correct with the build!" << endl;
	}

	// If the cards are suitable for a build, then the build will be created
	if (CheckBuildNumbers(playerHandBuildCard, playerTableBuildCards)) {
		CreatePlayerBuild();
	}
	else {
		cout << "Error, you can not make a build with the cards you entered." << endl;
		return false;
	}
	return true;
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

	// Local variables
	int aceAs1 = 0;
	int aceAs14 = 0;
	vector<Card> playerHand = player[currentPlayer]->GetHand();
	bool hasRightCards = false;

	// Iterate through the cards the player wants to build with and count their values
	for (size_t i = 0; i < playerBuildCards.size(); i++) {

		// If the card is an ace, we must increment the two different counts with 1 and 14 as the ace card
		if (playerBuildCards[i].GetNumber() == 'A') {
			aceAs1++;
			aceAs14 = aceAs14 + 14;
		}
		else {
			aceAs1 += CardNumber(playerBuildCards[i].GetNumber());
			aceAs14 += CardNumber(playerBuildCards[i].GetNumber());
		}
	}

	// If the player has a card that equals the total value of the build, then return true
	for (size_t i = 0; i < playerHand.size(); i++) {
		if (playerHand[i].GetNumber() == aceAs1 || playerHand[i].GetNumber() == aceAs14) {
			hasRightCards = true;
			return hasRightCards;
		}
	}

	return hasRightCards;
}

/*
Function Name: CardNumber
Purpose: Take a character as input and output the number that it represents.
Parameters:
number, a char, the number of a card (e.g. 2, X, J)
Return Value: Int
Local Variables:None
Algorithm: Go through if, else if, and else statements til the corrent number is found.
Assistance Received: none
*/
int Round::CardNumber(char number) {
	
	if (number == 'A') {
		return 1;
	}
	else if (number == '2') {
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
		cerr << "Error in the card number in the round class. Returning -1." << endl;
		return -1;
	}
}

/* *********************************************************************
Function Name: CreatePlayerBuild
Purpose: To remove the cards from the table and player and incorporate them into a build object
Parameters: None
Return Value: Void
Local Variables: None
Algorithm:
1) Set the owner of the build based on the player currently playing
2) Add the cards to the build object and remove them from the table and player hand
Assistance Received: none
********************************************************************* */
void Round::CreatePlayerBuild() {

	// Initialize a build
	tableBuilds.push_back(Build());

	// Setting the owner of a particular build
	if (currentPlayer == 0) {
		tableBuilds[buildCounter].SetOwner("human");
	}
	else {
		tableBuilds[buildCounter].SetOwner("computer");
	}

	// Adding the card from the player's hand onto the build that way I can send all the cards to be added to build object
	playerTableBuildCards.push_back(playerHandBuildCard);

	// With all the cards being used for a build, we push them onto the vector of builds
	tableBuilds[buildCounter].SetBuildOfCards(playerTableBuildCards);

	// Then remove the cards from the player's hand and the table since those cards are now part of a build
	RemoveTableCards(playerTableBuildCards);
	player[currentPlayer]->RemoveCard(playerHandBuildCard);
	
	buildCounter++;
}

/* *********************************************************************
Function Name: RemoveTableCards
Purpose: Remove a series of cards that are passed in from the table
Parameters:
cards, a vector of cards passed by value. It holds the cards to be removed
Return Value: Void
Local Variables: None
Algorithm:
1) Iterate through the table and the cards to be removed...
2) If the card to be removed matches with the one from the table, it will be erased and the vector will shift everything over
Assistance Received: none
********************************************************************* */
void Round::RemoveTableCards(vector<Card> cards) {

	// First go through the table vector, then through the cards vector that was passed in...
	for (size_t i = 0; i < table.size(); i++) {
		for (size_t j = 0; j < cards.size(); j++) {

			// If there is a match, erase the card from the vector
			if (table[i].GetCard() == cards[j].GetCard()) {
				table.erase(table.begin() + i);
			}
		}
	}
}

/* *********************************************************************
Function Name: AddCardsToTable
Purpose: To add any cards that were passed into it to the table
Parameters:
cards, a vector of cards passed by value. It holds cards to be added to the table
Return Value: Void
Local Variables: None
Algorithm:
1) Iterate through the vector of cards passed in and add them to the table
Assistance Received: none
********************************************************************* */
void Round::AddCardsToTable(vector<Card> cards) {
	for (size_t i = 0; i < cards.size(); i++) {
		table.push_back(cards[i]);
	}
}

/* *********************************************************************
Function Name: PrintHandAndTable
Purpose: Print the current hand of a player
Parameters: None
Return Value: Void
Local Variables: tempHand, gets the players hand and stores it there temporarily
Algorithm:
1) Get the player's current hand and print it out through a for loop
Assistance Received: none
********************************************************************* */
void Round::PrintHandAndTable() {

	// Get the hand of the player and their pile
	vector<Card> tempHand = player[currentPlayer]->GetHand();
	vector<Card> tempPile = player[currentPlayer]->GetPile();

	// If it is the human, print out their hand and pile
	if (currentPlayer == 0) {
		cout << "Your hand: ";
		for (size_t i = 0; i < tempHand.size(); i++) {
			cout << tempHand[i].GetCard() << " ";
		}
		cout << endl;

		cout << "Your pile: ";
		for (size_t i = 0; i < tempPile.size(); i++) {
			cout << tempPile[i].GetCard() << " ";
		}
		cout << endl;
	}
	// If it is the computer, print out their hand and pile
	else {
		cout << "Computer hand: ";
		for (size_t i = 0; i < tempHand.size(); i++) {
			cout << tempHand[i].GetCard() << " ";
		}
		cout << endl;

		cout << "Your pile: ";
		for (size_t i = 0; i < tempPile.size(); i++) {
			cout << tempPile[i].GetCard() << " ";
		}
		cout << endl;
	}
}

/* *********************************************************************
Function Name: PrintTable
Purpose: Print the current table of the round
Parameters: None
Return Value: Void
Local Variables: None
Algorithm:
1) Have a for loop to print any builds on the table
2) Have another for loop to print out the table
Assistance Received: none
********************************************************************* */
void Round::PrintTable() {

	// First printing out any builds that were built
	cout << "Table: ";
	for (size_t i = 0; i < tableBuilds.size(); i++) {
		tableBuilds[i].PrintBuild();
	}

	// Then printing out the rest of the table
	for (size_t i = 0; i < table.size(); i++) {
		cout << table[i].GetCard() << " ";
	}
	cout << endl;
}

/* *********************************************************************
Function Name: CheckCapture
Purpose: To check if the player is elegible to make a capture based on what they entered
Parameters: None
Return Value: Whether the player can make a capture or not, a boolean value
Local Variables: None
Algorithm:
1) Get the card the player wants to capture with and the player's hand
2) Check and see if the player has any cards on the table to capture or any sets
Assistance Received: none
********************************************************************* */
bool Round::CheckCapture() {

	// Getting the player card that they want to put on the build
	playerHandCaptureCard = player[currentPlayer]->GetPlayerCard();
	vector<Card> playerHand = player[currentPlayer]->GetHand();

	if (CaptureCardsOnTable() == true) {
		return true;
	}

	return false;
}

bool Round::CaptureCardsOnTable() {
	char number = playerHandCaptureCard.GetNumber();
	vector<Card> pile;
	vector<Card> removedTableCards;
	pile.push_back(playerHandCaptureCard);
	bool canCapture = false;


	for (size_t i = 0; i < table.size(); i++) {
		if (table[i].GetNumber() == number) {
			pile.push_back(table[i]);
			removedTableCards.push_back(table[i]);
			canCapture = true;
		}
	}

	// If everything is correct, add the cards and remove them properly
	if (canCapture = true) {
		player[currentPlayer]->RemoveCard(playerHandCaptureCard);
		RemoveTableCards(removedTableCards);

		player[currentPlayer]->AddToPile(pile);
	}

	vector<Card> setCards;
	int count = 0;
	int aceAs1Count = 0;
	int aceAs14Count = 0;

	if (player[currentPlayer]->GetPlayerWantSet() == 'y') {
		setCards = player[currentPlayer]->MakeSet();
	}

	for (size_t i = 0; i < table.size(); i++) {
		for (size_t j = 0; j < setCards.size(); j++) {
			if (table[i].GetCard() == setCards[j].GetCard()) {

				pile.push_back(table[i]);

				if (setCards[j].GetNumber() != 'A') {
					aceAs1Count += CardNumber(setCards[j].GetNumber());
				}
				else {
					aceAs1Count += CardNumber(setCards[j].GetNumber());
					aceAs14Count += 14;
				}
				count++;
			}
		}
	}

	if (aceAs1Count == CardNumber(playerHandCaptureCard.GetNumber()) || aceAs14Count == CardNumber(playerHandCaptureCard.GetNumber())) {
		player[currentPlayer]->RemoveCard(playerHandCaptureCard);
		RemoveTableCards(removedTableCards);

		player[currentPlayer]->AddToPile(pile);
	}
	else {
		cout << "Those set cards were not in the table." << endl;
	}

	if (currentPlayer == 0) {
		lastCapture = "human";
	}
	else {
		lastCapture = "computer";
	}

	if (canCapture == false) {
		cout << "You can not capture any cards on the table." << endl;
	}
	return canCapture;
}

/* *********************************************************************
Function Name: CheckTrail
Purpose: To validate if the player can make a trail move
Parameters: None
Return Value: True if a trail is valid, false otherwise
Local Variables:
playerHand, a vector of cards which temporarily holds the players current hand
canCapture, a boolean which is true if the player can capture, false otherwise
trailCard, a vector of cards which is to format the trail card in a way to be passed on and added to the table
Algorithm:
1) Check if the player is trying to make a trail when they have a card in their hand they can capture with the same on the table
2) If not, remove the trail card from the player's hand
3) Add the trail card to the table
Assistance Received: none
********************************************************************* */
bool Round::CheckTrail() {

	vector<Card> playerHand;
	playerHand = player[currentPlayer]->GetHand();

	bool canCapture = false;

	for (size_t i = 0; i < table.size(); i++) {
		for (size_t j = 0; j < playerHand.size(); j++) {
			if (table[i].GetNumber() == playerHand[j].GetNumber()) {
				canCapture = true;
			}
		}
	}

	if (canCapture != true) {
		playerHandCaptureCard = player[currentPlayer]->GetPlayerCard();
		vector<Card> trailCard;
		trailCard.push_back(playerHandCaptureCard);
		player[currentPlayer]->RemoveCard(playerHandCaptureCard);

		// Adding the trail card to the table
		AddCardsToTable(trailCard);
		return true;
	}

	cout << "You can not trail because there is a card on the table with the same value as a card in your hand." << endl;
	return false;

}

/* *********************************************************************
Function Name: PrintPlayerPiles
Purpose: Prints both of the player's piles at the end of a round
Parameters: None
Return Value: None
Local Variables: None
Algorithm:
1) Call print pile from the player class
Assistance Received: none
********************************************************************* */
void Round::PrintPlayerPiles() {

	cout << "Player's pile: ";
	player[0]->PrintPile();

	cout << "Computer's pile: ";
	player[1]->PrintPile();
}