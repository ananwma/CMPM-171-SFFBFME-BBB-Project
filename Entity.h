#pragma once
#include <SFML/Graphics.hpp>

class Entity {
public:
	Entity() = default;
	Entity(const Entity&) = delete;
	Entity(Entity&&) = delete;
	Entity& operator= (const Entity&) = delete;
	Entity& operator= (Entity&&) = delete;
	
	void setSprite(sf::Sprite);
	void setAnimSprite(sf::Sprite, int, int, int);
	void setPosition(float, float);
	void updateSide(Entity);
	void updateAnimFrame();

	enum direction { LEFT, RIGHT, NEUTRAL };


	~Entity() = default;

private:
	sf::Sprite sprite;
	float xpos;
	float ypos;

	int spriteWidth;
	int spriteHeight;
	int numAnimFrames;
	int currAnimFrame = 0;

	direction side;
	int currAnimFrame;
	int numAnimFrames;
};