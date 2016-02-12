#include "stdafx.h"
#include <iostream>

#include "CharacterBach.h"

using namespace std;

Bach::Bach() {
	width = 68;
	height = 105;
	walkspeed = 0.1f;
	if (!spritesheet.loadFromFile("sprites/Ryu.png")) {
		cerr << "Missing file sprites/Ryu.png!\n";
		exit(EXIT_FAILURE);
	}
	sprite.setTexture(spritesheet);

	//set sprite to initial position
	sprite.setPosition(20, 400);
}

void Bach::walk() {

}

void Bach::initMoves() {
	FrameVec frames;
	BoxVec hit, hurt;
	/*****IDLE*****/ 

		/**F1_HITBOXES**/
			hit.push_back(sf::FloatRect(10, 0, 20, 20));
			hit.push_back(sf::FloatRect(30, 0, 20, 20));
			hit.push_back(sf::FloatRect(0, 50, 20, 20));
		/**F1_HURTBOXES**/
			hurt.push_back(sf::FloatRect(0, 20, 20, 20));
			hurt.push_back(sf::FloatRect(20, 10, 30, 20));
			hurt.push_back(sf::FloatRect(30, 30, 20, 20));

		frames.push_back(Frame(hit, hurt));
		hit.clear();
		hurt.clear();

		/**F2_HITBOXES**/
			hit.push_back(sf::FloatRect(0, 0, 20, 20));
			hit.push_back(sf::FloatRect(0, 0, 20, 20));
			hit.push_back(sf::FloatRect(0, 0, 20, 20));
		/**F2_HURTBOXES**/
			hurt.push_back(sf::FloatRect(0, 0, 20, 20));
			hurt.push_back(sf::FloatRect(0, 0, 20, 20));
			hurt.push_back(sf::FloatRect(0, 0, 20, 20));

		frames.push_back(Frame(hit, hurt));
		hit.clear();
		hurt.clear();
		frames.push_back(Frame(hit, hurt));
		frames.push_back(Frame(hit, hurt));
		frames.push_back(Frame(hit, hurt));

		moveList[IDLE] = (Move(frames));
		moveList[WALK] = (Move(frames));
		moveList[JUMP] = (Move(frames));
		moveList[HITSTUN] = (Move(frames));
		moveList[JAB] = (Move(frames));
		frames.clear();
	/*****WALK*****/

}