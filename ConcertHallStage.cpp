#include "stdafx.h"
#include <iostream>
#include "ConcertHallStage.h"


ConcertHallStage::ConcertHallStage()
{
	if (!texture.loadFromFile("backgrounds/background.png")) {
		std::cerr << "Could not find image file!\n";
		exit(EXIT_FAILURE);
	}
	sprite.setTexture(texture);
	//(IMAGE_X - WINDOW_WIDTH) / 2
	window_limit = 440;
	window_offset = 440;
}


ConcertHallStage::~ConcertHallStage()
{
}
