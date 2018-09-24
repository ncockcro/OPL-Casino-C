#include "Player.h"


// Default constructor
Player::Player()
{
	playerWantSave = false;
}

// Default destructor
Player::~Player()
{
}

/* *********************************************************************
Function Name: MakeMove
Purpose: For each player to make a move in a round
Parameters: None
Return Value: Void
Local Variables: None
Algorithm:
1) This is a virtual function so the actualfunction is used in the child classes
Assistance Received: none
********************************************************************* */
void Player::MakeMove(bool falseMove, vector<Card> table, vector<Build> buildTable) {
}

/* *********************************************************************
Function Name: SetHand
Purpose: At the beginning of a round and when the players run out of cards, this function deals four cards to them
Parameters:
fourCards, a vector of cards passed by value. It holds the four cards to be added to a players hand
Return Value: Void
Local Variables: None
Algorithm:
1) Go through the deck of 52 cards and the four cards passed in
2) If the cards that were passed in match any of the cards in the deck, the card will be pushed to the players hand
Assistance Received: none
********************************************************************* */
void Player::SetHand(vector<Card> fourCards) {

		hand.push_back(fourCards[0]);
		hand.push_back(fourCards[1]);
		hand.push_back(fourCards[2]);
		hand.push_back(fourCards[3]);

}

/* *********************************************************************
Function Name: IsEmpty
Purpose: To check if a player's hand is empty
Parameters: None
Return Value: Returns true if the player's hand is empty, false otherwise, a boolean value
Local Variables: None
Algorithm:
1) If the hand vector is empty, return true
2) Otherwise, return false
Assistance Received: none
********************************************************************* */
bool Player::IsEmpty() {

	if (hand.empty()) {
		return true;
	}
	else {
		return false;
	}
}

/* *********************************************************************
Function Name: GetHand
Purpose: Return a player's hand
Parameters: None
Return Value: The player's hand, a constant vector of cards value
Local Variables: None
Algorithm:
1) Return the player's hand
Assistance Received: none
********************************************************************* */
vector<Card> Player::GetHand() const {
	return hand;
}

/* *********************************************************************
Function Name: GetPlayerCard
Purpose: To return the card the player want to use for either a build or capture
Parameters: None
Return Value: The player's card for a build or capture, a constant card value
Local Variables: None
Algorithm:
1) Return the player's card for a build or capture
Assistance Received: none
********************************************************************* */
Card Player::GetPlayerCard() const {
	return playerCard;
}

/* *********************************************************************
Function Name: GetBuildCards
Purpose: To retrieve the cards a player wants to use for a build
Parameters: None
Return Value: The build cards, a vector of cards value
Local Variables: None
Algorithm:
1) Return the cards used for a build
Assistance Received: none
********************************************************************* */
vector<Card> Player::GetBuildCards() const {
	return buildCards;
}

/* *********************************************************************
Function Name: GetNewOrExistingBuild
Purpose: To retrieve the indicator if the user wants to make a new or add to existing build
Parameters: None
Return Value: The string indicating new or existing build, a char value
Local Variables: None
Algorithm:
1) Return the char indicating a new or existing build
Assistance Received: none
********************************************************************* */
char Player::GetNewOrExistingBuild() const {
	return newOrExistingBuild;
}

/* *********************************************************************
Function Name: GetExistingBuildCard
Purpose: To retrieve the card of a build the human wants to add to
Parameters: None
Return Value: The card from an existing build, a card value
Local Variables: None
Algorithm:
1) Return the card of an existing build
Assistance Received: none
********************************************************************* */
Card Player::GetExistingBuildCard() const {
	return existingBuildCard;
}

/* *********************************************************************
Function Name: GetPlayerMove
Purpose: To retrieve the move that the player wants to make (build, capture, or trail
Parameters: None
Return Value: The character of the move the player want to make, a char value
Local Variables: None
Algorithm:
1) Return the playerMove variable
Assistance Received: none
********************************************************************* */
char Player::GetPlayerMove() const {
	return playerMove;
}

/* *********************************************************************
Function Name: RemoveCard
Purpose: To remove a specific card from a player's hand
Parameters:
card, a card passed by value. It holds the card to be removed
Return Value: The average grade in the class, a real value
Local Variables: None
Algorithm:
1) Iterate through a player's hand and if the card passed in matches with one of the cards
2) Remove the card
Assistance Received: none
********************************************************************* */
void Player::RemoveCard(Card card) {
	bool notFound = false;
	for (size_t i = 0; i < hand.size(); i++) {
		if (hand[i].GetCard() == card.GetCard()) {
			hand.erase(hand.begin() + i);
			notFound = true;
		}
	}

	if (notFound == false) {
		cerr << "Error in removing a card in the player class." << endl;
	}
}

/* *********************************************************************
Function Name: SetPile
Purpose: Given a pile of cards, set that to a player
Parameters:
passedPile, a vector of cards passed by value. It holds the cards to be set to the pile
size, an integer. It refers to the number of students in the class
Return Value: Void
Local Variables:
count, an integer used for tracking if all the cards in a pile are actual cards in a deck
Algorithm:
1) Iterate through all 52 cards in a deck and the cards in the passed pile
2) If there is a match, increment the counter
3) If the count in the end matches the size of the passed cards, then set the pile equal to the passed pile
Assistance Received: none
********************************************************************* */
void Player::SetPile(vector<Card> passedPile) {
	int count = 0;
	for (size_t i = 0; i < uniqueCards.size(); i++) {
		for (size_t j = 0; j < passedPile.size(); j++) {
			if (uniqueCards[i].GetCard() == passedPile[j].GetCard()) {
				count++;
			}
		}
	}

	if (count == passedPile.size()) {
		pile = passedPile;
	}
}

/* *********************************************************************
Function Name: AddToPile
Purpose: To add a certain amount of cards to a player's pile
Parameters:
passedPile, a vector of cards passed by value. It holds the pile to be added to a player's existing pile
Return Value: Void
Local Variables: None
Algorithm:
1) Iterate through the 52 cards deck and through the passed in pile
2) If there is a match, add the card to the existing pile
Assistance Received: none
********************************************************************* */
void Player::AddToPile(vector<Card> passedPile) {
	
	for (size_t i = 0; i < uniqueCards.size(); i++) {
		for (size_t j = 0; j < passedPile.size(); j++) {
			if (uniqueCards[i].GetCard() == passedPile[j].GetCard()) {
				pile.push_back(passedPile[j]);
			}
		}
	}
}

/* *********************************************************************
Function Name: GetPile
Purpose: To retrieve a player's pile
Parameters: None
Return Value: The pile of a players pile, a constant vector of cards value
Local Variables: None
Algorithm:
1) Returns a player's pile
Assistance Received: none
********************************************************************* */
vector<Card> Player::GetPile() const {
	return pile;
}

/* *********************************************************************
Function Name: AddToPlayerBuildCards
Purpose: To add a card to the list of build cards a player must put down at some point to
complete a build
Parameters: A build card to be added to the vector, a card type
Return Value: Void
Local Variables: None
Algorithm:
1) Cycle through and ensure the card passed in is a valid card
2) Push the card to the back of the vector of build cards
Assistance Received: none
********************************************************************* */
void Player::AddToPlayerBuildCards(Card buildCard) {
	for (size_t i = 0; i < uniqueCards.size(); i++) {
		if (buildCard.GetCard() == uniqueCards[i].GetCard()) {
			playerBuildCards.push_back(buildCard);
		}
	}
}

/* *********************************************************************
Function Name: GetPlayerBuildCards
Purpose: To retrieve the cards the player must use for a build
Parameters: None
Return Value: the vector of cards the player must use to build, a vector of cards
Local Variables: None
Algorithm:
1) Return the vector of cards the player must build with
Assistance Received: none
********************************************************************* */
vector<Card> Player::GetPlayerBuildCards() const {
	return playerBuildCards;
}

/* *********************************************************************
Function Name: PrintPile
Purpose: To print out a player's pile to the console
Parameters: None
Return Value: Void
Local Variables: None
Algorithm:
1) Iterate through a player's pile and print each card to the screen
Assistance Received: none
********************************************************************* */
void Player::PrintPile() {
	for (size_t i = 0; i < pile.size(); i++) {
		cout << pile[i].GetCard() << " ";
	}
	cout << endl;
}

/* *********************************************************************
Function Name: GetPlayerWantBuild
Purpose: To retrieve the character indicating if a player wants to capture a set or not
Parameters: None
Return Value: The character either being 'y' or 'n', a constant char value
Local Variables: None
Algorithm:
1) Return the playerWantBuild variable
Assistance Received: none
********************************************************************* */
char Player::GetPlayerWantBuild() const {
	return playerWantBuild;
}

/* *********************************************************************
Function Name: SetPlayerWantBuild
Purpose: To retrieve the character indicating if a player wants to capture a set or not
Parameters:
choice, a char variable, used for holding the choice if a player wants to build or not
Return Value: The character either being 'y' or 'n', a constant char value
Local Variables: None
Algorithm:
1) Check if the choice variable passed in is either a 'y' or 'n'
Assistance Received: none
********************************************************************* */
void Player::SetPlayerWantBuild(char choice) {
	if (tolower(choice) == 'y' || tolower(choice) == 'n') {
		playerWantBuild = choice;
	}
	else {
		cerr << "Error in setting the player want build in player class." << endl;
	}
}

/* *********************************************************************
Function Name: GetPlayerWantSet
Purpose: To retrieve the character indicating if a player wants to make a set or not
Parameters: None
Return Value: The character either being 'y' or 'n', a constant char value
Local Variables: None
Algorithm:
1) Return the playerWantSet variable
Assistance Received: none
********************************************************************* */
char Player::GetPlayerWantSet() const {
	return playerWantSet;
}

/* *********************************************************************
Function Name: GetPlayerSetCards
Purpose: To retrieve the cards the player wants to use for a set
Parameters: None
Return Value: The cards used for a set, a vector of cards value
Local Variables: None
Algorithm:
1) Return the playerSetCards variable
Assistance Received: none
********************************************************************* */
vector<Card> Player::GetPlayerSetCards() const {
	return playerSetCards;
}

/* *********************************************************************
Function Name: GetPlayerOfSetCards
Purpose: To retrieve the cards the player wants to use for a set
Parameters: None
Return Value: The sets the player wants to capture, a vector of sets value
Local Variables: None
Algorithm:
1) Return the playerOfSetCards variable
Assistance Received: none
********************************************************************* */
vector<Set> Player::GetPlayerOfSetCards() const {
	return playerOfSetCards;
}

/* *********************************************************************
Function Name: GetPlayerWantSave
Purpose: To retrieve the bool indicating if the player wants to save or not
Parameters: None
Return Value: The bool either being true or false, a constant boolean value
Local Variables: None
Algorithm:
1) Return the playerWantSave variable
Assistance Received: none
********************************************************************* */
bool Player::GetPlayerWantSave() const {
	return playerWantSave;
}

/* *********************************************************************
Function Name: MakeSet
Purpose: Has the user enter more kids for capturing a set
Parameters: None
Return Value: The cards being used for a set, a vector of cards value
Local Variables:
userInput, an string used to get user input
count, an int for keeping track of how many cards they entered
Algorithm:
1) Prompt the user to enter two cards used for a set
2) Return the value to be used in another function
Assistance Received: none
********************************************************************* */
vector<Card> Player::MakeSet() {
	string userInput;
	int count = 0;

	do {
		cout << "Enter the two cards that make up a set for you to capture (Type a card and hit enter): ";
		cin >> userInput;

		if (CheckCard(userInput)) {
			playerSetCards.push_back(Card());
			playerSetCards[count].SetCard(userInput);
			count++;
		}

	} while (count < 2);

	return playerSetCards;
}

/* *********************************************************************
Function Name: CheckCard
Purpose: Takes a card in as input and checks to see if it is one of the 52 in a deck
Parameters: None
Return Value: True if the card is valid, false otherwise, a boolean value
Local Variables: None
Algorithm:
1) Iterate through the 52 card deck and see if the passed in card matches one of them
2) If it does, return true, otherwise, return false
Assistance Received: none
********************************************************************* */
bool Player::CheckCard(string card) {

	for (size_t i = 0; i < uniqueCards.size(); i++) {
		if (uniqueCards[i].GetCard() == card) {
			return true;
		}
	}

	cout << "You don't have that card, enter a different one." << endl;
	return false;
}

/* *********************************************************************
Function Name: AICheckForBuild
Purpose: Check if there is a build for a player's hand and suggest what to do
Parameters:
playerHand, an vector of cards passed by value. It holds a player's hand
Return Value: If the computer can build or not, a boolean value
Local Variables: None
Algorithm:
1) WORK IN PROGRESS
Assistance Received: none
********************************************************************* */
bool Player::AICheckForBuild(vector<Card> playerHand, vector<Card> table, vector<Build> buildTable) {



	// ****** For creating a new build ******
	int handCardNumber;
	// Cycling through the computer's hand and checking if there are cards that add up to that card
	for (size_t i = 0; i < playerHand.size(); i++) {
		handCardNumber = CardNumber(playerHand[i].GetNumber());

		// Now cycling through the computers hand and table, looking for a combination of a card from the hand and a card on
		// the table that will add up to another card in the player's hand
		for (size_t j = 0; j < playerHand.size(); j++) {
			// Skipping over the same exact computer card from the first for loop
			if (playerHand[i].GetCard() == playerHand[j].GetCard()) {
				continue;
			}
			for (size_t k = 0; k < table.size(); k++) {
				if ((CardNumber(playerHand[j].GetNumber()) + CardNumber(table[k].GetNumber())) == handCardNumber) {
					newOrExistingBuild = 'n';
					playerCard = playerHand[j];
					buildCards.push_back(table[k]);
					return true;
				}
			}
		}
	}
	return false;
}
bool Player::AICheckForCapture(vector<Card> playerHand, vector<Card> table, vector<Build> buildTable) {

	vector<Card> currentBuild;
	int count = 0;
	bool isCapturing = false;

	// Checking to see if any builds can be captured

	// First we need to cycle through each of the builds on the table
	for (size_t i = 0; i < buildTable.size(); i++) {
		currentBuild = buildTable[i].GetBuildOfCards();

		// Then cycle through all of the cards in a specific build and add up the value of the cards
		for (size_t j = 0; j < currentBuild.size(); j++) {
			count += CardNumber(currentBuild[j].GetNumber());
		}

		// Now we must go through the player's hand and see if any of the cards equal the sum of the build
		// If so, this function will return true and the build will be captured
		for (size_t j = 0; j < playerHand.size(); j++) {

			// Capturing the build with an ace
			if (playerHand[i].GetNumber() == 'A' && count == 14) {
				playerWantBuild = 'y';
				playerCard = playerHand[j];
				existingBuildCard = currentBuild[j];
				return true;
			}

			// Capturing the build with any other card
			if (CardNumber(playerHand[j].GetNumber()) == count) {
				playerWantBuild = 'y';
				playerCard = playerHand[j];
				existingBuildCard = currentBuild[j];
				return true;
			}
		}
	}

	// If there were no builds to capture, then we will check for any loose cards to capture
	// First cycling through the table
	for (size_t i = 0; i < table.size(); i++) {

		// Then through the player's hand
		for (size_t j = 0; j < playerHand.size(); j++) {

			// If any of them have the same card number value, the computer can capture the card
			if (CardNumber(playerHand[j].GetNumber()) == CardNumber(table[i].GetNumber())) {
				playerCard = playerHand[j];
				isCapturing = true;
			}
		}
	}

	// **** Set Checking ****
	vector<Card> tempCards;
	vector<Card> setOfCards;
	Set tempSet;
	bool canCapture = true;

	// If the computer is capturing, maybe there are some sets to be captured aswell
	if (isCapturing) {

		// Next two for loops go through the table and we are looking for combinations of cards on the table
		// that add up to the card the computer is capturing with
		for (size_t i = 0; i < table.size(); i++) {
			for (size_t j = 0; j < table.size(); j++) {

				// If the card the player is capturing with is an ace, then we need to look for sets that add up to 14
				if (playerCard.GetNumber() == 'A' && CardNumber(table[i].GetNumber()) + CardNumber(table[j].GetNumber()) == 14) {
					tempCards.push_back(table[j]);
					tempCards.push_back(table[i]);
					// Before adding the cards to a set, we need to check if they were already placed in a set prior
					// This for loop will cycle through each of the prior sets
					for (size_t l = 0; l < playerOfSetCards.size(); l++) {
						setOfCards = playerOfSetCards[l].GetCardsOfSet();
						
						// This for loop will cycle through a specific set of cards and determine if the cards
						// were used in a set prior
						for (size_t m = 0; m < setOfCards.size(); m++) {
							if (setOfCards[m].GetCard() == tempCards[m].GetCard()) {
								canCapture = false;
							}
						}
					}
					tempCards.clear();
					// If the cards are not already in the set vector, then add them to it
					if (canCapture) {
						// If the cards are not already in the set vector, then add them to it
						playerWantSet = 'y';
						tempCards.push_back(table[i]);
						tempCards.push_back(table[j]);

						// Then push these cards onto a set object and them to the vector of sets
						tempSet.SetCardsOfSet(tempCards);
						playerOfSetCards.push_back(tempSet);
						tempCards.clear();
					}

				}
				// Otherwise, were are just looking for any set that adds up to the card the player chose
				if (CardNumber(table[i].GetNumber()) + CardNumber(table[j].GetNumber()) == CardNumber(playerCard.GetNumber())) {
					tempCards.push_back(table[j]);
					tempCards.push_back(table[i]);
					// Before adding the cards to a set, we need to check if they were already placed in a set prior
					// This for loop will cycle through each of the prior sets
					for (size_t l = 0; l < playerOfSetCards.size(); l++) {
						setOfCards = playerOfSetCards[l].GetCardsOfSet();

						// This for loop will cycle through a specific set of cards and determine if the cards
						// were used in a set prior
						for (size_t m = 0; m < setOfCards.size(); m++) {
							if (setOfCards[m].GetCard() == tempCards[m].GetCard()) {
								canCapture = false;
							}
						}
					}
					tempCards.clear();

					// If the cards are not already in the set vector, then add them to it
					if (canCapture) {
						// Set playerWantSet to yes so it will be checked in the round class
						playerWantSet = 'y';
						tempCards.push_back(table[i]);
						tempCards.push_back(table[j]);

						// Then push these cards onto a set object and them to the vector of sets
						tempSet.SetCardsOfSet(tempCards);
						playerOfSetCards.push_back(tempSet);
						tempCards.clear();
					}
				}
			}
		}
	}
	return isCapturing;
}

/* *********************************************************************
Function Name: AIMakeTrail
Purpose: To pick the lowest card the computer has and trail
Parameters:
playerHand, a vector of cards passed by value. It holds the player's cards
Return Value: Void
Local Variables:
lowestCard, a card object used to hold the lowest valued card in a player hand
Algorithm:
1) Cycle through a player's hand and find which card has the lowest value
2) Add it to the playerCard and trail with it so maybe it can be incorporated into a build
Assistance Received: none
********************************************************************* */
void Player::AIMakeTrail(vector<Card> playerHand) {

	Card lowestCard;
	lowestCard.SetCard("CK");
	for (size_t i = 0; i < playerHand.size(); i++) {
		if (CardNumber(playerHand[i].GetNumber()) <= CardNumber(lowestCard.GetNumber())) {
			lowestCard = playerHand[i];
		}
	}

	playerCard = lowestCard;
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
int Player::CardNumber(char number) {

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
		cerr << "Error in the card number in the computer class. Returning -1." << endl;
		return -1;
	}
}