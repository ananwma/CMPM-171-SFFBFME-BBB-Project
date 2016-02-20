#pragma once
#include "Move.h"

class BachIdle : public Move {
public:
	BachIdle();
	virtual void initFrames();
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
	deltax = 0;
	deltay = 0;
	// State move puts player in
	state = NONE;
}

void BachIdle::initFrames() {
	BoxVec hit;
	BoxVec hurt;
	/***FRAME 1***/
	hurt.push_back(sf::FloatRect(139, 289, 233, 239));
	hurt.push_back(sf::FloatRect(125, 3, 226, 292));
	frameVector.push_back(Frame(hit, hurt));
	hit.clear();
	hurt.clear();
}