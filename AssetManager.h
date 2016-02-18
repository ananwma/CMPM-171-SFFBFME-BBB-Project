#pragma once
#include <SFML/graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "Stage.h"
#include "AssetManager.h"
#include "Player.h"

using namespace std;

class AssetManager
{
public:
	Stage stage;
	float xpos;
	sf::Texture bTexture;
	sf::Sprite bImage;
	int window_limit;
	int window_offset;

	vector <string> imagelist;
	vector <string> audiolist;

	void load_images();
	void load_audio();
	void setStage(Stage & s);
	Stage getStage();
	void AssetManager::move_camera_left(Stage &stage, Player &p1, Player &p2);
	void AssetManager::move_camera_right(Stage &stage, Player &p1, Player &p2);
	AssetManager();
	~AssetManager();
};
