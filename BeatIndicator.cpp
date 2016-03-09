#include "stdafx.h"
#include "BeatIndicator.h"
#include "Player.h"

BeatIndicator::BeatIndicator() {
	if (!bTexture.loadFromFile("sprites/metro_indicator.png")) {
		std::cerr << "Error missing Metronome Indicator sprites!\n";
		exit(EXIT_FAILURE);
	}
	bSprite.setTexture(bTexture);
	bState = NOBEAT;
	width = 154;
	height = 100;
	bSprite.setTextureRect(sf::IntRect(bState * width, 0, width, height));
	



}

void BeatIndicator::updateIndicator(BeatStates b) {
	bState = b;
	bSprite.setTextureRect(sf::IntRect(bState * width, 0, width, height));


}