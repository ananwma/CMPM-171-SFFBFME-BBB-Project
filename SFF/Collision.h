#pragma once
#include "Player.h"

class Collision
{
public:
	void flip_sprites(Player &p1, Player &p2);
	void move_right(Player &p1, Player &p2, int window_width);
	void move_left(Player &p1, Player &p2);
	Collision();
	~Collision();
};

