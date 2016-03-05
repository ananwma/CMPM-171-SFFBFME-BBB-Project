#pragma once
#include "Move.h"

class BachShoryuken : public Move {
public:
	BachShoryuken();
	virtual void initFrames();
	virtual void initCancelMoves();
};

BachShoryuken::BachShoryuken() {
	if (!spritesheet.loadFromFile("sprites/bach_furious_fugue_flail.png")) {
		std::cerr << "Error missing BachShoryuken sprites!\n";
		exit(EXIT_FAILURE);
	}
	// Number of animation frames
	frameCount = 7;
	// Damage
	damage = 100;
	//Number of hitstun frames this causes
	hitstun = 8;
	//Number of blockstun frames this causes
	blockstun = 4;
	// Change in position on move
	velY = -20;
	velX = 3;
	// Change in opponents position
	pushY = -20;
	pushX = 15;
	// State move puts player in
	state = AIRBORNE_STATE;
}

void BachShoryuken::initFrames() {
	BoxVec hit;
	BoxVec hurt;
	BoxVec clip;
	frameVector.push_back(Frame(hit, hurt, clip));
	/***FRAME 2***/
	hit.push_back(sf::FloatRect(199, 26, 141, 259));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	frameVector.push_back(Frame(hit, hurt, clip));
	frameVector.push_back(Frame(hit, hurt, clip));
	/***FRAME 5***/
	hit.push_back(sf::FloatRect(274, 5, 114, 246));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	frameVector.push_back(Frame(hit, hurt, clip));
	frameVector.push_back(Frame(hit, hurt, clip));
}

void BachShoryuken::initCancelMoves() {

}