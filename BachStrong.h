#pragma once
#include "Move.h"

class BachStrong : public Move {
public:
	BachStrong();
	virtual void initFrames();
	virtual void initCancelMoves() {};
};

BachStrong::BachStrong() {
	if (!spritesheet.loadFromFile("sprites/bach_strong.png")) {
		std::cerr << "Error missing BachStrong sprites!\n";
		exit(EXIT_FAILURE);
	}
	// Number of animation frames
	frameCount = 7;
	// Damage
	damage = 50;
	//Number of hitstun frames this causes
	hitstun = 5;
	//Number of blockstun frames this causes
	blockstun = 3;
	// Change in position on move
	// Change in opponents position
	pushX = 5;
	// State move puts player in
	state = ATTACK_STATE;

	initFrames();
}

void BachStrong::initFrames() {
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
	clip.push_back(sf::FloatRect(165, 110, 150, 401));
	hurt.push_back(sf::FloatRect(148, 17, 137, 115));
	hurt.push_back(sf::FloatRect(110, 318, 244, 201));
	hurt.push_back(sf::FloatRect(140, 105, 181, 216));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 4***/
	clip.push_back(sf::FloatRect(159, 120, 149, 401));
	hurt.push_back(sf::FloatRect(124, 305, 229, 215));
	hurt.push_back(sf::FloatRect(139, 116, 181, 196));
	hurt.push_back(sf::FloatRect(148, 18, 142, 111));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 5***/
	clip.push_back(sf::FloatRect(175, 130, 137, 397));
	hurt.push_back(sf::FloatRect(131, 306, 213, 217));
	hurt.push_back(sf::FloatRect(161, 166, 154, 213));
	hurt.push_back(sf::FloatRect(164, 82, 244, 127));
	hit.push_back(sf::FloatRect(171, 54, 242, 174));
	hurt.push_back(sf::FloatRect(165, 44, 125, 117));
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
	/***FRAME 7***/
	clip.push_back(sf::FloatRect(152, 113, 150, 398));
	hurt.push_back(sf::FloatRect(109, 291, 249, 231));
	hurt.push_back(sf::FloatRect(141, 109, 176, 221));
	hurt.push_back(sf::FloatRect(154, 20, 133, 129));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
}