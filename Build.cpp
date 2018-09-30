#include "Build.h"



Build::Build()
{
}


Build::~Build()
{
}


/* *********************************************************************
Function Name: SetOwner
Purpose: To set the owner of a build
Parameters:
passedOwner, an integer passed by value. It holds the passed in owner of a build
Return Value: Void
Local Variables: None
Algorithm:
1) Check and make sure the passed in owner is either 0 or 1
2) Set the owner to be what was passed in
Assistance Received: none
********************************************************************* */
void Build::SetOwner(int passedOwner) {
	if (passedOwner == 0 || passedOwner == 1) {
		owner = passedOwner;
	}
	else {
		cout << "Error in setting the owner of a build in the build class." << endl;
	}
}

/* *********************************************************************
Function Name: GetOwner
Purpose: To retrieve the owner of a specific build
Parameters: None
Return Value: The owner of a build, a constant integer value
Local Variables: None
Algorithm:
1) Return the owner
Assistance Received: none
********************************************************************* */
int Build::GetOwner() const {
	return owner;
}

/* *********************************************************************
Function Name: SetBuildOfCards
Purpose: Set the vector of cards of a build
Parameters:
buildCards, an vector of cards passed by value. It holds the cards to be made of a build
Return Value: Void
Local Variables: None
Algorithm:
1) Set the buildOfCards to be the set passed in
Assistance Received: none
********************************************************************* */
void Build::SetBuildOfCards(vector<Card> buildCards) {
	for (size_t i = 0; i < buildCards.size(); i++) {
		if (buildCards[i].GetCard().size() == 2) {
			buildOfCards.push_back(buildCards[i]);
		}
		else {
			cerr << "Error in added a card to the build vector in the build.cpp" << endl;
		}
	}
}

/* *********************************************************************
Function Name: GetBuildOfCards
Purpose: To retrieve a build of cards
Parameters: None
Return Value: The vector of cards that make up a build, a vector of cards value
Local Variables: None
Algorithm:
1) Return the buildOfCards
Assistance Received: none
********************************************************************* */
vector<Card> Build::GetBuildOfCards() const {
	return buildOfCards;
}

/* *********************************************************************
Function Name: PrintBuild
Purpose: To print out a build
Parameters: None
Return Value: Void
Local Variables: None
Algorithm:
1) Iterate through and print each card of a build
Assistance Received: none
********************************************************************* */
void Build::PrintBuild() {

	cout << " [ ";
	for (size_t i = 0; i < buildOfCards.size(); i++) {
		cout << buildOfCards[i].GetCard() << " ";
	}
	cout << "] ";
}

/* *********************************************************************
Function Name: CheckAndAddCardInBuild
Purpose: To verify if a card can be added to a build and add it if possible
Parameters:
card, an card passed by value. It holds the card to be added
currentPlayer, an integer. It holds the current player that is playing
playerHand, a vector of cards. It holds the hand of a player
Return Value: True if the card can be added, false otherwise, a boolean value
Local Variables:
cardInBuild, a boolean used to track if a card is in a build or not
tempBuild, a vector of cards used to see what it would be like if a card was added to it
aceAs1, an integer to count numbers as if ace was 1
aceAs14, an integer to count numbers as if ace was 14
Algorithm:
1) Check and see if the card the build they want to add to exists in this build
2) If it is and the current player isnt the owner of the build, then try to add the card
3) If the player has a card in their hand that equals what the value will be after added the card
4) Add the card to the build
5) Set the owner of the build to the current player
Assistance Received: none
********************************************************************* */
bool Build::CheckAndAddCardInBuild(Card cardToBeAdded, Card cardInBuild, int currentPlayer, vector<Card> playerHand) {
	bool isCardInBuild = false;
	vector<Card> tempBuild = buildOfCards;
	int aceAs1 = 0;
	int aceAs14 = 0;
	for (size_t i = 0; i < buildOfCards.size(); i++) {
		if (buildOfCards[i].GetCard() == cardInBuild.GetCard()) {
			isCardInBuild = true;
		}
	}

	// If the card the user wants to add to a build exists and they are not the owner...
	if (isCardInBuild = true && owner != currentPlayer) {
		// Push the card the player wants to add to the build onto a temporary copy of the build to 
		// be added if the numbers correctly add up to a card in their hand
		tempBuild.push_back(cardToBeAdded);

		// Iterate through the build with the card added and see what number it adds up to
		for (size_t i = 0; i < tempBuild.size(); i++) {
			if (tempBuild[i].GetNumber() != 'A') {
				aceAs1 += CardNumber(tempBuild[i].GetNumber());
				aceAs14 += CardNumber(tempBuild[i].GetNumber());
			}
			else {
				aceAs1++;
				aceAs14 += 14;
			}
		}
		// Then iterate through the players hand and check and see with the card they want to add being added,
		// Does it equal one of the cards in their hand
		for (size_t i = 0; i < playerHand.size(); i++) {
			// If it does equal, update the build with the added card and return true
			if (CardNumber(playerHand[i].GetNumber()) == aceAs1 || CardNumber(playerHand[i].GetNumber()) == aceAs14 ||
				playerHand[i].GetNumber() == 'A' && aceAs1 == 14) {
				buildOfCards = tempBuild;
				owner = currentPlayer;

				if (playerHand[i].GetNumber() != 'A') {
					cardValueOfBuild = CardNumber(playerHand[i].GetNumber());
				}
				else {
					cardValueOfBuild = 14;
				}

				return true;
			}
		}

		// If we get out of the for loop then that means that it never added up to a card in the player's hand
		cout << "You do not have a card that adds up to the build you are trying to make." << endl;
		return false;

	}
	else {
		cout << "You can not add to that existing build." << endl;
		return false;
	}
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
int Build::CardNumber(char number) {

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
Function Name: CanCaptureBuildOfCards
Purpose: To verify if a player can capture a build
Parameters:
cardToBeCaptured, a card passed by value. It holds the card that will capture the build
cardInBuild, a card passed by value. It holds the card that is in the build already
playerHand, a vector of cards. It holds the hand of a player
Return Value: True if the build can be captured, false otherwise, a boolean value
Local Variables:
isCardInBuild, a boolean used to track if a card is in a build or not
captureCardNum, an int to represent the value of the card the player is capturing with
captureCardAce, an int to represent the value of an ace if the player is capturing with one
Algorithm:
1) Check and see if the build they want to capture exists
2) If it is and the player is capturing with a card equivalent to the value of the build, then return true
Assistance Received: none
********************************************************************* */
bool Build::CanCaptureBuildOfCards(Card cardToBeCaptured, Card cardInBuild, vector<Card> playerHand) {
	bool isCardInBuild = false;
	int captureCardNum = CardNumber(cardToBeCaptured.GetNumber());
	int captureCardAce = 14;

	// First checking to see if the build the user wants to capture exists by looking for the card they provided
	for (size_t i = 0; i < buildOfCards.size(); i++) {
		if (buildOfCards[i].GetCard() == cardInBuild.GetCard()) {
			isCardInBuild = true;
		}
	}

	// If the card the user typed in is in the build and the card the user
	// wants to capture with is not an ace, then we need to make sure the card they are
	// capturing with is the same value as the total build
	if (isCardInBuild && cardToBeCaptured.GetNumber() != 'A') {
		if (CardNumber(cardToBeCaptured.GetNumber()) == cardValueOfBuild) {
			return true;
		}
	}
	// If the card is in the build and the card is an ace, then we treat the capturing
	// card as 14 and see if it matches the total build value
	else if (isCardInBuild && cardToBeCaptured.GetNumber() == 'A') {
		if (captureCardAce == cardValueOfBuild) {
			return true;
		}
	}
	return false;
}

/* *********************************************************************
Function Name: SetValueOfBuild
Purpose: To set the numeric value of a build (what it adds up to)
Parameters:
value, an int passed by value. It holds the value of the build
Return Value: Void
Local Variables: None
Algorithm:
1) If the value is greater than 0 and less than 15
2) Set the value of the build to what was passed in
Assistance Received: none
********************************************************************* */
void Build::SetValueOfBuild(int value) {

	// Value must be greater than 0 and less than 15 to remain in the size of a build
	if (value > 0 && value < 15) {
		cardValueOfBuild = value;
	}
	else {
		cerr << "Error in setting the value of a build in the build class." << endl;
	}
}

/* *********************************************************************
Function Name: GetValueOfBuild
Purpose: To retrieve the added up value of a build
Parameters: None
Return Value: Void
Local Variables: None
Algorithm:
1) Return the value of the build
Assistance Received: none
********************************************************************* */
int Build::GetValueOfBuild() const {
	return cardValueOfBuild;
}

/* *********************************************************************
Function Name: SetCaptureCardOfBuild
Purpose: To set the card that will be used to capture the build
Parameters:
card, a card ojbect passed by value, the card that will be used to capture a build
Return Value: Void
Local Variables: None
Algorithm:
1) Check to make sure the card has an actual number value
2) If it does, set the value
3) Otherwise, print out an error message
Assistance Received: none
********************************************************************* */
void Build::SetCaptureCardOfBuild(Card card) {
	
	// If the card is an actual card being passed in, then set the value
	for (size_t i = 0; i < uniqueCards.size(); i++) {
		if (uniqueCards[i].GetCard() == card.GetCard()) {
			captureCardOfBuild = card;
		}
	}
	if (true) {
		captureCardOfBuild = card;
	}
	else {
		cerr << "Error in setting the capture card in the build class." << endl;
	}
}

/* *********************************************************************
Function Name: GetCaptureCardOfBuild
Purpose: To retrieve the card that
Parameters: None
Return Value: the card that can capture a build, a card object
Local Variables: None
Algorithm:
1) Return the capture card of a build
Assistance Received: none
********************************************************************* */
Card Build::GetCaptureCardOfBuild() const {
	return captureCardOfBuild;
}