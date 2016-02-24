#pragma once
#include "Move.h"

class BachStrong : public Move {
public:
	BachStrong();
	virtual void initFrames();
};

BachStrong::BachStrong() {
	if (!spritesheet.loadFromFile("sprites/bach_strong.png")) {
		std::cerr << "Error missing BachStrong sprites!\n";
		exit(EXIT_FAILURE);
	}
	// Number of animation frames
	frameCount = 3;
	// Damage
	damage = 50;
	// Change in position on move
	deltax = 0;
	deltay = 0;
	// State move puts player in
	state = ATTACKING;
}

void BachStrong::initFrames() {
	BoxVec hit;
	BoxVec hurt;
	/***FRAME 1***/
	hurt.push_back(sf::FloatRect(139, 289, 231, 239));
	hurt.push_back(sf::FloatRect(125, 3, 213, 292));
	frameVector.push_back(Frame(hit, hurt));
	hit.clear();
	hurt.clear();
	/***FRAME 2***/
	hurt.push_back(sf::FloatRect(108, 296, 268, 223));
	hurt.push_back(sf::FloatRect(114, 9, 247, 288));
	frameVector.push_back(Frame(hit, hurt));
	hit.clear();
	hurt.clear();
	/***FRAME 3***/
	hurt.push_back(sf::FloatRect(177, 55, 210, 227));
	hit.push_back(sf::FloatRect(162, 75, 293, 114));
	hurt.push_back(sf::FloatRect(110, 277, 274, 264));
	hurt.push_back(sf::FloatRect(110, 52, 174, 216));
	frameVector.push_back(Frame(hit, hurt));
	hit.clear();
	hurt.clear();
}