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
	// Change in position on move
	deltax = X;
	deltay = X;
   // State move puts player in
	state = STATE;
}

void MOVENAME::initFrames() {
	BoxVec hit;
	BoxVec hurt;
	/****PASTE GENERATED CODE HERE****/
}

void MOVENAME::initCancelMoves() {

}