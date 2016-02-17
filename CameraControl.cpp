#include "stdafx.h"
#include "CameraControl.h"
#include "Player.h"


CameraControl::CameraControl()
{
}

void move_camera_left(Player &p1, Player &p2, int window_width, int window_offset, int window_limit) {
	if (p1.side == RIGHT && p1.character->sprite.getPosition().x == 0 && p1.character->sprite.getPosition().x == window_width && window_offset >= -window_limit) {
		
	}
}
void move_camera_right(Player &p1, Player &p2, int window_width, int window_offset, int window_limit) {
	if (p1.side == LEFT && p1.character->sprite.getPosition().x == 0 && p1.character->sprite.getPosition().x == window_width) {

	}
}

CameraControl::~CameraControl()
{
}
