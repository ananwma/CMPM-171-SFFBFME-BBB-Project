#pragma once
#include "Move.h"

class BachGrab : public Move {
public:
	BachGrab();
	virtual void initFrames();
	virtual void initCancelMoves();
};

BachGrab::BachGrab() {
	if (!spritesheet.loadFromFile("sprites/Bachmissgrab.png")) {
		std::cerr << "Error missing BachGrab sprites!\n";
		exit(EXIT_FAILURE);
	}
	// Number of animation frames
	frameCount = 5;
	// Damage
	damage = 40;
	// Change in attacker's position on move
	velX = 0;
	velY = 0;
	// Change in opponent's position on move
	pushX = -10;
	pushY = -40;
	//Number of hitstun frames this causes
	hitstun = 6;
	//Number of blockstun frames this causes
	blockstun = 0;
	// State move puts player in
	state = GRAB_STATE;
	
	initFrames();
}

void BachGrab::initFrames() {
	BoxVec hit;
	BoxVec hurt;
	BoxVec clip;
	/***FRAME 1***/
	clip.push_back(sf::FloatRect(62, 111, 169, 415));
	hurt.push_back(sf::FloatRect(24, 95, 243, 433));
	hurt.push_back(sf::FloatRect(53, 8, 139, 221));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 2***/
	clip.push_back(sf::FloatRect(88, 113, 143, 401));
	hurt.push_back(sf::FloatRect(8, 314, 286, 208));
	hurt.push_back(sf::FloatRect(63, 121, 193, 308));
	hurt.push_back(sf::FloatRect(71, 20, 156, 224));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 3***/
	clip.push_back(sf::FloatRect(109, 143, 139, 382));
	hit.push_back(sf::FloatRect(116, 60, 221, 187));
	hurt.push_back(sf::FloatRect(38, 62, 297, 120));
	hurt.push_back(sf::FloatRect(10, 320, 295, 215));
	hurt.push_back(sf::FloatRect(77, 159, 188, 177));
	hurt.push_back(sf::FloatRect(75, 52, 154, 126));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 4***/
	clip.push_back(sf::FloatRect(96, 145, 149, 381));
	hurt.push_back(sf::FloatRect(91, 160, 178, 361));
	hurt.push_back(sf::FloatRect(110, 68, 212, 141));
	hurt.push_back(sf::FloatRect(81, 41, 153, 133));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 5***/
	clip.push_back(sf::FloatRect(55, 133, 163, 370));
	hurt.push_back(sf::FloatRect(26, 52, 261, 135));
	hurt.push_back(sf::FloatRect(11, 162, 245, 346));
	hurt.push_back(sf::FloatRect(51, 37, 149, 166));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 6***/
	hurt.push_back(sf::FloatRect(33, 119, 293, 144));
	hurt.push_back(sf::FloatRect(25, 135, 181, 380));
	hurt.push_back(sf::FloatRect(16, 38, 166, 120));
	clip.push_back(sf::FloatRect(49, 141, 135, 378));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
}

void BachGrab::initCancelMoves() {
	//cancelMoves.push_back(GMAJ);
}
