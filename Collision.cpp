#include "stdafx.h"
#include "Collision.h"
#include "Player.h"
#include <SFML/graphics.hpp>

Collision::Collision()
{
}

void Collision::flip_sprites(Player &p1, Player &p2) {
	/*if (p1.xpos < p2.xpos && p1.side == RIGHT) {
		p1.side = LEFT;
	}
	else if (p1.xpos > p2.xpos && p1.side == LEFT) {
		p1.side = RIGHT;
	}*/
}

//****************************************
// GETPOSITION() IS TOP LEFT NOT MIDDLE
//****************************************

void Collision::move_right(Player &p1, Player &p2, int window_width, AssetManager &current_screen) {
	/*if (((p1.character->sprite.getPosition().x + p1.getSpriteWidth()) >= (p2.character->sprite.getPosition().x)) && p1.side == RIGHT && ((p1.character->sprite.getPosition().y + p1.getSpriteHeight() / 2) >= (p2.character->sprite.getPosition().y - p2.getSpriteHeight() / 2))) {
	}
	
	else {
		if (((p1.character->sprite.getPosition().x + p1.getSpriteWidth()) >= window_width)) {
			current_screen.move_camera_right(current_screen.stage, p1, p2);
		}
		else {
			p1.character->sprite.move(2.500000f, 0);
		}
	}
	p1.character->currentMove = 1;
	p1.character->currentMoveFrame = 0;*/
}

void Collision::move_left(Player &p1, Player &p2, AssetManager &current_screen) {
	/*if (((p1.character->sprite.getPosition().x) <= (p2.character->sprite.getPosition().x + p2.getSpriteWidth())) && (p1.side == LEFT) && ((p1.character->sprite.getPosition().y + p1.getSpriteHeight() / 2) >= (p2.character->sprite.getPosition().y - p2.getSpriteHeight() / 2))) {
	}
	else {
		if (((p1.character->sprite.getPosition().x) <= 0)) {
			current_screen.move_camera_left(current_screen.stage, p1, p2);
		}
		else {
			p1.character->sprite.move(-2.5000000f, 0);
		}
	}
	p1.character->currentMove = 1;
	p1.character->currentMoveFrame = 0;*/
}
Collision::~Collision()
{
}
