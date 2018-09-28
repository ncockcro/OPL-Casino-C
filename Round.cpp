#include "Round.h"


Round::Round()
{
	// Human player
	player.push_back(&p1);
	// Computer player
	player.push_back(&p2);

	buildCounter = 0;
	playTrue = true;

	deckOfCards = Deck();
	loadGame = false;
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
Local Variables:
playTrue, is true if a player's move is valid, false otherwise, a boolean value
Algorithm:
1) WORK IN PROGRESS
Assistance Received: none
********************************************************************* */
void Round::PlayRound(string firstPlayer) {

	if (firstPlayer == "Human") {
		currentPlayer = 0;
	}
	else {
		currentPlayer = 1;
	}

	// If we are NOT loading from a previous game then we need to deal cards to the players
	if (loadGame == false) {
		// At the beginning of a round, deal first four cards to player, next four to computer, and next four to the table
		DealCardsToPlayers();
		DealCardsToTable();
	}

	do {
		// Print hand, pile, and table and then have the player make a move
		PrintHandPileAndTable();

		// Player 1 is going now
		// If they make an error in making a move, they will be prompted again to make a correct move
		do {
			player[currentPlayer]->MakeMove(table, tableBuilds);

			// If the player made the choice to save the game, then this function will be triggered
			if (player[currentPlayer]->GetPlayerWantSave() == true) {
				SaveGame();
			}

		} while (CheckMove(player[currentPlayer]->GetPlayerMove()) == false);

		// Print what kind of move the player just made
		player[currentPlayer]->PrintMove();

		// Switch players
		SwitchPlayer();

		// Print table and have the other player make a move
		PrintHandPileAndTable();

		// Player 2 is going now
		do {
			player[currentPlayer]->MakeMove(table, tableBuilds);

			// If the player made the choice to save the game, then this function will be triggered
			if (player[currentPlayer]->GetPlayerWantSave() == true) {
				SaveGame();
			}

		} while (CheckMove(player[currentPlayer]->GetPlayerMove()) == false);

		// Print what kind of move the player just made
		player[currentPlayer]->PrintMove();

		// Switch again before the loop ends
		SwitchPlayer();

		// So long as there are still cards in the deck and both of the player's hands are empty, deal more cards
		if (!deckOfCards.IsEmpty() && player[0]->IsEmpty() && player[1]->IsEmpty()) {
			DealCardsToPlayers();
		}

	// while there are still cards in the deck and cards in the player's hands
	} while (!deckOfCards.IsEmpty() && !player[0]->IsEmpty() && !player[1]->IsEmpty());

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
string Round::GetLastCapture() const{
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
vector<Card> Round::GetPlayerPile() const{
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
vector<Card> Round::GetComputerPile() const{
	return player[1]->GetPile();
}

/* *********************************************************************
Function Name: SetRoundInfo
Purpose: Setting the round info so if the player decides to save the game, the info is available
Parameters:
round, an integer value, holds the current round
humanScore, an integer value, holds the human's score
computerScore, an integer value, holds the computer's score
Return Value: Void
Local Variables: None
Algorithm:
1) Set the round, human score, and computer score
Assistance Received: none
********************************************************************* */
void Round::SetRoundInfo(int round, int humanScore, int computerScore) {

	// So long as it is not a negative round or 0, set the currentRound to be that round
	if (round > 0) {
		currentRound = round;
	}
	else {
		cerr << "Error in setting round in the round class." << endl;
	}

	// So long as the human and computer scores are 0 or greater, set them
	if (humanScore >= 0 && computerScore >= 0) {
		humanPoints = humanScore;
		computerPoints = computerScore;
	}
	else {
		cerr << "Error in setting score in the round class." << endl;
	}
}

/* *********************************************************************
Function Name: SetRoundInfo
Purpose: Setting the round info so if the player decides to save the game, the info is available
Parameters:
round, an integer value, holds the current round
humanScore, an integer value, holds the human's score
computerScore, an integer value, holds the computer's score
Return Value: Void
Local Variables: None
Algorithm:
1) Set the round, human score, and computer score
Assistance Received: none
********************************************************************* */
void Round::LoadDeck(vector<Card> loadedDeck) {
	deckOfCards = Deck(loadedDeck);
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
		cerr << "Error with switching players!" << endl;
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
4) If the move is for help, return false
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

	// If the player asked for help, return false so they can actually make a move
	else if (move == 'h') {
		return false;
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
addExistingBuildSuccessful, a boolean for seeing if the player can add to a build or not
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
	bool addExistingBuildSuccessful = false;

	// If the player is creating a new build...
	if (tolower(player[currentPlayer]->GetNewOrExistingBuild()) == 'n') {

		if (playerTableBuildCards.size() < 1) {
			cout << "You did not enter any cards from the table to make a build with." << endl;
			return false;
		}

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
			cout << "You can not make a build with those cards." << endl;
			return false;
		}

		// If the cards are suitable for a build , then the build will be created
		if (CheckBuildNumbers(playerHandBuildCard, playerTableBuildCards)) {
			CreatePlayerBuild();
		}
		else {
			cout << "Error, you can not make a build with the cards you entered." << endl;
			return false;
		}
		return true;
	}
	// If the player wants to add to an existing build, then we will go through each build to find which one
	// they want to add to and if it is possible
	else if (tolower(player[currentPlayer]->GetNewOrExistingBuild()) == 'e') {
		for (size_t i = 0; i < tableBuilds.size(); i++) {
			
			// If this function that is called returns true, then it was successful in validating the new build with the
			// card added and created the new build already so all that is left to do is return true
			// Here, we are also passing into the function the card to be added, the existing build, the current player,
			// and the current player's hand
			if (tableBuilds[i].CheckAndAddCardInBuild(playerHandBuildCard, player[currentPlayer]->GetExistingBuildCard(), currentPlayer,
				player[currentPlayer]->GetHand())) {
				player[currentPlayer]->SetPrintTableBuildCards(tableBuilds[i].GetBuildOfCards());
				addExistingBuildSuccessful = true;
			}
		}
		// If addExistingBuildSuccessful is true, then that means the card was added to the build successfully
		if (addExistingBuildSuccessful) {
			return true;
		}
		// Otherwise, they were not able to add the card to the build they specified
		else {
			cout << "There are no builds you can add to with those cards." << endl;
			return false;
		}
	}

	// Error handling in case something really got messed up and the program can't determine
	// if the user wants a new or existing build
	else {
		cerr << "Error, dont know if it is a new or existing build in round class." << endl;
		return false;
	}
}

/***********************************************************************
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
********************************************************************* */
bool Round::CheckBuildNumbers(Card playerCard, vector<Card> playerBuildCards) {

	// Local variables
	int aceAs1 = 0;
	int aceAs14 = 0;
	vector<Card> playerHand = player[currentPlayer]->GetHand();
	bool hasRightCards = false;

	playerBuildCards.push_back(playerCard);

	// Iterate through the cards the player wants to build with and count their values
	for (size_t i = 0; i < playerBuildCards.size(); i++) {

		// If the card is an ace, we must increment the two different counts with 1 and 14 as the ace card
		if (playerBuildCards[i].GetNumber() == 'A') {
			aceAs1++;
			aceAs14 = aceAs14 + 14;
		}
		// Otherwise, just increment with whatever the number is
		else {
			aceAs1 += CardNumber(playerBuildCards[i].GetNumber());
			aceAs14 += CardNumber(playerBuildCards[i].GetNumber());
		}
	}

	// If the player has a card that equals the total value of the build, then return true
	for (size_t i = 0; i < playerHand.size(); i++) {
		if (CardNumber(playerHand[i].GetNumber()) == aceAs1 || CardNumber(playerHand[i].GetNumber()) == aceAs14) {
			hasRightCards = true;
			player[currentPlayer]->AddToPlayerBuildCards(playerHand[i]);
			return hasRightCards;
		}
		// If the player is creating a build with an ace as the card they will use to capture it with later...
		if (playerHand[i].GetNumber() == 'A' && aceAs14) {
			hasRightCards = true;
			player[currentPlayer]->AddToPlayerBuildCards(playerHand[i]);
			return hasRightCards;
		}
	}

	return hasRightCards;
}

/***********************************************************************
Function Name: CardNumber
Purpose: Take a character as input and output the number that it represents.
Parameters:
number, a char, the number of a card (e.g. 2, X, J)
Return Value: Int
Local Variables:None
Algorithm: Go through if, else if, and else statements til the corrent number is found.
Assistance Received: none
********************************************************************* */
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

	vector<Card> playersBuildCards = player[currentPlayer]->GetPlayerBuildCards();
	char lastAddedCard = playersBuildCards.back().GetNumber();
	vector<Card> handCards;

	// Initialize a build
	tableBuilds.push_back(Build());

	// Setting the owner of a particular build
	if (currentPlayer == 0) {
		tableBuilds[buildCounter].SetOwner(0);
	}
	else {
		tableBuilds[buildCounter].SetOwner(1);
		
	}

	tableBuilds[buildCounter].SetValueOfBuild(CardNumber(lastAddedCard));

	// This is for setting the card that is needed for capturing the build
	handCards = player[currentPlayer]->GetHand();
	for (size_t i = 0; i < handCards.size(); i++) {
		if (CardNumber(handCards[i].GetNumber()) == CardNumber(lastAddedCard)) {
			tableBuilds[buildCounter].SetCaptureCardOfBuild(handCards[i]);
			break;
		}
	}

	// Saving the build cards to be outputted after the move is done
	player[currentPlayer]->SetPrintTableBuildCards(playerTableBuildCards);

	// Adding the card from the player's hand onto the build that way I can send all the cards to be added to build object
	playerTableBuildCards.push_back(playerHandBuildCard);

	// With all the cards being used for a build, we push them onto the vector of builds
	tableBuilds[buildCounter].SetBuildOfCards(playerTableBuildCards);

	// If the card the player is going to capture the build with is an ace, set the value of the build to 14
	if (playersBuildCards.back().GetNumber() == 'A') {
		tableBuilds[buildCounter].SetValueOfBuild(14);
	}
	// Otherwise, set the value to be whatever else the card is
	else {
		tableBuilds[buildCounter].SetValueOfBuild(CardNumber(playersBuildCards.back().GetNumber()));
	}

	// Then remove the cards from the player's hand and the table since those cards are now part of a build
	RemoveTableCards(playerTableBuildCards);
	player[currentPlayer]->RemoveCard(playerHandBuildCard);
	
	buildCounter++;


	
}

/* *********************************************************************
Function Name: AddToExistingBuild
Purpose: To validate if a player can add to a build and if so, add to it
Parameters: None
Return Value: Returns true if successful, false otherwise, a bolean value
Local Variables: None
Algorithm:
1) 
Assistance Received: none
********************************************************************* */
bool Round::AddToExistingBuild() {
	return false;
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
	for (size_t i = 0; i < cards.size(); i++) {
		for (size_t j = 0; j < table.size(); j++) {

			// If there is a match, erase the card from the vector
			if (cards[i].GetCard() == table[j].GetCard()) {
				table.erase(table.begin() + j);
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
void Round::PrintHandPileAndTable() {

	// Get the hand of the player and their pile
	vector<Card> humanHand = player[0]->GetHand();
	vector<Card> humanPile = player[0]->GetPile();
	vector<Card>computerHand = player[1]->GetHand();
	vector<Card> computerPile = player[1]->GetPile();

	cout << endl;
	// If it is the human, print out their hand and pile
	cout << "Your hand: ";
	for (size_t i = 0; i < humanHand.size(); i++) {
		cout << humanHand[i].GetCard() << " ";
	}
	cout << endl;

	cout << "Your pile: ";
	for (size_t i = 0; i < humanPile.size(); i++) {
		cout << humanPile[i].GetCard() << " ";
	}
	cout << endl;


	// If it is the computer, print out their hand and pile
	cout << "Computer hand: ";
	for (size_t i = 0; i < computerHand.size(); i++) {
		cout << computerHand[i].GetCard() << " ";
	}
	cout << endl;
	cout << "Computer pile: ";
	for (size_t i = 0; i < computerPile.size(); i++) {
		cout << computerPile[i].GetCard() << " ";
	}
	cout << endl;


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

	// Getting the player card that they want to put on the build and the current player's hand
	playerHandCaptureCard = player[currentPlayer]->GetPlayerCard();
	vector<Card> playerHand = player[currentPlayer]->GetHand();

	// Local variables for capturing
	char number = CardNumber(playerHandCaptureCard.GetNumber());
	vector<Card> pile;
	vector<Card> removedTableCards;
	pile.push_back(playerHandCaptureCard);
	bool canCapture = false;

	// Local variables for sets
	vector<Card> setCards;
	int count = 0;
	int aceAs1Count = 0;
	int aceAs14Count = 0;
	string userInput;

	// If the player said they wanted to make a set, then we will check those cards with the table cards first
	// to make sure they are on the table and add up to the capture card
	if (player[currentPlayer]->GetPlayerWantSet() == 'y') {
		vector <Set> playerSets;
		playerSets = player[currentPlayer]->GetPlayerOfSetCards();
		vector<Card> cardsOfSet;

		// Cycling through all of the sets that the player wants to capture
		for (size_t i = 0; i < playerSets.size(); i++) {
			cardsOfSet = playerSets[i].GetCardsOfSet();

			// For each set, we must check and make sure that the cards are actually on the table
			for (size_t j = 0; j < table.size(); j++) {
				for (size_t l = 0; l < cardsOfSet.size(); l++) {
					// If the card is on the table, push it onto the pile vector to be added later
					if (table[j].GetCard() == cardsOfSet[l].GetCard()) {

						pile.push_back(table[j]);
						removedTableCards.push_back(table[j]);

						// Special handling if the card is an ace or not
						if (cardsOfSet[l].GetNumber() == 'A') {
							aceAs1Count += CardNumber(cardsOfSet[l].GetNumber());
							aceAs14Count += 14;
						}
						else {
							aceAs1Count += CardNumber(cardsOfSet[l].GetNumber());
						}
						count++;
					}
				}
			}

			// If the set card's numbers add up to the capture card, then they can make the set
			if (aceAs1Count != CardNumber(playerHandCaptureCard.GetNumber()) && aceAs14Count != CardNumber(playerHandCaptureCard.GetNumber())) {
				cout << "Card numbers did not add up to what you were capturing with. Try again." << endl;
				return false;
			}
			aceAs1Count = 0;
			aceAs14Count = 0;
		}
		/*do {
			// First checking to make sure that if the cards they want a set with is on the table 
			for (size_t i = 0; i < table.size(); i++) {
				for (size_t j = 0; j < setCards.size(); j++) {

					// If the card is on the table, push it onto the pile vector to be added later
					if (table[i].GetCard() == setCards[j].GetCard()) {

						pile.push_back(table[i]);
						removedTableCards.push_back(table[i]);

						// Special handling if the card is an ace or not
						if (setCards[j].GetNumber() == 'A') {
							aceAs1Count += CardNumber(setCards[j].GetNumber());
							aceAs14Count += 14;
						}
						else {
							aceAs1Count += CardNumber(setCards[j].GetNumber());
						}
						count++;
					}
				}
			}

			// If the set card's numbers add up to the capture card, then they can make the set
			if (aceAs1Count != CardNumber(playerHandCaptureCard.GetNumber()) && aceAs14Count != CardNumber(playerHandCaptureCard.GetNumber())) {
				cout << "Card numbers did not add up to what you were capturing with. Try again." << endl;
				return false;
			}

			do {
				cout << "Do you want to capture another set? (y,n): ";
				cin >> userInput;
			} while (userInput != "y" && userInput != "n");
			if (userInput == "y") {
				aceAs1Count = 0;
				aceAs14Count = 0;
				setCards.pop_back();
				setCards.pop_back();
				setCards = player[currentPlayer]->MakeSet();
			}
		} while (userInput == "y");*/
	}

	// If the player wanted to build, then this function will check if it is possible based on
	// the information the user provided
	if (player[currentPlayer]->GetPlayerWantBuild() == 'y') {
		if (CheckIfPlayerCanCaptureBuild(playerHandCaptureCard, playerHand)) {
			canCapture = true;

			// Decrement the build counter since the player is capturing the build
			buildCounter--;
			// Resetting this variable so the player doesn't always want a build
			player[currentPlayer]->SetPlayerWantBuild('n');
		}
	}
	else {
		// Checking to see if there are any cards on the table that match the card the player wants to capture with the same value
		for (size_t i = 0; i < table.size(); i++) {
			if (CardNumber(table[i].GetNumber()) == number) {
				pile.push_back(table[i]);
				removedTableCards.push_back(table[i]);
				canCapture = true;
			}
		}

		// If everything is correct, add the cards and remove them properly
		if (canCapture == true) {
			player[currentPlayer]->RemoveCard(playerHandCaptureCard);
			RemoveTableCards(removedTableCards);
			// Setting the cards from the table that were captured into a variable in the player class
			// so they can be outputted that they were captured
			player[currentPlayer]->SetPrintTableCaptureCards(removedTableCards);

			player[currentPlayer]->AddToPile(pile);
		}
	}

	// Set lastCapture to whoever the current player is
	if (currentPlayer == 0) {
		lastCapture = "Human";
	}
	else {
		lastCapture = "Computer";
	}

	if (canCapture == false) {
		cout << "You can not capture any cards on the table with that capture card." << endl;
	}

	playTrue = canCapture;
	return canCapture;

}

/* *********************************************************************
Function Name: CheckIfPlayerCanCaptureBuild
Purpose: To check if the player is elegible to capture a build
Parameters:
playerHandCapturedCard, a card passed by value. It holds the card the player wants to capture with
playerHand, a vector of cards. It refers to the player's hand
Return Value: Whether the player can make a capture or not, a boolean value
Local Variables:
existingBuildCard, a card used to store the card the player wants to add to a build
tempPile, a vector of cards used to add the cards to a player's pile
Algorithm:
1) Get the card the player wants to capture with and the player's hand
2) Check and see if the player has any cards on the table to capture or any sets
Assistance Received: none
********************************************************************* */
bool Round::CheckIfPlayerCanCaptureBuild(Card playerHandCaptureCard, vector<Card> playerHand) {

	Card existingBuildCard = player[currentPlayer]->GetExistingBuildCard();
	vector<Card> tempPile;

	// Iterate through each of the builds on the table and check if any of them can be captured
	// based on the specifications the user entered in
	for (size_t i = 0; i < tableBuilds.size(); i++) {
		// If there was a build that can be successfully captured after checking if possible, move the cards
		// from the build element into player's pile, move the card used for capture to player pile, and 
		// erase this build
		if (tableBuilds[i].CanCaptureBuildOfCards(playerHandCaptureCard, existingBuildCard, playerHand)) {
			tempPile = tableBuilds[i].GetBuildOfCards();
			tempPile.push_back(playerHandCaptureCard);
			player[currentPlayer]->AddToPile(tempPile);

			player[currentPlayer]->RemovePlayerBuildCard(playerHandCaptureCard);
			tableBuilds.erase(tableBuilds.begin() + i);
			player[currentPlayer]->RemoveCard(playerHandCaptureCard);
			return true;
		}
	}

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

	// Iterating through the cards a player can not place down because the card is needed to complete a build
	for (size_t i = 0; i < player[currentPlayer]->GetPlayerBuildCards().size(); i++) {
		if (player[currentPlayer]->GetPlayerBuildCards()[i].GetCard() == player[currentPlayer]->GetPlayerCard().GetCard()) {
			cout << "You can not trail because this card is part of a build." << endl;
			return false;
		}
	}

	// Checking if the player is able to capture with a same value card
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

/* *********************************************************************
Function Name: SaveGame
Purpose: Saves all of the information needed to a text file
Parameters: None
Return Value: None
Local Variables:
outputFile, an output stream object, used for writing to an output file
tempBuild, a vector of cards, used to temporarily store a build
tempDeck, a vector of cards, used to temporarily store the remaining cards in the deck
Algorithm:
1) Call print pile from the player class
Assistance Received: none
********************************************************************* */
void Round::SaveGame() {
	ofstream outputFile;

	// Open the file
	outputFile.open("CasinoSaveFile.txt");

	// Save the round
	outputFile << "Round: " << currentRound << endl;

	// Save the information pertaining to the computer
	outputFile << "Computer: " << endl;
	outputFile << "\t Score: " << computerPoints << endl;
	outputFile << "\t Hand: ";

	for (size_t i = 0; i < player[1]->GetHand().size(); i++) {
		outputFile << player[1]->GetHand()[i].GetCard() << " ";
	}
	outputFile << endl;

	outputFile << "\t Pile: ";
	for (size_t i = 0; i < player[1]->GetPile().size(); i++) {
		outputFile << player[1]->GetPile()[i].GetCard() << " ";
	}
	outputFile << endl;

	// Save information pertaining to the human
	outputFile << "Human: " << endl;
	outputFile << "\t Score: " << humanPoints << endl;
	outputFile << "\t Hand: ";

	for (size_t i = 0; i < player[0]->GetHand().size(); i++) {
		outputFile << player[0]->GetHand()[i].GetCard() << " ";
	}
	outputFile << endl;

	outputFile << "\t Pile: ";
	for (size_t i = 0; i < player[0]->GetPile().size(); i++) {
		outputFile << player[0]->GetPile()[i].GetCard() << " ";
	}
	outputFile << endl;

	// save the table (builds and loose cards)
	outputFile << "Table: ";
	for (size_t i = 0; i < tableBuilds.size(); i++) {
		vector<Card> tempBuild = tableBuilds[i].GetBuildOfCards();
		for (size_t j = 0; j < tempBuild.size(); j++) {
			outputFile << tempBuild[j].GetCard() << " ";
		}
	}
	for (size_t i = 0; i < table.size(); i++) {
		outputFile << table[i].GetCard() << " ";
	}
	outputFile << endl;

	// Save the build owners
	outputFile << "Build Owner: " << endl;

	// Save the deck
	vector<Card> tempDeck = deckOfCards.GetDeck();
	outputFile << "Deck: ";
	for (size_t i = 0; i < tempDeck.size(); i++) {
		outputFile << tempDeck[i].GetCard() << " ";
	}
	outputFile << endl;

	// Save the current player
	if (currentPlayer == 0) {
		outputFile << "Next Player: " << "Human" << endl;
	}
	else if (currentPlayer == 1) {
		outputFile << "Next Player: " << "Computer" << endl;
	}
	
	outputFile.close();

	exit(1);
}

/* *********************************************************************
Function Name: LoadRound
Purpose: Load all of the appropriate information for a round to be picked up on
Parameters:
loadComputerHand, holds the computer's hand, a vector of cards
loadComputerPile, holds the computer's pile, a vector of cards
loadHumanHand, holds the human's hand, a vector of cards
loadHumanPile, holds the human's pile, a vector of cards
loadTable, holds the cards on the table, a vector of cards
loadBuils, holds any builds on the table, a vector of builds
loadDeck, holds the cards left in a deck, a vector of cards
loadNextPlayer, holds the player who plays next, a string
Return Value: None
Local Variables: None
Algorithm:
1) Set each of the different fields to what the data was passed in.
2) No error checking here as saved input files should always be properly formatted
Assistance Received: none
********************************************************************* */
void Round::LoadRound(vector<Card> loadComputerHand, vector<Card> loadComputerPile, vector<Card> loadHumanHand,
	vector<Card> loadHumanPile, vector<Card> loadTable, vector<Build> loadBuilds, vector<Card> loadDeck) {

	// Load in computer's attributes
	player[1]->SetHand(loadComputerHand);
	player[1]->SetPile(loadComputerPile);

	// Load in player's attributes
	player[0]->SetHand(loadHumanHand);
	player[0]->SetPile(loadHumanPile);

	// Load in the table
	table = loadTable;

	// Load in the builds
	tableBuilds = loadBuilds;

	// Load in the deck
	deck = loadDeck;

	loadGame = true;
}