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
	window_limit = 200;
	window_offset = 200;
}


ConcertHallStage::~ConcertHallStage()
{
}
