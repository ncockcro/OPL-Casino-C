#include "Deck.h"



Deck::Deck()
{
	for (int i = 1; i < 10; i++) {
		deckOfCards.push_back("C" + to_string(i));
		deckOfCards.push_back("D" + to_string(i));
		deckOfCards.push_back("H" + to_string(i));
		deckOfCards.push_back("S" + to_string(i));
	}

	deckOfCards.push_back("CX");
	deckOfCards.push_back("DX");
	deckOfCards.push_back("HX");
	deckOfCards.push_back("SX");

	deckOfCards.push_back("CJ");
	deckOfCards.push_back("DJ");
	deckOfCards.push_back("HJ");
	deckOfCards.push_back("SJ");

	deckOfCards.push_back("CQ");
	deckOfCards.push_back("DQ");
	deckOfCards.push_back("HQ");
	deckOfCards.push_back("SQ");

	deckOfCards.push_back("CK");
	deckOfCards.push_back("DK");
	deckOfCards.push_back("HK");
	deckOfCards.push_back("SK");

	ShuffleCards();

}


Deck::~Deck()
{
}

// Prints the current vector which contains the deck of cards whenever it is called.
void Deck::PrintDeck() {
	for (size_t i = 0; i < deckOfCards.size(); i++) {
	cout << deckOfCards[i] << " ";
	}
	cout << endl;
}

// Shuffles the vector that contains the deck of cards.
void Deck::ShuffleCards() {

	// Shuffles the vector of cards
	auto rng = default_random_engine{};
	shuffle(begin(deckOfCards), end(deckOfCards), rng);
}
