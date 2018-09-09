#include "Computer.h"



Computer::Computer()
{
}


Computer::~Computer()
{
}

// Exclusive details for when the computer is making a move.
void Computer::MakeMove() {
	cout << "Computer making move." << endl;
	hand.pop_back();
	hand.pop_back();
	hand.pop_back();
	hand.pop_back();
}
