#pragma once
#include "Move.h"

class BachJab : public Move {
public:
	BachJab();
	virtual void initFrames();
	virtual void initCancelMoves();
};

BachJab::BachJab() {
	if (!spritesheet.loadFromFile("sprites/bach_jab.png")) {
		std::cerr << "Error missing Bach jab sprites!\n";
		exit(EXIT_FAILURE);
	}
	// Number of animation frames
	frameCount = 3;
	// Damage
	damage = 20;
	// Change in position on move
	deltax = 0;
	deltay = 0;
	// State move puts player in
	state = ATTACKING;
}

void BachJab::initFrames() {
	BoxVec hit;
	BoxVec hurt;
	BoxVec clip;
	/***FRAME 1***/
	clip.push_back(sf::FloatRect(127, 102, 173, 412));
	hurt.push_back(sf::FloatRect(139, 289, 223, 239));
	hurt.push_back(sf::FloatRect(125, 3, 226, 292));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 2***/
	hit.push_back(sf::FloatRect(196, 93, 178, 119));
	clip.push_back(sf::FloatRect(139, 102, 161, 414));
	hurt.push_back(sf::FloatRect(108, 296, 253, 223));
	hurt.push_back(sf::FloatRect(114, 9, 247, 288));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 3***/
	clip.push_back(sf::FloatRect(129, 111, 155, 418));
	hurt.push_back(sf::FloatRect(178, 55, 255, 227));
	hit.push_back(sf::FloatRect(162, 75, 276, 114));
	hurt.push_back(sf::FloatRect(110, 277, 235, 246));
	hurt.push_back(sf::FloatRect(78, 17, 173, 280));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
}

void BachJab::initCancelMoves() {
	cancelMoves.push_back(JAB);
	cancelMoves.push_back(STRONG);

}