#pragma once
#include "Player.h"
#include "AssetManager.h"

class Collision
{
public:
	void flip_sprites(Player &p1, Player &p2);
	void move_right(Player &p1, Player &p2, int window_width, AssetManager &current_screen);
	Collision();
	void move_left(Player & p1, Player & p2, AssetManager &current_screen);
	~Collision();
};

