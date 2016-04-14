#include "stdafx.h"
#include "Entity.h"

void Entity::setSprite(sf::Sprite s) {
	sprite = s;
}

void Entity::setAnimSprite(sf::Sprite s, int width, int height, int framecount) {
	sprite = s;
	spriteWidth = width;
	spriteHeight = height;
	numAnimFrames = framecount;
}

void Entity::setPosition(float x, float y) {
	sprite.setPosition(x, y);
	xpos = x;
	ypos = y;
}

void Entity::updateSide(Entity relativeTo) {
}

void Entity::updateAnimFrame() {
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
			character->sprite.setTexture(character->moveList.at(IDLE)->spritesheet);
			if (state != AIRBORNE_STATE)
				state = NO_STATE;
		}
	}*/
	if (side == LEFT) {
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
}