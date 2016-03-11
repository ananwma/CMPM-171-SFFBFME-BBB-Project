#pragma once
#include "Move.h"

class BachShort : public Move {
public:
	BachShort();
	virtual void initFrames();
	virtual void initCancelMoves();
};

BachShort::BachShort() {
	if (!spritesheet.loadFromFile("sprites/bach_short.png")) {
		std::cerr << "Error missing BachShort sprites!\n";
		exit(EXIT_FAILURE);
	}
	// Number of animation frames
	frameCount = 5;
	// Damage
	damage = 20;
	// Change in attacker's position on move
	velX = 0;
	velY = 0;
	// Change in opponent's position on move
	pushX = 0;
	pushY = 0;
	//Number of hitstun frames this causes
	hitstun = 2;
	//Number of blockstun frames this causes
	blockstun = 1;
	// State move puts player in
	state = ATTACK_STATE;

	initFrames();
}

void BachShort::initFrames() {
	BoxVec hit;
	BoxVec hurt;
	BoxVec clip;
	/***FRAME 1***/
	clip.push_back(sf::FloatRect(144, 99, 154, 432));
	hurt.push_back(sf::FloatRect(129, 104, 201, 173));
	hurt.push_back(sf::FloatRect(120, 272, 231, 251));
	hurt.push_back(sf::FloatRect(132, 3, 131, 102));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 2***/
	clip.push_back(sf::FloatRect(145, 103, 159, 425));
	hurt.push_back(sf::FloatRect(113, 113, 219, 182));
	hurt.push_back(sf::FloatRect(108, 281, 246, 238));
	hurt.push_back(sf::FloatRect(121, 6, 143, 109));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 3***/
	hit.push_back(sf::FloatRect(221, 444, 190, 70));
	clip.push_back(sf::FloatRect(118, 130, 150, 401));
	hurt.push_back(sf::FloatRect(106, 9, 137, 115));
	hurt.push_back(sf::FloatRect(68, 316, 332, 183));
	hurt.push_back(sf::FloatRect(100, 102, 181, 216));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 4***/
	hurt.push_back(sf::FloatRect(89, 281, 268, 236));
	clip.push_back(sf::FloatRect(155, 120, 149, 401));
	hurt.push_back(sf::FloatRect(146, 121, 181, 196));
	hurt.push_back(sf::FloatRect(133, 13, 142, 111));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 5***/
	clip.push_back(sf::FloatRect(142, 125, 137, 397));
	hurt.push_back(sf::FloatRect(104, 301, 238, 217));
	hurt.push_back(sf::FloatRect(143, 160, 152, 213));
	hurt.push_back(sf::FloatRect(136, 91, 179, 127));
	hurt.push_back(sf::FloatRect(113, 6, 125, 117));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
}

void BachShort::initCancelMoves() {

}