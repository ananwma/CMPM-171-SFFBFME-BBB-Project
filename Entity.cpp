#include "stdafx.h"
#include <iostream>
#include "Entity.h"

void Entity::setTexture(sf::Texture &_texture) {
	texture = &_texture;
	sprite.setTexture(*texture);
}

void Entity::setAnimTexture(sf::Texture &_texture, int width, int height, int framecount) {
	texture = &_texture;
	spriteWidth = width;
	spriteHeight = height;
	numAnimFrames = framecount;
	currAnimFrame = 0;
}

void Entity::setPosition(float x, float y) {
	sprite.setPosition(x, y);
	xpos = x;
	ypos = y;
}

void Entity::updateSide(Entity &relativeTo) {
	if (xpos < relativeTo.xpos)
		side = LEFT;
	else
		side = RIGHT;
} 

int Entity::updateAnimFrame() {
	//MOVE TO PLAYER
	/*int animFrames = ((getCurrentMove()->getFrameCount()) - 1);
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
			character->sprite->setTexture(character->moveList.at(IDLE)->spritesheet);
			if (state != AIRBORNE_STATE)
				state = NO_STATE;
		}
	}*/
	sprite.setTexture(*texture);
	if (side == LEFT) {
		std::cout << currAnimFrame << std::endl;
		sprite.setTextureRect(sf::IntRect(
			currAnimFrame * spriteWidth,
			0,
			spriteWidth,
			spriteHeight
			));
	}
	// Draw flipped
	else if (side == RIGHT) {
		sprite.setTextureRect(sf::IntRect(
			(currAnimFrame * spriteWidth) + spriteWidth,
			0,
			-spriteWidth,
			spriteHeight
			));
	}
	//++currAnimFrame;

	++currAnimFrame %= numAnimFrames;
	return currAnimFrame;
}

void Entity::updatePhysics() {

	//Add acceleration to velocity
	xvel += xacc;
	yvel += yacc;

	//Update positions based on velocity
	xpos += xvel;
	ypos += yvel;

	//Add gravitational acceleration if above ground
	if (ypos < GROUND) {
		yvel += gravity;
	} 

	if (ypos + yvel > GROUND) {
		ypos = GROUND;
		yvel = 0.0f;
		xvel = 0.0f;
		//if (state != ATTACK_STATE)
		//	state = NO_STATE;
	}
	//if (((character->sprite->getPosition().x + character->wall_offset <= 0) || (character->sprite->getPosition().x + character->width - character->wall_offset >= WALL_WIDTH)) && state == AIRBORNE_STATE) {
	//if((xpos <= 0)||(xpos >= 1280)){
	//	xvel = 0;
	//}
	setPosition(xpos, ypos);
}

void Entity::setSide(direction _side) {
	side = _side;
}  