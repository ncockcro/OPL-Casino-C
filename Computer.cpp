#include "Computer.h"



Computer::Computer()
{
}

/* *********************************************************************
Function Name: MakeMove
Purpose: To make a move specific for the computer
Parameters:
falseMove, if the entered a move prior and it was wrong, this will go straight to making a move again, a boolean value
Return Value: Void
Local Variables: None
Algorithm:
1) Check if the computer can make a build and make it
2) If can't build, check if the computer can capture and make it
3) If it can't build or capture, then just trail
Assistance Received: none
********************************************************************* */
void Computer::MakeMove(vector<Card> table, vector<Build> tableBuilds) {

	string userInput;

	cout << "Computer's turn." << endl;
	do {
		cout << "1.) Save the game" << endl;
		cout << "2.) Computer make a move" << endl;
		cout << "3.) Quit the game: ";
		cin >> userInput;

		if (userInput != "1" && userInput != "2" && userInput != "3") {
			cout << endl;
			cout << "Incorrect menu option." << endl;
			cout << endl;
		}
	} while (userInput != "1" && userInput != "2" && userInput != "3");

	// Save game
	if (userInput == "1") {
		playerWantSave = true;
		return;
	}

	// Quit the game
	else if (userInput == "3") {
		exit(1);
	}

	// Check if the computer can make a build
	if (AICheckForBuild(hand, table, tableBuilds)) {
		playerMove = 'b';
		return;
	}

	// Check if the player can make a capture
	if (AICheckForCapture(hand, table, tableBuilds)) {
		playerMove = 'c';
		return;
	}

	// If it cant do either of those things, then trail
	else {
		AIMakeTrail(hand);
		playerMove = 't';
		return;
	}
}

/* *********************************************************************
Function Name: PrintMove
Purpose: For each player to print out the move they just made
Parameters: None
Return Value: Void
Local Variables: None
Algorithm:
1) This is where the computer will output their moves after each of their turns
Assistance Received: none
********************************************************************* */
void Computer::PrintMove() {

	// If the computer made a build...
	if (playerMove == 'b') {
	
		cout << endl;
		cout << "The computer chose to play a " << GetNumberName(playerCard.GetNumber()) << " of ";
		cout << GetSuitName(playerCard.GetSuit());

		// **** New Builds ****
		if (newOrExistingBuild == 'n') {
			cout << endl << " to make a build with the ";

			// Cycling through the cards that were from the table that made the build
			for (size_t i = 0; i < buildCards.size(); i++) {
				if (i > 1) {
					cout << " and ";
				}
				cout << GetNumberName(buildCards[i].GetNumber()) << " of ";
				cout << GetSuitName(buildCards[i].GetSuit());
			}
			cout << endl;
			cout << "It wanted to be able to capture more cards later." << endl;
		}

		// **** Adding to an existing build ****
		else if (newOrExistingBuild == 'e') {
			cout << " to add to an existing build with the ";

			// Cycling through the cards that already existed in the build
			for (size_t i = 0; i < printTableBuildCards.size(); i++) {
				if (i > 1) {
					cout << " and ";
				}
				cout << GetNumberName(printTableBuildCards[i].GetNumber()) << " of ";
				cout << GetSuitName(printTableBuildCards[i].GetSuit());
			}
			cout << ". " << endl << "It wanted to steal the opponents cards." << endl;
		}
		else {
			cerr << "Something went wrong when printing computer builds in the computer class.";
		}
		printTableBuildCards.clear();
	}

	// If the computer captured...
	else if (playerMove == 'c') {
		cout << "The computer chose to play a " << GetNumberName(playerCard.GetNumber());
		cout << " of " << GetSuitName(playerCard.GetSuit()) << endl << "to capture the ";

		// If the computer captured a build...
		if (printPlayerCapturedBuild == 'y') {
			for (size_t i = 0; i < printTableBuildCards.size(); i++) {
				if (i > 0) {
					cout << " and ";
				}

				cout << GetNumberName(printTableBuildCards[i].GetNumber()) << " of ";
				cout << GetSuitName(printTableBuildCards[i].GetSuit());
			}
		}

		// Print out any loose cards the player captured
		for (size_t i = 0; i < printTableCaptureCards.size(); i++) {
			if (i > 1) {
				cout << " and ";
			}

			cout << GetNumberName(printTableCaptureCards[i].GetNumber()) << " of ";
			cout << GetSuitName(printTableCaptureCards[i].GetSuit());
		}
		cout << endl;

		vector<Card> setCards;
		if (playerWantSet == 'y') {
			cout << " and the set of ";

			// First cycling through the vector of sets
			for (size_t i = 0; i < playerOfSetCards.size(); i++) {
				setCards = playerOfSetCards[i].GetCardsOfSet();

				// Then cycling through the cards in that set to be printed out
				for (size_t j = 0; j < setCards.size(); j++) {
					if (i > 0) {
						cout << " and ";
					}

					cout << GetNumberName(setCards[j].GetNumber()) << " of ";
					cout << GetSuitName(setCards[j].GetSuit());
				}
			}
		}
		cout << endl;
		cout << "It wanted to add more cards to its pile." << endl;

		// Clearing the print vectors
		printTableBuildCards.clear();
		printTableCaptureCards.clear();
	}
	// If the computer trailed...
	else if (playerMove == 't') {
		cout << "The computer chose to trail with the " << GetNumberName(playerCard.GetNumber()) << " of ";
		cout << GetSuitName(playerCard.GetSuit()) << endl;
		cout << "It had no other moves to make." << endl;
	}
	else {
		cerr << "Uknown player move in the computer class." << endl;
	}
}