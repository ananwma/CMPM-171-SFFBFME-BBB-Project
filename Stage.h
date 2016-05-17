#pragma once
#include <SFML/Graphics.hpp>

class Stage
{
friend class AssetManager;
public:
	sf::Sprite base;
	sf::Sprite med;
	sf::Sprite front;
	sf::Texture basetexture;
	sf::Texture medtexture;
	sf::Texture fronttexture;
	int window_limit;
	int window_offset;
	Stage();
	~Stage();
};


