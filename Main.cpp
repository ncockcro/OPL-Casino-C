/*
Written by: Nicholas Cockcroft
Date: September 5, 2018

Description: Main part of the program which runs everything and is responsible for starting the program.
*/

#include <iostream>
#include "Tournament.h"

using namespace std;

int main() {
	Tournament masterGame = Tournament();

	masterGame.PlayGame();

	system("pause");
	return 0;
}