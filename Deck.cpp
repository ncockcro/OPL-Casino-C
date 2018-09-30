#include "Deck.h"



Deck::Deck()
{
	int count = 0;

	// 2-9 cards
	for (int i = 2; i < 10; i++) {
		deckOfCards.push_back(Card());
		deckOfCards[count].SetCard("C" + to_string(i));
		count++;
		deckOfCards.push_back(Card());
		deckOfCards[count].SetCard("D" + to_string(i));
		count++;
		deckOfCards.push_back(Card());
		deckOfCards[count].SetCard("H" + to_string(i));
		count++;
		deckOfCards.push_back(Card());
		deckOfCards[count].SetCard("S" + to_string(i));
		count++;
	}

	// Tens
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("CX");
	count++;
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("DX");
	count++;
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("HX");
	count++;
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("SX");
	count++;

	// Jacks
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("CJ");
	count++;
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("DJ");
	count++;
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("HJ");
	count++;
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("SJ");
	count++;

	// Queens
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("CQ");
	count++;
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("DQ");
	count++;
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("HQ");
	count++;
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("SQ");
	count++;

	// Kings
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("CK");
	count++;
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("DK");
	count++;
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("HK");
	count++;
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("SK");
	count++;

	// Aces
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("CA");
	count++;
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("DA");
	count++;
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("HA");
	count++;
	deckOfCards.push_back(Card());
	deckOfCards[count].SetCard("SA");
	count++;

	// Shuffle the cards
	ShuffleCards();

}

/* *********************************************************************
Function Name: Deck(vector<Card> cards)
Purpose: Overloaded constructor used for when the player wants to load their own deck in
Parameters:
cards, holds cards read in from a file, a vector of cards value
Return Value: Void
Local Variables: None
Algorithm:
1) Iterate through the vector of cards and store them in the deck
Assistance Received: none
********************************************************************* */
Deck::Deck(vector<Card> cards) {

	deckOfCards = cards;
}

/* *********************************************************************
Function Name: PrintDeck
Purpose: Print out the cards from the deck
Parameters: None
Return Value: Void
Local Variables: None
Algorithm:
1) Iterate through the vector of cards and print them out to the console
Assistance Received: none
********************************************************************* */
void Deck::PrintDeck() {
	for (size_t i = 0; i < deckOfCards.size(); i++) {
	cout << deckOfCards[i].GetCard() << " ";
	}
	cout << endl;
}

/* *********************************************************************
Function Name: IsEmpty
Purpose: Checks if a deck of cards is empty
Parameters: None
Return Value: Returns if there are cards or there are not, a boolean value
Local Variables: None
Algorithm:
1) If a deck is empty, return true, otherwise, return false
Assistance Received: none
********************************************************************* */
bool Deck::IsEmpty() {

	if (deckOfCards.empty()) {
		return true;
	}
	else {
		return false;
	}
}

/* *********************************************************************
Function Name: GetDeck
Purpose: Getter for getting a copy of a deck of cards
Parameters: None
Return Value: a constant vector of cards
Local Variables: None
Algorithm:
1) Return a copy of the deck of cards
Assistance Received: none
********************************************************************* */
vector<Card> Deck::GetDeck() const {
	return deckOfCards;
}

/* *********************************************************************
Function Name: RemoveFourCards
Purpose: Removes four cards from the deck, handy when dealing cards to the players
Parameters: None
Return Value: Void
Local Variables: None
Algorithm:
1) Erase four cards from the deck
Assistance Received: none
********************************************************************* */
void Deck::RemoveFourCards() {

	deckOfCards.erase(deckOfCards.begin(), deckOfCards.begin() + 4);
}

/* *********************************************************************
Function Name: ShuffleCards
Purpose: Shuffles the cards of a deck
Parameters: None
Return Value: Void
Local Variables: None
Algorithm:
1) Shuffle the deck of cards
Assistance Received: none
********************************************************************* */
void Deck::ShuffleCards() {
	srand((unsigned int)time(0));

	// Shuffles the vector of cards
	random_shuffle(begin(deckOfCards), end(deckOfCards));
}
