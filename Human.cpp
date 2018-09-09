#include "Human.h"



Human::Human()
{
}


Human::~Human()
{
}

// Exclusive details for when the human is making a move.
void Human::MakeMove() {
	cout << "Human making move." << endl;
	hand.pop_back();
	hand.pop_back();
	hand.pop_back();
	hand.pop_back();
}