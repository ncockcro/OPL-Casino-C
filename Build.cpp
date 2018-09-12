#include "Build.h"



Build::Build()
{
}


Build::~Build()
{
}

void Build::SetOwner(string passedOwner) {
	if (passedOwner == "human" || passedOwner == "computer") {
		owner = passedOwner;
	}
	else {
		cout << "Error in setting the owner of a build in the build class." << endl;
	}
}
const string Build::GetOwner() {
	return owner;
}

void Build::SetBuildOfCards(vector<Card> buildCards) {
	for (size_t i = 0; i < buildCards.size(); i++) {
		if (buildCards[i].GetCard().size() == 2) {
			buildOfCards.push_back(buildCards[i]);
		}
		else {
			cout << "Error in added a card to the build vector in the build.cpp" << endl;
		}
	}
}
const vector<Card> Build::GetBuildOfCards() {
	return buildOfCards;
}

void Build::PrintBuild() {

	cout << " [ ";
	for (size_t i = 0; i < buildOfCards.size(); i++) {
		cout << buildOfCards[i].GetCard() << " ";
	}
	cout << " ] ";
}