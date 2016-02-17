#pragma once
#include <SFML/Graphics.hpp>

class Stage
{
friend class AssetManager;
public:
	sf::Sprite sprite;
	sf::Texture texture;
	int window_limit;
	int window_offset;
	Stage();
	~Stage();
};


