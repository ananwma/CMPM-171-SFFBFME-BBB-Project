#pragma once
#include <SFML\Graphics.hpp>
class UI
{
public:
	// CTOR and DTOR
	UI(float, float, sf::Sprite);
	~UI() = default;

	// Mutators
	void setPos(float, float);
	void setSprite(sf::Sprite);
	void setData(int);

	// Accessors
	sf::Vector2f getPos();
	int getData();

private:
	float xpos;
	float ypos;
	std::vector<sf::Drawable> drawables;
	int data;
};

