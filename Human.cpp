#include "Human.h"



Human::Human()
{
}


Human::~Human()
{
}

// Exclusive details for when the human is making a move.
void Human::MakeMove() {
	string userInput;
	cout << "Human making move." << endl;

	do {
		cout << "Type 'b' to build, 'c' to capture, or 't' to trail: ";
		cin >> userInput;
	} while (tolower(userInput[0]) != 'b' && tolower(userInput[0]) != 'c' && tolower(userInput[0]) != 't');

	if (tolower(userInput[0]) == 'b') {
		MakeBuild();
	}
	else if (tolower(userInput[0]) == 'c') {
		// Call capture function for input
	}
	else if (tolower(userInput[0]) == 't') {
		// Call trail function for input
	}
	else {
		cout << "Error in making a move by the player." << endl;
	}
	hand.pop_back();
	hand.pop_back();
	hand.pop_back();
	hand.pop_back();
}

// If the player chooses to make a build, this function will get the user input from the for what card they want
// To use and validates if they have that card.
void Human::MakeBuild() {
	
	string playerCard;
	bool hasCard = false;

	// Prompts the user for a card they would like to build
	cout << "Type 'p' if you would like to go to the previous screen." << endl;
	cout << "Enter the card that you have and want to use for a build: ";
	cin >> playerCard;

	// Takes the user back to the previous function so they can either build, capture, or trail
	if (tolower(playerCard[0]) == 'p') {
		MakeMove();
	}

	// Go through the human's cards and see if they have the card they just entered
	for (int i = 0; i < hand.size(); i++) {
		if (playerCard == hand[i].GetCard()) {
			hasCard = true;
		}
	}

	// If they didn't have the card, this function will call itself again
	if (hasCard == false) {
		MakeBuild();
	}

	vector<string> buildCards;

	// WORKING HERE ON HAVING THE USER ENTER THE CARDS THEY WANT TO BUILD
	cout << "Enter the card(s) you want to build with, press 'enter' after each card('p' to stop): ";

}