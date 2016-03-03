#include "stdafx.h"
#include "Character.h"
#include "Player.h"
#define WALL_WIDTH 1280
#define INIT_XPOS 20
#define INIT_YPOS 400
#define GRAVITY 0.98f
#define GROUND 100


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
	hitstunFrames = 0;
	meter = 1000.0f;
	xpos = INIT_XPOS;
	ypos = INIT_YPOS;
	xvel = 0.0f;
	yvel = 0.0f;
	xacc = 0.0f;
	yacc = 0.0f;
	// Gravity
	//yacc = 1.0f;
	state = NO_STATE;
	colliding = false;
	canCancel = false;
	lastMoveHit = false;
	left = false;
	jumping = false;
	holdingBlock = false;
	right = false;
}

void Player::setCharacter(Character* c) {
	character = c;
	health = character->health;
	side = LEFT;
}

void Player::setPosition(float x, float y) {
	character->sprite.setPosition(x, y);
	xpos = x;
	ypos = y;
	//updateBoxes(x, y);
}

void Player::doMove(int move) {
	if (state != ATTACK_STATE && state != BLOCKSTUN_STATE && state != HITSTUN_STATE && state != AIRBORNE_STATE) {
		if (state == WALK_STATE)
			xvel = 0;
		if (move == IDLE)
			xvel = 0;
		character->currentMove = move;
		getCurrentMove()->setHitFalse();
		character->sprite.setTexture(character->moveList.at(move)->spritesheet);
		character->currentMoveFrame = 0;
		state = getCurrentMove()->state;
		yvel = getCurrentMove()->velY;
	}
	else if (state == ATTACK_STATE && canCancel && moveCancelable(character->currentMove, move)) {
		character->currentMove = move;
		character->sprite.setTexture(character->moveList.at(move)->spritesheet);
		character->currentMoveFrame = 0;
		state = getCurrentMove()->state;
	}
}

void Player::getHit(Move *move) {
	//if (state != BLOCKING) {
	character->currentMove = HITSTUN;
	character->currentMoveFrame = 0;
	hitstunFrames = move->hitstun;
	character->sprite.setTexture(character->moveList.at(HITSTUN)->spritesheet);
	state = HITSTUN_STATE;
	health -= move->damage;
	int direction;
	if (side == RIGHT) {
		direction = 1;
	}
	else {
		direction = -1;
	}
	xvel = move->pushX*direction;
	yvel = move->pushY;
	if (yvel < 0 || ypos < GROUND) state = AIRBORNE_STATE;
	//}
	/*else {
		character->currentMove = BLOCKSTUN;
		character->currentMoveFrame = 0;
		character->sprite.setTexture(character->moveList.at(BLOCKSTUN)->spritesheet);
		state = BLOCKSTUN_STATE;
		health -= move->damage;
	}*/
}

void Player::block(Move *move) {
	//if (state != BLOCKING) {
	character->currentMove = BLOCK;
	character->currentMoveFrame = 0;
	blockstunFrames = move->blockstun;
	character->sprite.setTexture(character->moveList.at(BLOCK)->spritesheet);
	state = BLOCKSTUN_STATE;
	//health -= move->damage;
	int direction;
	if (side == RIGHT) {
		direction = 1;
	}
	else {
		direction = -1;
	}
	xvel = move->pushX*direction;
	//yvel = move->pushY;
	if (yvel < 0 || ypos < GROUND) state = AIRBORNE_STATE;
	//}
	/*else {
	character->currentMove = BLOCKSTUN;
	character->currentMoveFrame = 0;
	character->sprite.setTexture(character->moveList.at(BLOCKSTUN)->spritesheet);
	state = BLOCKSTUN_STATE;
	health -= move->damage;
	}*/
}

bool Player::moveCancelable(int currMove, int newMove) {
	for (int i = 0; i < character->moveList.at(currMove)->cancelMoves.size(); i++) {
		if (newMove == character->moveList.at(currMove)->cancelMoves.at(i)) {
			return true;
		}
	}
	return false;
}

void Player::walk(direction dir) {
	// will need to add more later for figuring out which side player is on
	if (state != ATTACK_STATE && state != BLOCKSTUN_STATE && state != HITSTUN_STATE && state != AIRBORNE_STATE) {
		character->currentMove = WALK;
		character->sprite.setTexture(character->moveList.at(WALK)->spritesheet);
		state = WALK_STATE;
		if (dir == LEFT) {
			//character->sprite.move(character->walkspeed, 0);
			//xpos += character->walkspeed;
			if (!(character->sprite.getPosition().x + character->wall_offset <= -200)) {
				xvel = -character->walkspeed;
			}
		}
		else if (dir == RIGHT) {
			//character->sprite.move(-character->walkspeed, 0);
			//xpos -= character->walkspeed;
			if (!(character->sprite.getPosition().x + character->width - character->wall_offset >= WALL_WIDTH + 200)) {
				xvel = character->walkspeed;
			}
		}
	}
}

void Player::jump(direction dir) {
	if (state != ATTACK_STATE && state != BLOCKSTUN_STATE && state != HITSTUN_STATE && state != AIRBORNE_STATE) {
		character->currentMove = WALK;
		character->sprite.setTexture(character->moveList.at(WALK)->spritesheet);
		state = AIRBORNE_STATE;
		if (dir == RIGHT) {
			yvel = -character->jumpY;
			xvel = character->jumpX;
		}
		if (dir == LEFT) {
			yvel = -character->jumpY;
			xvel = -character->jumpX;
		}
		if (dir == NEUTRAL) {
			yvel = -character->jumpY;
		}
	}
}

void Player::updateAnimFrame() {
	character->currentMoveFrame++;
	int animFrames = ((getCurrentMove()->getFrameCount()) - 1);
	if (getCurrentFrameNum() > animFrames) {

		if (state == HITSTUN_STATE && hitstunFrames != 0) {
			character->currentMoveFrame = animFrames;
			hitstunFrames -= 1;
		}
		else if (state == BLOCKSTUN_STATE && blockstunFrames != 0) {
			character->currentMoveFrame = animFrames;
			blockstunFrames -= 1;
		}
		else if (state == WALK_STATE || state == NO_STATE) {
			character->currentMoveFrame = 0;
		}
		else if (state == NO_STATE || state == ATTACK_STATE || state == HITSTUN_STATE || state == AIRBORNE_STATE || state == BLOCKSTUN_STATE) {
			character->currentMoveFrame = 0;
			character->currentMove = IDLE;
			canCancel = false;
			getCurrentFrame().hit = false;
			character->sprite.setTexture(character->moveList.at(IDLE)->spritesheet);
			if (state != AIRBORNE_STATE)
				state = NO_STATE;
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
	//Add acceleration to velocity
	xvel += xacc;
	yvel += yacc;
	//Update positions based on velocity
	xpos += xvel;
	ypos += yvel;
	//Add gravitational acceleration if AIRBORNE_STATE
	if (ypos < GROUND) {
		yvel += GRAVITY;
		if (ypos + yvel > GROUND) {
			ypos = GROUND;
			yvel = 0.0f;
			xvel = 0.0f;
			state = NO_STATE;
		}
	}


	/*if (ypos >= 100) {
		ypos = 100;
		yvel = 0;
		if (state == AIRBORNE_STATE) {
			state = NO_STATE;
			xvel = 0;
		}
		xvel = 0;
		// dont go below ground
		character->sprite.setPosition(xpos, 100);
	}
	else
		state = AIRBORNE_STATE;*/

	if (((character->sprite.getPosition().x + character->wall_offset <= 0) || (character->sprite.getPosition().x + character->width - character->wall_offset >= WALL_WIDTH)) && state == AIRBORNE_STATE) {
		xvel = 0;
	}
	character->sprite.setPosition(xpos, ypos);
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
