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
	frameCount = 5;
	// Damage
	damage = 20;
	//Number of hitstun frames this causes
	hitstun = 6;
	//Number of blockstun frames this causes
	blockstun = 1;
	// Change in position on move
	// Change in opponents position
	
	pushX = 2;
	// State move puts player in
	state = ATTACK_STATE;
}

void BachJab::initFrames() {
	BoxVec hit;
	BoxVec hurt;
	BoxVec clip;
	/***FRAME 1***/
	clip.push_back(sf::FloatRect(139, 102, 158, 411));
	hurt.push_back(sf::FloatRect(139, 289, 223, 239));
	hurt.push_back(sf::FloatRect(125, 3, 226, 292));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 2***/
	hit.push_back(sf::FloatRect(172, 97, 197, 108));
	clip.push_back(sf::FloatRect(130, 98, 175, 394));
	hurt.push_back(sf::FloatRect(108, 296, 253, 223));
	hurt.push_back(sf::FloatRect(114, 9, 247, 288));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 3***/
	clip.push_back(sf::FloatRect(125, 111, 161, 408));
	hurt.push_back(sf::FloatRect(171, 53, 259, 227));
	hit.push_back(sf::FloatRect(162, 75, 273, 114));
	hurt.push_back(sf::FloatRect(110, 277, 235, 246));
	hurt.push_back(sf::FloatRect(78, 17, 173, 280));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 4***/
	clip.push_back(sf::FloatRect(138, 108, 166, 405));
	hurt.push_back(sf::FloatRect(114, 307, 242, 176));
	hurt.push_back(sf::FloatRect(154, 181, 166, 173));
	hurt.push_back(sf::FloatRect(108, 12, 196, 243));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	/***FRAME 4***/
	hurt.push_back(sf::FloatRect(139, 289, 223, 239));
	hurt.push_back(sf::FloatRect(125, 3, 226, 292));
	frameVector.push_back(Frame(hit, hurt));
	hit.clear();
	hurt.clear();
	/***FRAME 5***/
	hurt.push_back(sf::FloatRect(108, 296, 253, 223));
	hurt.push_back(sf::FloatRect(114, 9, 247, 288));
	frameVector.push_back(Frame(hit, hurt));
	hit.clear();
	hurt.clear();
	clip.clear();
}

void BachJab::initCancelMoves() {
	cancelMoves.push_back(JAB);
	cancelMoves.push_back(STRONG);

}