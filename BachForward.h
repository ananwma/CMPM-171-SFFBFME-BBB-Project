#pragma once
#include "Move.h"

class BachForward : public Move {
public:
	BachForward();
	virtual void initFrames();
	virtual void initCancelMoves();
};

BachForward::BachForward() {
	if (!spritesheet.loadFromFile("sprites/bach_forward.png")) {
		std::cerr << "Error missing BachForward sprites!\n";
		exit(EXIT_FAILURE);
	}
	// Number of animation frames
	frameCount = 6;
	// Damage
	damage = 40;
	// Change in attacker's position on move
	velX = 0;
	velY = 0;
	// Change in opponent's position on move
	pushX = 3;
	pushY = 0;
	//Number of hitstun frames this causes
	hitstun = 5;
	//Number of blockstun frames this causes
	blockstun = 3;
	// State move puts player in
	state = ATTACK_STATE;
}

void BachForward::initFrames() {
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
	clip.push_back(sf::FloatRect(118, 130, 150, 401));
	hurt.push_back(sf::FloatRect(106, 9, 137, 115));
	hurt.push_back(sf::FloatRect(68, 316, 332, 183));
	hurt.push_back(sf::FloatRect(100, 102, 181, 216));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 4***/
	hit.push_back(sf::FloatRect(170, 312, 281, 201));
	clip.push_back(sf::FloatRect(88, 125, 149, 401));
	hurt.push_back(sf::FloatRect(76, 288, 358, 233));
	hurt.push_back(sf::FloatRect(97, 109, 181, 196));
	hurt.push_back(sf::FloatRect(88, 1, 142, 111));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 5***/
	clip.push_back(sf::FloatRect(117, 130, 137, 397));
	hurt.push_back(sf::FloatRect(104, 301, 238, 217));
	hurt.push_back(sf::FloatRect(113, 163, 152, 213));
	hurt.push_back(sf::FloatRect(98, 95, 179, 127));
	hurt.push_back(sf::FloatRect(113, 6, 125, 117));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 6***/
	clip.push_back(sf::FloatRect(158, 131, 154, 397));
	hurt.push_back(sf::FloatRect(140, 292, 202, 238));
	hurt.push_back(sf::FloatRect(157, 75, 245, 115));
	hurt.push_back(sf::FloatRect(150, 164, 173, 191));
	hurt.push_back(sf::FloatRect(148, 44, 139, 116));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
}

void BachForward::initCancelMoves() {
	cancelMoves.push_back(GMAJ);
}