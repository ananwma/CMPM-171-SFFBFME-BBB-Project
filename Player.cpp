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
	xvel = 0.0f;
	yvel = 0.0f;
	xacc = 0.0f;
	// Gravity
	yacc = 0.098f;
	state = NONE;
	colliding = false;
}

void Player::setCharacter(Character* c) {
	character = c;
	side = LEFT;
}

void Player::setPosition(float x, float y) {
	character->sprite.setPosition(x, y);
	xpos = x;
	ypos = y;
	//updateBoxes(x, y);
}

void Player::doMove(int move) {
	if (state != ATTACKING && state != HITSTUN_STATE) {
		character->currentMove = move;
		character->sprite.setTexture(character->moveList.at(move)->spritesheet);
		character->currentMoveFrame = 0;
		state = getCurrentMove()->state;
	}
}

void Player::walk(direction dir) {
	// will need to add more later for figuring out which side player is on
	if (state != ATTACKING && state != HITSTUN_STATE && state != AIRBORNE) {
		character->currentMove = WALK;
		character->sprite.setTexture(character->moveList.at(WALK)->spritesheet);
		if (dir == LEFT) {
			//character->sprite.move(character->walkspeed, 0);
			//xpos += character->walkspeed;
			xvel = character->walkspeed;
		}
		else if (dir == RIGHT) {
			//character->sprite.move(-character->walkspeed, 0);
			//xpos -= character->walkspeed;
			xvel = -character->walkspeed;
		}
	}
}

void Player::jump(direction dir) {
	if (state != ATTACKING && state != HITSTUN_STATE && state != AIRBORNE) {
		character->currentMove = WALK;
		character->sprite.setTexture(character->moveList.at(WALK)->spritesheet);
		state = AIRBORNE;
		if (dir == LEFT) {
			yvel = -10.5f;
			xvel = 2.5;
		}
		if (dir == RIGHT) {
			yvel = -10.5f;
			xvel = -2.5;
		}
		if (dir == NEUTRAL) {
			yvel = -10.5f;
		}
	}
}

void Player::updateAnimFrame() {
	character->currentMoveFrame++;
	int animFrames = ((getCurrentMove()->getFrameCount()) - 1);
	if (getCurrentFrameNum() > animFrames) {
		character->currentMoveFrame = 0;
		if (state == ATTACKING || state == HITSTUN_STATE || state == AIRBORNE) {
			character->currentMove = IDLE;
			character->sprite.setTexture(character->moveList.at(IDLE)->spritesheet);
			state = NONE;
		}
	}
	if (side == LEFT) {
		character->sprite.setTextureRect(sf::IntRect(
			getCurrentFrameNum() * character->width,
			0,
			character->width,
			character->height
			));
	}
	// Draw flipped
	else if (side == RIGHT) {
		character->sprite.setTextureRect(sf::IntRect(
			(getCurrentFrameNum() * character->width) + character->width,
			0,
			-character->width,
			character->height
			));
	}
}

void Player::updatePhysics() {
	xpos += xvel;
	ypos += yvel;
	xvel += xacc;
	yvel += yacc;

	// If on ground
	if (ypos >= 100) {
		ypos = 100;
		yvel = 0;
		if (state == AIRBORNE) {
			state = NONE;
			xvel = 0;
		}
		xvel = 0;
		// dont go below ground
		character->sprite.setPosition(xpos, 100);
	}
	else
		state = AIRBORNE;

	character->sprite.move(xvel, yvel);
}

int Player::getCurrentMoveNum() {
	return character->currentMove;
}

int Player::getCurrentFrameNum() {
	return character->currentMoveFrame;
}


Move* Player::getCurrentMove() {
	return character->moveList.at(character->currentMove);
}

Frame& Player::getCurrentFrame() {
	return getCurrentMove()->frameVector.at(character->currentMoveFrame);
}

float Player::getSpriteWidth() {
	return character->width;
}
float Player::getSpriteHeight() {
	return character->height;
}

Player::~Player()
{
}
