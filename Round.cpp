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

SwitchPlayer();

if (!deckOfCards.IsEmpty() && player[0]->IsEmpty() && player[1]->IsEmpty()) {
	DealCardsToPlayers();
}

	} while (!deckOfCards.IsEmpty() && !player[0]->IsEmpty() && !player[1]->IsEmpty()); // while there are still cards in the deck and cards in the player's hands

	lastCapture = "computer";
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
	if (move == 'b') {
		if (CheckBuild() == true) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (move == 'c') {
		if (CheckCapture() == true) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (move == 't') {
		if (CheckTrail() == true) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		cerr << "Error in checking the move in the round class." << endl;
	}
}

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

	if (count != buildSize) {
		cout << "Error, the cards you entered for a build are not on the table" << endl;
		return false;
	}
	else {
		cout << "You were correct with the build!" << endl;
	}

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

void Round::CreatePlayerBuild() {

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

void Round::RemoveTableCards(vector<Card> cards) {


	for (size_t i = 0; i < table.size(); i++) {
		for (size_t j = 0; j < cards.size(); j++) {
			if (table[i].GetCard() == cards[j].GetCard()) {
				table.erase(table.begin() + i);
			}
		}
	}
}

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

	vector<Card> tempHand = player[currentPlayer]->GetHand();
	vector<Card> tempPile = player[currentPlayer]->GetPile();

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

	cout << "Table: ";
	for (size_t i = 0; i < tableBuilds.size(); i++) {
		tableBuilds[i].PrintBuild();
	}

	for (size_t i = 0; i < table.size(); i++) {
		cout << table[i].GetCard() << " ";
	}
	cout << endl;
}

bool Round::CheckCapture() {

	// Getting the player card that they want to put on the build
	playerHandCaptureCard = player[currentPlayer]->GetPlayerCard();
	vector<Card> playerHand = player[currentPlayer]->GetHand();
	bool hasCard = false;

	for (int i = 0; i < playerHand.size(); i++) {
		if (playerHandCaptureCard.GetCard() == playerHand[i].GetCard()) {
			hasCard = true;
		}
	}

	if (PlayerHasCaptureCard() == true && CaptureCardsOnTable() == true) {
		return true;
	}

	return false;
}

bool Round::PlayerHasCaptureCard() {
	// Getting the player card that they want to put on the build
	playerHandCaptureCard = player[currentPlayer]->GetPlayerCard();
	vector<Card> playerHand = player[currentPlayer]->GetHand();
	bool hasCard = false;

	for (int i = 0; i < playerHand.size(); i++) {
		if (playerHandCaptureCard.GetCard() == playerHand[i].GetCard()) {
			hasCard = true;
			return hasCard;
		}
	}
	return hasCard;
}
bool Round::CaptureCardsOnTable() {
	char number = playerHandCaptureCard.GetNumber();
	vector<Card> pile;
	pile.push_back(playerHandCaptureCard);
	

	for (int i = 0; i < table.size(); i++) {
		if (table[i].GetNumber() == number) {
			pile.push_back(table[i]);
			
			player[currentPlayer]->AddToPile(pile);
			return true;
		}
	}

	cout << "There are no cards on the table you can capture with." << endl;
	return false;
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
	for (int i = 0; i < table.size(); i++) {
		for (int j = 0; j < playerHand.size(); j++) {
			if (table[i].GetCard() == playerHand[j].GetCard()) {
				canCapture = true;
			}
		}
	}

	if (canCapture != true) {
		playerHandCaptureCard = player[currentPlayer]->GetPlayerCard();
		vector<Card> trailCard;
		trailCard.push_back(playerHandCaptureCard);
		player[currentPlayer]->RemoveCard(playerHandCaptureCard);
		player[currentPlayer]->AddToPile(trailCard);

		// Adding the trail card to the table
		AddCardsToTable(trailCard);
		return true;
	}

	return false;

}