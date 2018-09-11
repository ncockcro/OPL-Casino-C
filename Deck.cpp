#include "Deck.h"



Deck::Deck()
{
	int count = 0;

	// 2-9 cards
	for (int i = 2; i < 10; i++) {
		deckOfCards.push_back(Card());
		deckOfCards[count].SetCard("C" + to_string(i));
		deckOfCards[count].SetSuit('C');
		deckOfCards[count].SetNumber('0' + i);
		count++;
		deckOfCards.push_back(Card());
		deckOfCards[count].SetCard("D" + to_string(i));
		deckOfCards[count].SetSuit('D');
		deckOfCards[count].SetNumber('0' + i);
		count++;
		deckOfCards.push_back(Card());
		deckOfCards[count].SetCard("H" + to_string(i));
		deckOfCards[count].SetSuit('H');
		deckOfCards[count].SetNumber('0' + i);
		count++;
		deckOfCards.push_back(Card());
		deckOfCards[count].SetCard("S" + to_string(i));
		deckOfCards[count].SetSuit('S');
		deckOfCards[count].SetNumber('0' + i);
		count++;
	}

	// Tens
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("CX");
	deckOfCards[count].SetSuit('C');
	deckOfCards[count].SetNumber('X');
	count++;
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("DX");
	deckOfCards[count].SetSuit('D');
	deckOfCards[count].SetNumber('X');
	count++;
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("HX");
	deckOfCards[count].SetSuit('H');
	deckOfCards[count].SetNumber('X');
	count++;
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("SX");
	deckOfCards[count].SetSuit('S');
	deckOfCards[count].SetNumber('X');
	count++;

	// Jacks
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("CJ");
	deckOfCards[count].SetSuit('C');
	deckOfCards[count].SetNumber('J');
	count++;
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("DJ");
	deckOfCards[count].SetSuit('D');
	deckOfCards[count].SetNumber('J');
	count++;
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("HJ");
	deckOfCards[count].SetSuit('H');
	deckOfCards[count].SetNumber('J');
	count++;
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("SJ");
	deckOfCards[count].SetSuit('S');
	deckOfCards[count].SetNumber('J');
	count++;

	// Queens
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("CQ");
	deckOfCards[count].SetSuit('C');
	deckOfCards[count].SetNumber('Q');
	count++;
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("DQ");
	deckOfCards[count].SetSuit('D');
	deckOfCards[count].SetNumber('Q');
	count++;
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("HQ");
	deckOfCards[count].SetSuit('H');
	deckOfCards[count].SetNumber('Q');
	count++;
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("SQ");
	deckOfCards[count].SetSuit('S');
	deckOfCards[count].SetNumber('Q');
	count++;

	// Kings
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("CK");
	deckOfCards[count].SetSuit('C');
	deckOfCards[count].SetNumber('K');
	count++;
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("DK");
	deckOfCards[count].SetSuit('D');
	deckOfCards[count].SetNumber('K');
	count++;
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("HK");
	deckOfCards[count].SetSuit('H');
	deckOfCards[count].SetNumber('K');
	count++;
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("SK");
	deckOfCards[count].SetSuit('S');
	deckOfCards[count].SetNumber('K');
	count++;

	// Aces
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("CA");
	deckOfCards[count].SetSuit('C');
	deckOfCards[count].SetNumber('A');
	count++;
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("DA");
	deckOfCards[count].SetSuit('D');
	deckOfCards[count].SetNumber('A');
	count++;
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("HA");
	deckOfCards[count].SetSuit('H');
	deckOfCards[count].SetNumber('A');
	count++;
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("SA");
	deckOfCards[count].SetSuit('S');
	deckOfCards[count].SetNumber('A');
	count++;

	// Shuffle the cards
	ShuffleCards();

}


Deck::~Deck()
{
}

// Prints the current vector which contains the deck of cards whenever it is called.
void Deck::PrintDeck() {
	for (size_t i = 0; i < deckOfCards.size(); i++) {
	cout << deckOfCards[i].GetCard() << " ";
	}
	cout << endl;
}

// Returns true if the deck of cards is empty, false if it is not.
bool Deck::IsEmpty() {

	if (deckOfCards.empty()) {
		return true;
	}
	else {
		return false;
	}
}

// Returns the deck of cards
const vector<Card> Deck::GetDeck() {
	return deckOfCards;
}

// Removes four cards from the deck.
void Deck::RemoveFourCards() {

	deckOfCards.erase(deckOfCards.begin(), deckOfCards.begin() + 4);
}

// Shuffles the vector that contains the deck of cards.
void Deck::ShuffleCards() {

	// Shuffles the vector of cards
	random_shuffle(begin(deckOfCards), end(deckOfCards));
}
