#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
class UI
{
public:
	// CTOR and DTOR
	UI() = default;
	~UI() = default;

	// Mutators
	void setPos(float, float);
	void addDrawable(sf::Drawable&);
	void setData(int);

	// Accessors
	sf::Vector2f getPos();
	int getData();

private:
	float xpos;
	float ypos;
	sf::Sprite sprite;
	std::vector<sf::Drawable&> drawVector;
	int data;
};

