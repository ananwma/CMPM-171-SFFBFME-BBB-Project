#include "stdafx.h"
#include <iostream>
#include "ConcertHallStage.h"


ConcertHallStage::ConcertHallStage()
{
	if (!basetexture.loadFromFile("backgrounds/background.png")) {
		std::cerr << "Could not find image file!\n";
		exit(EXIT_FAILURE);
	}	
	if (!fronttexture.loadFromFile("backgrounds/front.png")) {
		std::cerr << "Could not find image file!\n";
		exit(EXIT_FAILURE);
	}
	if (!medtexture.loadFromFile("backgrounds/med.png")) {
		std::cerr << "Could not find image file!\n";
		exit(EXIT_FAILURE);
	}
	if (!shadertexture.loadFromFile("backgrounds/shader.png")) {
		std::cerr << "Could not find image file!\n";
		exit(EXIT_FAILURE);
	}
	base.setTexture(basetexture);
	med.setTexture(medtexture);
	front.setTexture(fronttexture);
	shader.setTexture(shadertexture);
	//(IMAGE_X - WINDOW_WIDTH) / 2
	window_limit = 440;
	window_offset = 440;
}


ConcertHallStage::~ConcertHallStage()
{
}
