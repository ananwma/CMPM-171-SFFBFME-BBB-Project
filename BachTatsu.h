#pragma once
#include "Move.h"

class BachTatsu : public Move {
public:
	BachTatsu();
	virtual void initFrames();
	virtual void initCancelMoves();
};

BachTatsu::BachTatsu() {
	if (!spritesheet.loadFromFile("sprites/bach_toccata_and_kick_ur_ass_in_d_minor.png")) {
		std::cerr << "Error missing BachTatsu sprites!\n";
		exit(EXIT_FAILURE);
	}
	// Number of animation frames
	frameCount = 15;
	// Damage
	damage = 10;
	// Change in attacker's position on move
	velX = 0;
	velY = -20;
	// Change in opponent's position on move
	pushX = 0;
	pushY = 0;
	//Number of hitstun frames this causes
	hitstun = 3;
	//Number of blockstun frames this causes
	blockstun = 2;
	// State move puts player in
	state = ATTACK_STATE;

	initFrames();
}

void BachTatsu::initFrames() {
	BoxVec hit;
	BoxVec hurt;
	BoxVec clip;
	/***FRAME 1***/
	clip.push_back(sf::FloatRect(129, 117, 158, 407));
	hurt.push_back(sf::FloatRect(115, 296, 211, 227));
	hurt.push_back(sf::FloatRect(135, 99, 182, 241));
	hurt.push_back(sf::FloatRect(99, 6, 153, 132));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 2***/
	clip.push_back(sf::FloatRect(162, 106, 134, 414));
	hurt.push_back(sf::FloatRect(129, 291, 210, 231));
	hurt.push_back(sf::FloatRect(128, 97, 183, 250));
	hurt.push_back(sf::FloatRect(132, 10, 140, 105));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 3***/
	clip.push_back(sf::FloatRect(109, 128, 152, 402));
	hurt.push_back(sf::FloatRect(92, 292, 292, 244));
	hurt.push_back(sf::FloatRect(109, 99, 169, 243));
	hurt.push_back(sf::FloatRect(83, 16, 155, 172));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 4***/
	hit.push_back(sf::FloatRect(89, 297, 348, 234));
	clip.push_back(sf::FloatRect(107, 105, 142, 423));
	hurt.push_back(sf::FloatRect(47, 276, 392, 255));
	hurt.push_back(sf::FloatRect(108, 96, 160, 203));
	hurt.push_back(sf::FloatRect(69, 3, 161, 148));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 5***/
	hit.push_back(sf::FloatRect(7, 283, 348, 248));
	clip.push_back(sf::FloatRect(191, 108, 137, 426));
	hurt.push_back(sf::FloatRect(0, 238, 371, 297));
	hurt.push_back(sf::FloatRect(175, 98, 173, 184));
	hurt.push_back(sf::FloatRect(204, 8, 156, 159));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 6***/
	hit.push_back(sf::FloatRect(89, 297, 348, 234));
	clip.push_back(sf::FloatRect(107, 105, 142, 423));
	hurt.push_back(sf::FloatRect(47, 276, 392, 255));
	hurt.push_back(sf::FloatRect(108, 96, 160, 203));
	hurt.push_back(sf::FloatRect(69, 3, 161, 148));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 7***/
	hit.push_back(sf::FloatRect(7, 283, 348, 248));
	clip.push_back(sf::FloatRect(191, 108, 137, 426));
	hurt.push_back(sf::FloatRect(0, 238, 371, 297));
	hurt.push_back(sf::FloatRect(175, 98, 173, 184));
	hurt.push_back(sf::FloatRect(204, 8, 156, 159));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 8***/
	hit.push_back(sf::FloatRect(89, 297, 348, 234));
	clip.push_back(sf::FloatRect(107, 105, 142, 423));
	hurt.push_back(sf::FloatRect(47, 276, 392, 255));
	hurt.push_back(sf::FloatRect(108, 96, 160, 203));
	hurt.push_back(sf::FloatRect(69, 3, 161, 148));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 9***/
	hit.push_back(sf::FloatRect(7, 283, 348, 248));
	clip.push_back(sf::FloatRect(191, 108, 137, 426));
	hurt.push_back(sf::FloatRect(0, 238, 371, 297));
	hurt.push_back(sf::FloatRect(175, 98, 173, 184));
	hurt.push_back(sf::FloatRect(204, 8, 156, 159));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 10***/
	hit.push_back(sf::FloatRect(89, 297, 348, 234));
	clip.push_back(sf::FloatRect(107, 105, 142, 423));
	hurt.push_back(sf::FloatRect(47, 276, 392, 255));
	hurt.push_back(sf::FloatRect(108, 96, 160, 203));
	hurt.push_back(sf::FloatRect(69, 3, 161, 148));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 11***/
	hit.push_back(sf::FloatRect(7, 283, 348, 248));
	clip.push_back(sf::FloatRect(191, 108, 137, 426));
	hurt.push_back(sf::FloatRect(0, 238, 371, 297));
	hurt.push_back(sf::FloatRect(175, 98, 173, 184));
	hurt.push_back(sf::FloatRect(204, 8, 156, 159));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 12***/
	hit.push_back(sf::FloatRect(89, 297, 348, 234));
	clip.push_back(sf::FloatRect(107, 105, 142, 423));
	hurt.push_back(sf::FloatRect(47, 276, 392, 255));
	hurt.push_back(sf::FloatRect(108, 96, 160, 203));
	hurt.push_back(sf::FloatRect(69, 3, 161, 148));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 13***/
	clip.push_back(sf::FloatRect(109, 128, 152, 402));
	hurt.push_back(sf::FloatRect(92, 292, 292, 244));
	hurt.push_back(sf::FloatRect(109, 99, 169, 243));
	hurt.push_back(sf::FloatRect(83, 16, 155, 172));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 14***/
	clip.push_back(sf::FloatRect(162, 106, 134, 414));
	hurt.push_back(sf::FloatRect(129, 291, 210, 231));
	hurt.push_back(sf::FloatRect(128, 97, 183, 250));
	hurt.push_back(sf::FloatRect(132, 10, 140, 105));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 15***/
	hurt.push_back(sf::FloatRect(132, 10, 140, 105));
	clip.push_back(sf::FloatRect(129, 117, 158, 407));
	hurt.push_back(sf::FloatRect(115, 296, 211, 227));
	hurt.push_back(sf::FloatRect(135, 99, 182, 241));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
}

void BachTatsu::initCancelMoves() {

}