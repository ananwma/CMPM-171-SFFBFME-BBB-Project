#pragma once
#include "Player.h"
#include "stdafx.h"

class CameraControl
{
public:
	void move_camera_left(Player &p1, Player &p2, int window_width, int window_offset, int window_limit);
	void move_camera_right(Player &p1, Player &p2, int window_width, int window_offset, int window_limit);
	CameraControl();
	~CameraControl();
};

