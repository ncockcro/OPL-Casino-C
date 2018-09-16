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

	do {
		cout << "Type 'b' to build, 'c' to capture, or 't' to trail: ";
		cin >> userInput;
	} while (tolower(userInput[0]) != 'b' && tolower(userInput[0]) != 'c' && tolower(userInput[0]) != 't');

	// Saving the players move
	playerMove = userInput[0];

	if (tolower(userInput[0]) == 'b') {
 		MakeBuild();
	}
	else if (tolower(userInput[0]) == 'c') {
		MakeCapture();
	}
	else if (tolower(userInput[0]) == 't') {
		MakeTrail();
	}
	else {
		cout << "Error in making a move by the player." << endl;
	}
}

// If the player chooses to make a build, this function will get the user input from the for what card they want
// To use and validates if they have that card.
void Human::MakeBuild() {

	string userInput;
	bool hasCard = false;
	buildCards.clear();


	// Prompts the user for a card they would like to build
	do {
		cout << "Enter the card that you have and want to use for a build: ";
		cin >> userInput;
	} while (!CheckCard(userInput));

	// Go through the human's cards and see if they have the card they just entered
	for (size_t i = 0; i < hand.size(); i++) {
		if (userInput == hand[i].GetCard()) {
			hasCard = true;
			playerCard.SetCard(userInput);
		}
	}

	// If they didn't have the card, this function will call itself again
	if (hasCard == false) {
		cout << "You do not have that card, enter a different one" << endl;
		MakeBuild();
	}

	int count = 0;

	// Have a loop go through and ask the user for how many cards they would like to build with
	do {
		cout << "Enter the card(s) you want to build with, press 'enter' after each card('p' to stop): ";
		cin >> userInput;

		// If they typed in the correct input, 
		if (CheckCard(userInput)) {
			buildCards.push_back(Card());
			buildCards[count].SetCard(userInput);
			count++;
		}
		else if (tolower(userInput[0]) != 'p') {
			cout << "**** Incorrect input, disreguarding. ****" << endl;
		}

	} while (tolower(userInput[0]) != 'p');

}

void Human::MakeCapture() {

	string userInput;
	bool hasCard = false;


	// Prompts the user for a card they would like to build
	do {
		cout << "Enter the card that you have and want to use for a capture: ";
		cin >> userInput;
	} while (!CheckCard(userInput));

	// Go through the human's cards and see if they have the card they just entered
	for (size_t i = 0; i < hand.size(); i++) {
		if (userInput == hand[i].GetCard()) {
			hasCard = true;
			playerCard.SetCard(userInput);
		}
	}

	// If they didn't have the card, this function will call itself again
	if (hasCard == false) {
		cout << "You do not have that card, enter a different one" << endl;
		MakeCapture();
	}

	do {
		cout << "Are there any sets you would like to capture? (y, n): ";
		cin >> userInput;
	} while (tolower(userInput[0]) != 'y' && tolower(userInput[0]) != 'n');

	playerWantSet = userInput[0];


}

void Human::MakeTrail() {
	string userInput;
	bool validCard = false;

	// Prompts the user for a card they would like to build
	do {
		cout << "Enter the card that you have and want to use for a trail: ";
		cin >> userInput;

		for (size_t i = 0; i < hand.size(); i++) {
			if (userInput == hand[i].GetCard()) {
				validCard = true;
			}
		}

	} while (!validCard);

	playerCard.SetCard(userInput);
}