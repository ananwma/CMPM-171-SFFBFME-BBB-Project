#pragma once
#pragma once
#include "Move.h"

class BachSuper : public Move {
public:
	BachSuper();
	virtual void initFrames();
	virtual void initCancelMoves();
};

BachSuper::BachSuper() {
	if (!spritesheet.loadFromFile("sprites/bachs_big_bash.png")) {
		std::cerr << "Error missing BachSuper sprites!\n";
		exit(EXIT_FAILURE);
	}
	// Number of animation frames
	frameCount = 16;
	// Damage
	damage = 200;
	// Change in attacker's position on move
	velX = 10;
	velY = 0;
	// Change in opponent's position on move
	pushX = 20;
	pushY = 0;
	//Number of hitstun frames this causes
	hitstun = 10;
	//Number of blockstun frames this causes
	blockstun = 5;
	// State move puts player in
	state = ATTACK_STATE;
	
	initFrames();
}

void BachSuper::initFrames() {
	BoxVec hit;
	BoxVec hurt;
	BoxVec clip;
	//1-7
	clip.push_back(sf::FloatRect(139, 102, 158, 411));
	frameVector.push_back(Frame(hit, hurt, clip));
	frameVector.push_back(Frame(hit, hurt, clip));
	frameVector.push_back(Frame(hit, hurt, clip));
	frameVector.push_back(Frame(hit, hurt, clip));
	frameVector.push_back(Frame(hit, hurt, clip));
	frameVector.push_back(Frame(hit, hurt, clip));
	frameVector.push_back(Frame(hit, hurt, clip));
	/***FRAME 8***/
	hit.push_back(sf::FloatRect(4, 33, 442, 482));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	//9-12
	clip.push_back(sf::FloatRect(139, 102, 158, 411));
	frameVector.push_back(Frame(hit, hurt, clip));
	frameVector.push_back(Frame(hit, hurt, clip));
	frameVector.push_back(Frame(hit, hurt, clip));
	frameVector.push_back(Frame(hit, hurt, clip));
	/***FRAME 13***/
	hurt.push_back(sf::FloatRect(142, 22, 216, 493));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 14***/
	clip.push_back(sf::FloatRect(139, 102, 158, 411));
	hurt.push_back(sf::FloatRect(180, 13, 163, 488));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 15***/
	clip.push_back(sf::FloatRect(139, 102, 158, 411));
	hurt.push_back(sf::FloatRect(167, 3, 183, 529));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 16***/
	hurt.push_back(sf::FloatRect(153, 12, 192, 509));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
}

void BachSuper::initCancelMoves() {

}