#include "Human.h"



Human::Human()
{
}


Human::~Human()
{
}

/* *********************************************************************
Function Name: MakeMove
Purpose: Prompts the user for what kind of move they want to make
Parameters: None
Return Value: Void
Local Variables:
userInput, an string used to get user input
Algorithm:
1) Prompt the user to enter what they want to do
2) Depending on what the user picked, another function will be called for each type of play
Assistance Received: none
********************************************************************* */
void Human::MakeMove(vector<Card> table, vector<Build> buildTable) {
	string userInput;

	printTableBuildCards.clear();
	printTableCaptureCards.clear();

	do {
		cout << "1.) Save the game" << endl;
		cout << "2.) Make a move" << endl;
		cout << "3.) Ask for help" << endl;
		cout << "4.) Quit the game: ";
		cin >> userInput;

		if (userInput != "1" && userInput != "2" && userInput != "3" && userInput != "4") {
			cout << endl;
			cout << "Incorrect menu option." << endl;
			cout << endl;
		}
	} while (userInput != "1" && userInput != "2" && userInput != "3" && userInput != "4");

	// Save game
	if (userInput == "1") {
		playerWantSave = true;
	}

	// Build, capture, or trail
	else if (userInput == "2") {
		MakePlay();
	}

	// Use the computer's AI for help
	else if (userInput == "3") {
		playerMove = 'h';
		AskForHelp(table, buildTable);
	}

	// Quit the game
	else if (userInput == "4") {
		exit(1);
	}
}

/* *********************************************************************
Function Name: PrintMove
Purpose: Outputs a description of what kind of move the player just did
Parameters: None
Return Value: Void
Local Variables:
userInput, an string used to get user input
Algorithm:
1) Prompt the user to enter a type of move to make
2) Depending on what the user picked, another function will be called for each type of move
Assistance Received: none
********************************************************************* */
void Human::PrintMove() {
	if (playerMove == 'b') {
		cout << "The player chose to play a " << playerCard.GetNumber() << " of ";
		cout << GetSuitName(playerCard.GetSuit()) << endl;

		// Building onto a new build
		if (tolower(newOrExistingBuild) == 'n') {
			cout << "to make a new build with the ";
			
			// Cycling through the cards in the build that was made
			for (size_t i = 0; i < printTableBuildCards.size(); i++) {

				if (printTableBuildCards[i].GetCard() == playerCard.GetCard()) {
					continue;
				}
				if (i > 0) {
					cout << " and ";
				}

				cout << GetNumberName(printTableBuildCards[i].GetNumber()) << " of ";
				cout << GetSuitName(printTableBuildCards[i].GetSuit());

			}
		}
		// Building onto an existing build
		else {
			cout << " to add to an existing build with the ";

			// Cycling through the cards from the existing build that the card was added to
			for (size_t i = 0; i < printTableBuildCards.size(); i++) {
				if (i > 0) {
					cout << " and ";
				}
				cout << GetNumberName(printTableBuildCards[i].GetNumber()) << " of ";
				cout << GetSuitName(printTableBuildCards[i].GetSuit());

			}
		}
	}
	// When the human captures...
	else if (playerMove == 'c') {

		cout << "The player chose to play a ";
		// If the number of the card is less than 10, just print the number
		cout << GetNumberName(playerCard.GetNumber()) << " of ";
		cout << GetSuitName(playerCard.GetSuit()) << " to capture ";

		// Now cycling through the cards the player captured
		for (size_t i = 0; i < printTableCaptureCards.size(); i++) {

			if (i > 0) {
				cout << " and ";
			}
			cout << "the ";

			cout << GetNumberName(printTableCaptureCards[i].GetNumber());
			cout << " of " << GetSuitName(printTableCaptureCards[i].GetSuit()) << endl;
		}

		vector<Card> cardsOfASet;
		// Now outputting any sets the player also captured if they did
		if (tolower(playerWantSet) == 'y') {
			cout << " and the set of ";

			// First cycling through the list of sets
			for (size_t i = 0; i < playerOfSetCards.size(); i++) {
				cardsOfASet = playerOfSetCards[i].GetCardsOfSet();

				// Then cycling through the list of cards in a set
				for (size_t j = 0; j < cardsOfASet.size(); j++) {

					if (j > 0) {
						cout << " and ";
					}

					cout << GetNumberName(cardsOfASet[j].GetNumber());
					cout << " of ";
					cout << GetSuitName(cardsOfASet[j].GetSuit());
				}
				cout << endl;
			}
		}
	}
	// If the player is trailing
	else if (tolower(playerMove) == 't') {
		cout << "The player trailed with the " << GetNumberName(playerCard.GetNumber());
		cout << " of " << GetSuitName(playerCard.GetSuit());
	}
	else {
		cerr << "Error dont know what the player did in the human class." << endl;
	}
}

/* *********************************************************************
Function Name: MakePlay
Purpose: Prompts the user for what kind of play they want to make
Parameters: None
Return Value: Void
Local Variables:
userInput, an string used to get user input
Algorithm:
1) Prompt the user to enter a type of move to make
2) Depending on what the user picked, another function will be called for each type of move
Assistance Received: none
********************************************************************* */
void Human::MakePlay() {

	string userInput;
	do {
		cout << "Type 'b' to build, 'c' to capture, or 't' to trail: ";
		cin >> userInput;

		if (tolower(userInput[0]) != 'b' && tolower(userInput[0]) != 'c' && tolower(userInput[0]) != 't' && userInput.size() > 1) {
			cout << "Try again." << endl;
			userInput = "-1";
		}
	} while (tolower(userInput[0]) != 'b' && tolower(userInput[0]) != 'c' && tolower(userInput[0]) != 't');


	// Saving the players move
	playerMove = tolower(userInput[0]);

	// Building
	if (playerMove == 'b') {
		MakeBuild();
	}
	// Capturing
	else if (playerMove == 'c') {
		MakeCapture();
	}
	// Trailing
	else if (playerMove == 't') {
		MakeTrail();
	}
	else {
		cerr << "Error in making a move by the player." << endl;
	}
}

/* *********************************************************************
Function Name: MakeBuild
Purpose: Get user input for a build card from there hand and build cards from the table
Parameters: None
Return Value: Void
Local Variables:
userInput, an string used to get user input
hasCard, a boolean for if the user has a card in their hand or not
count, an integer counter for keeping track of how many build cards
Algorithm:
1) Prompt the user for what card from their hand they want to build with
2) Check if they have that card
3) Then ask them for the cards on the table they want to build with
Assistance Received: none
********************************************************************* */
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

	do {
		cout << "Are you making a new build or adding to a build? ('n' for new and 'e' for existing): ";
		cin >> userInput;
		if (tolower(userInput[0]) != 'n' && tolower(userInput[0]) != 'e' && userInput.size() > 1) {
			cout << "Try again." << endl;
			userInput = "-1";
		}
	} while (tolower(userInput[0]) != 'n' && tolower(userInput[0]) != 'e');

	newOrExistingBuild = userInput[0];

	// If they want to add to an existing build, then ask them for a card from an existing build they want to add to
	if (newOrExistingBuild == 'e') {
		do {
			cout << "Enter a card from a build you want to add onto: ";
			cin >> userInput;
		} while (!CheckCard(userInput));

		existingBuildCard.SetCard(userInput);
	}

	// If they are making a new build, then prompt them for all the necessary information
	if (newOrExistingBuild == 'n') {
		int count = 0;

		// Have a loop go through and ask the user for how many cards they would like to build with
		do {
			cout << "Enter the card(s) you want to build with, press 'enter' after each card('p' to stop): ";
			cin >> userInput;

			// If they typed in the correct input, 
			if (tolower(userInput[0]) != 'p' && CheckCard(userInput)) {
				buildCards.push_back(Card());
				buildCards[count].SetCard(userInput);
				count++;
			}
			else if (tolower(userInput[0]) != 'p') {
				cout << "**** Incorrect input, disreguarding. ****" << endl;
			}

		} while (tolower(userInput[0]) != 'p');
	}

}

/* *********************************************************************
Function Name: MakeCapture
Purpose: Prompts the user for information reguarding a capture
Parameters: None
Return Value: Void
Local Variables:
userInput, an string used to get user input
hasCard, a boolean for checking if a card they entered exists in their hand
Algorithm:
1) Prompt the user to enter a card they want to capture with
2) Check and make sure they have that card
3) If they have the card, then ask if they want to make a set
4) If they say yes, it sets a variable, "playerWantSet" to y which is used in another function
Assistance Received: none
********************************************************************* */
void Human::MakeCapture() {

	string userInput;
	bool hasCard = false;
	vector<Card> setCards;

	playerWantSet = 'n';

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

	// Ask the user if they are capturing a build, and if so, skip the sets and prompt them
	// For a card from the build
	do {
		cout << "Do you want to capture a build? (y,n): ";
		cin >> userInput;
		if (tolower(userInput[0]) != 'y' && tolower(userInput[0]) != 'n' || userInput.size() > 1) {
			cout << "Try again." << endl;
			userInput = "-1";
		}
	} while (userInput[0] != 'y' && userInput[0] != 'n');

	playerWantBuild = userInput[0];

	if (playerWantBuild == 'y') {
		do {
			cout << "Enter a card from the build you want to capture: ";
			cin >> userInput;
		} while (!CheckCard(userInput));

		existingBuildCard.SetCard(userInput);
	}

	if (playerWantBuild != 'y') {
		// Finally, ask the user if they want to make a set while using the capture card
		do {
			cout << "Are there any sets you would like to capture? (y, n): ";
			cin >> userInput;
		} while (tolower(userInput[0]) != 'y' && tolower(userInput[0]) != 'n');

		playerWantSet = userInput[0];
	}

	// If the user wants to capture a set aswell, this is the code that will handle user input for that
	Set tempSet;
	Card tempCard;
	if (playerWantSet == 'y') {
		do {

			// Prompt the user for two cards they want to use for a set
			do {
				cout << "Enter two cards for a set: ";
				cin >> userInput;

				// So long as what they entered is a valid card, it will be pushed onto the vector of cards
				if (CheckCard(userInput)) {
					tempCard.SetCard(userInput);
					setCards.push_back(tempCard);
				}
				else {
					cout << "Invalid card, entry is disreguarded. Try again." << endl;
				}
			} while (setCards.size() != 2);

			// After the user entered two cards, the vector of cards is pushed onto a set object and then that
			// set object is pushed onto a vector of sets
			tempSet.SetCardsOfSet(setCards);
			playerOfSetCards.push_back(tempSet);

			// After that the user has the option to enter in another set and repeat the process
			cout << "Do you want to capture another set? (y,n): ";
			cin >> userInput;
		} while (tolower(userInput[0]) != 'n');
	}
}

/* *********************************************************************
Function Name: MakeTrail
Purpose: Prompts the user for any kind of information regaurding a trail
Parameters: None
Return Value: Void
Local Variables:
userInput, an string used to get user input
hasCard, a boolean for checking if the user has the card they enter in
Algorithm:
1) Prompt the user to enter a card to trail with
2) Once they enter a card they have, the variable, "playerCard", is set
to be that card
Assistance Received: none
********************************************************************* */
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