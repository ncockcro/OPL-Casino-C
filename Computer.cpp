#include "Computer.h"



Computer::Computer()
{
}


Computer::~Computer()
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
void Computer::MakeMove(bool falseMove, vector<Card> table, vector<Build> tableBuilds) {

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
