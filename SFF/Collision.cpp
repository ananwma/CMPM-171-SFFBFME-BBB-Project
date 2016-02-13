#include "stdafx.h"
#include "Collision.h"
#include "Player.h"


Collision::Collision()
{
}

void Collision::flip_sprites(Player &p1, Player &p2) {
	if ((p1.character->sprite.getPosition().x < p2.character->sprite.getPosition().x) && !p1.facing_right) {
		p1.character->sprite.scale(-1, 1);
		p1.character->sprite.move(-p1.character->width, 1);
		p2.character->sprite.scale(-1, 1);
		p2.character->sprite.move(p2.character->width, 1);
		p1.facing_right = true;
	}
	else if ((p1.character->sprite.getPosition().x > p2.character->sprite.getPosition().x) && p1.facing_right) {
		p1.character->sprite.scale(-1, 1);
		p1.character->sprite.move(p1.character->width, 1);
		p2.character->sprite.scale(-1, 1);
		p2.character->sprite.move(-p2.character->width, 1);
		p1.facing_right = false;
	}
}

void Collision::move_right(Player &p1, Player &p2, int window_width) {
	if (((p1.character->sprite.getPosition().x + p1.character->width / 2) >= (p2.character->sprite.getPosition().x - p2.character->width / 2)) && p1.facing_right && ((p1.character->sprite.getPosition().y + p1.character->height / 2) >= (p2.character->sprite.getPosition().y - p2.character->height / 2)) || ((p1.character->sprite.getPosition().x + p1.character->width / 2) >= window_width)) {
	}
	else {
		p1.character->currentMove = 1;
		p1.character->currentMoveFrame = 0;
		p1.character->sprite.move(0.500000f, 0);
	}
	p1.character->currentMove = 1;
	p1.character->currentMoveFrame = 0;
}

void Collision::move_left(Player &p1, Player &p2) {
	if (((p1.character->sprite.getPosition().x - p1.character->width / 2) <= (p2.character->sprite.getPosition().x + p2.character->width / 2)) && !p1.facing_right && ((p1.character->sprite.getPosition().y + p1.character->height / 2) >= (p2.character->sprite.getPosition().y - p2.character->height / 2)) || ((p1.character->sprite.getPosition().x - p1.character->width / 2) <= 0)) {
	}
	else {
		p1.character->currentMove = 1;
		p1.character->sprite.move(-0.5000000f, 0);
		p1.character->currentMoveFrame = 0;
	}
	p1.character->currentMove = 1;
	p1.character->currentMoveFrame = 0;
}
Collision::~Collision()
{
}
