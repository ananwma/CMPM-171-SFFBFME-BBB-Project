#include "stdafx.h"
#include "Character.h"
#include "Player.h"

#define INIT_XPOS 20
#define INIT_YPOS 400


Player::Player()
{
	/*if (!pTexture.loadFromFile(character->spritesheet))
		std::cout << "Error could not load player image" << std::endl;
	pImage.setTexture(pTexture);
	health = 100;
	meter = 0;
	roundWins = 0;
	canCancel = false;*/
	playerId = -1;
	//currentMoveFrame = 0;
	//x = start_x;
	//y = start_y;
	xpos = INIT_XPOS;
	ypos = INIT_YPOS;
}

void Player::setCharacter(Character* c) {
	character = c;
}

void Player::doMove(int move) {
	character->currentMove = move;
	character->currentMoveFrame = 0;
}

void Player::walk(direction dir) {
	// will need to add more later for figuring out which side player is on
	character->currentMove = WALK;
	if (dir == FORWARDS) {
		character->sprite.move(character->walkspeed, 0);
		xpos += character->walkspeed;
	}
	else if (dir == BACKWARDS) {
		character->sprite.move(character->walkspeed *-1, 0);
		xpos += character->walkspeed;
	}
}

void Player::updateAnimFrame() {
	character->currentMoveFrame++;
	int animFrames = ((getCurrentMove().frames.size()) - 1);
	if (getCurrentFrameNum() > animFrames) {
		character->currentMoveFrame = 0;
	}

	character->sprite.setTextureRect(sf::IntRect(
		getCurrentFrameNum() * character->width, 
		getCurrentMoveNum() * character->height, 
		character->width, 
		character->height
	));
}

int Player::getCurrentMoveNum() {
	return character->currentMove;
}

int Player::getCurrentFrameNum() {
	return character->currentMoveFrame;
}


Move Player::getCurrentMove() {
	return character->moveList.at(character->currentMove);
}

Frame Player::getCurrentFrame() {
	return getCurrentMove().frames.at(character->currentMoveFrame);
}



Player::~Player()
{
}
