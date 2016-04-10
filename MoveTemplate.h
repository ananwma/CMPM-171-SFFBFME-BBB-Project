#pragma once
#include "Move.h"

class MOVENAME : public Move {
public:
	MOVENAME();
	virtual void initFrames();
	virtual void initCancelMoves();
};

MOVENAME::MOVENAME() {
	if (!spritesheet.loadFromFile("sprites/FILENAME.png")) {
		std::cerr << "Error missing MOVENAME sprites!\n";
		exit(EXIT_FAILURE);
	}
	// Number of animation frames
	frameCount = X;
	// Damage
	damage = X;
	// Change in attacker's position on move
	velX = X;
   velY = X;
   // Change in opponent's position on move
	pushX = X;
   pushY = X;
   //Number of hitstun frames this causes
	hitstun = X;
	//Number of blockstun frames this causes
	blockstun = X;
   // State move puts player in
	state = STATE;
}

void MOVENAME::initFrames() {
	BoxVec hit;
	BoxVec hurt;
   BoxVec clip;
	/****PASTE GENERATED CODE HERE****/
}

void MOVENAME::initCancelMoves() {

}