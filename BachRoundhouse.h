#pragma once
#include "Move.h"

class BachRoundhouse : public Move {
public:
	BachRoundhouse();
	virtual void initFrames();
	virtual void initCancelMoves();
};

BachRoundhouse::BachRoundhouse() {
	if (!spritesheet.loadFromFile("sprites/bach_roundhouse.png")) {
		std::cerr << "Error missing BachRoundhouse sprites!\n";
		exit(EXIT_FAILURE);
	}
	// Number of animation frames
	frameCount = 7;
	// Damage
	damage = 80;
	// Change in attacker's position on move
	velX = 0;
	velY = 0;
	// Change in opponent's position on move
	pushX = 6;
	pushY = -2;
	//Number of hitstun frames this causes
	hitstun = 5;
	//Number of blockstun frames this causes
	blockstun = 4;
	// State move puts player in
	state = ATTACK_STATE;
}

void BachRoundhouse::initFrames() {
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
	clip.push_back(sf::FloatRect(108, 105, 150, 401));
	hurt.push_back(sf::FloatRect(93, 0, 137, 115));
	hurt.push_back(sf::FloatRect(67, 246, 307, 273));
	hurt.push_back(sf::FloatRect(102, 95, 181, 216));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 4***/
	hurt.push_back(sf::FloatRect(153, 150, 286, 173));
	hit.push_back(sf::FloatRect(164, 152, 273, 176));
	clip.push_back(sf::FloatRect(48, 105, 149, 436));
	hurt.push_back(sf::FloatRect(32, 211, 179, 330));
	hurt.push_back(sf::FloatRect(24, 91, 181, 196));
	hurt.push_back(sf::FloatRect(1, -4, 142, 111));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 5***/
	clip.push_back(sf::FloatRect(126, 133, 137, 397));
	hurt.push_back(sf::FloatRect(86, 241, 253, 277));
	hurt.push_back(sf::FloatRect(115, 152, 154, 213));
	hurt.push_back(sf::FloatRect(94, 87, 190, 127));
	hurt.push_back(sf::FloatRect(105, 7, 125, 117));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 6***/
	clip.push_back(sf::FloatRect(100, 138, 154, 397));
	hurt.push_back(sf::FloatRect(85, 285, 202, 238));
	hurt.push_back(sf::FloatRect(96, 97, 196, 115));
	hurt.push_back(sf::FloatRect(97, 168, 173, 191));
	hurt.push_back(sf::FloatRect(98, 9, 139, 116));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 7***/
	clip.push_back(sf::FloatRect(129, 136, 150, 398));
	hurt.push_back(sf::FloatRect(76, 293, 249, 231));
	hurt.push_back(sf::FloatRect(111, 109, 176, 221));
	hurt.push_back(sf::FloatRect(94, 8, 133, 129));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
}

void BachRoundhouse::initCancelMoves() {

}