#pragma once
#include "Move.h"

class BachIdle : public Move {
public:
	BachIdle();
	virtual void initFrames();
	virtual void initCancelMoves() {};
};

BachIdle::BachIdle() {
	if (!spritesheet.loadFromFile("sprites/bach_idle.png")) {
		std::cerr << "Error missing BachIdle sprites!\n";
		exit(EXIT_FAILURE);
	}
	// Number of animation frames
	frameCount = 1;
	// Damage
	damage = 0;
	// Change in position on move

	// State move puts player in
	state = NO_STATE;
}

void BachIdle::initFrames() {
	BoxVec hit;
	BoxVec hurt;
	BoxVec clip;
	/***FRAME 1***/
	clip.push_back(sf::FloatRect(155, 96, 148, 423));
	hurt.push_back(sf::FloatRect(139, 289, 233, 239));
	hurt.push_back(sf::FloatRect(125, 3, 226, 292));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
}