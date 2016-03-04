#pragma once
#include "Move.h"

class BachFierce : public Move {
public:
	BachFierce();
	virtual void initFrames();
	virtual void initCancelMoves();
};

BachFierce::BachFierce() {
	if (!spritesheet.loadFromFile("sprites/bach_fierce.png")) {
		std::cerr << "Error missing BachFierce sprites!\n";
		exit(EXIT_FAILURE);
	}
	// Number of animation frames
	frameCount = 13;
	// Damage
	damage = 100;
	// Change in attacker's position on move
	velX = 0;
	velY = 0;
	// Change in opponent's position on move
	pushX = 3;
	pushY = 0;
	//Number of hitstun frames this causes
	hitstun = 6;
	//Number of blockstun frames this causes
	blockstun = 5;
	// State move puts player in
	state = ATTACK_STATE;
}

void BachFierce::initFrames() {
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
	clip.push_back(sf::FloatRect(160, 128, 139, 397));
	hurt.push_back(sf::FloatRect(131, 306, 213, 217));
	hurt.push_back(sf::FloatRect(149, 122, 164, 204));
	hurt.push_back(sf::FloatRect(165, 15, 125, 117));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 6***/
	clip.push_back(sf::FloatRect(161, 124, 154, 397));
	hurt.push_back(sf::FloatRect(137, 278, 202, 238));
	hurt.push_back(sf::FloatRect(160, 109, 150, 191));
	hurt.push_back(sf::FloatRect(141, 11, 139, 116));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 7***/
	hurt.push_back(sf::FloatRect(196, 60, 237, 244));
	clip.push_back(sf::FloatRect(172, 116, 150, 398));
	hurt.push_back(sf::FloatRect(127, 299, 249, 231));
	hurt.push_back(sf::FloatRect(151, 111, 176, 221));
	hurt.push_back(sf::FloatRect(182, 39, 133, 129));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 8***/
	hit.push_back(sf::FloatRect(129, 52, 299, 254));
	clip.push_back(sf::FloatRect(161, 119, 137, 402));
	hurt.push_back(sf::FloatRect(94, 314, 286, 213));
	hurt.push_back(sf::FloatRect(135, 52, 289, 274));
	hurt.push_back(sf::FloatRect(152, 26, 156, 123));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 9***/
	clip.push_back(sf::FloatRect(163, 113, 156, 403));
	hurt.push_back(sf::FloatRect(111, 274, 261, 243));
	hurt.push_back(sf::FloatRect(156, 51, 270, 232));
	hurt.push_back(sf::FloatRect(144, 25, 163, 141));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 10***/
	hurt.push_back(sf::FloatRect(143, 279, 239, 244));
	hurt.push_back(sf::FloatRect(186, 11, 132, 128));
	hurt.push_back(sf::FloatRect(187, 103, 161, 223));
	clip.push_back(sf::FloatRect(189, 109, 139, 412));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 11***/
	hurt.push_back(sf::FloatRect(140, 291, 251, 235));
	hurt.push_back(sf::FloatRect(173, 112, 179, 211));
	hurt.push_back(sf::FloatRect(175, 15, 141, 170));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 12***/
	clip.push_back(sf::FloatRect(204, 103, 155, 424));
	hurt.push_back(sf::FloatRect(181, 275, 239, 252));
	hurt.push_back(sf::FloatRect(187, 108, 208, 205));
	hurt.push_back(sf::FloatRect(183, 2, 138, 170));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
	/***FRAME 13***/
	clip.push_back(sf::FloatRect(139, 110, 156, 431));
	hurt.push_back(sf::FloatRect(115, 259, 243, 274));
	hurt.push_back(sf::FloatRect(144, 104, 185, 160));
	hurt.push_back(sf::FloatRect(141, 4, 119, 115));
	frameVector.push_back(Frame(hit, hurt, clip));
	hit.clear();
	hurt.clear();
	clip.clear();
}

void BachFierce::initCancelMoves() {

}