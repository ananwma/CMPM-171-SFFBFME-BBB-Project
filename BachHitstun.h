#pragma once
#include "Move.h"

class BachHitstun : public Move {
public:
	BachHitstun();
	virtual void initFrames();
};

BachHitstun::BachHitstun() {
	if (!spritesheet.loadFromFile("sprites/bach_hitstun.png")) {
		std::cerr << "Error missing BachHitstun sprites!\n";
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
	state = HITSTUN_STATE;
}

void BachHitstun::initFrames() {
	BoxVec hit;
	BoxVec hurt;
	/***FRAME 1***/
	hurt.push_back(sf::FloatRect(148, 277, 223, 226));
	hurt.push_back(sf::FloatRect(100, 24, 221, 284));
	frameVector.push_back(Frame(hit, hurt));
	hit.clear();
	hurt.clear();
}