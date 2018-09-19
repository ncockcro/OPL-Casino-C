#include "Computer.h"



Computer::Computer()
{
}


Computer::~Computer()
{
}

// Exclusive details for when the computer is making a move.
void Computer::MakeMove(bool falseMove) {
	cout << "Computer making move." << endl;
	playerMove = 't';
	playerCard.SetCard(hand.back().GetCard());
	hand.pop_back();
}
