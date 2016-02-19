#include "stdafx.h"
#include <iostream>
#include "ConcertHallStage.h"


ConcertHallStage::ConcertHallStage()
{
	if (!texture.loadFromFile("cute_image.jpg")) {
		//exit(EXIT_FAILURE);
	}
	sprite.setTexture(texture);
	window_limit = 200;
	window_offset = 0;
}


ConcertHallStage::~ConcertHallStage()
{
}
