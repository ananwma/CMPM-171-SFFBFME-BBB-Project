#pragma once
#include "Move.h"

class BachBlockstun : public Move {
public:
	BachBlockstun();
	virtual void initFrames();
	virtual void initCancelMoves() {};
};

BachBlockstun::BachBlockstun() {
	if (!spritesheet.loadFromFile("sprites/bach_block.png")) {
		std::cerr << "Error missing BachBlockstun sprites!\n";
		exit(EXIT_FAILURE);
	}
	// Number of animation frames
	frameCount = 1;
	// Damage
	damage = 0;
	// Change in position on move

	// State move puts player in
	state = BLOCKSTUN_STATE;
}

void BachBlockstun::initFrames() {
	BoxVec hit;
	BoxVec hurt;
	BoxVec clip;
	/***FRAME 1***/
	clip.push_back(sf::FloatRect(129, 93, 160, 408));
	hurt.push_back(sf::FloatRect(148, 277, 223, 226));
	hurt.push_back(sf::FloatRect(100, 24, 221, 284));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
}
