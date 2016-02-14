#pragma once
#include <SFML/graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class AssetManager
{
public:
	vector <string> imagelist;
	vector <string> audiolist;
	float xpos;
	sf::Texture bTexture;
	sf::Sprite bImage;
	void load_images();
	void load_audio();

	AssetManager();
	~AssetManager();
};
