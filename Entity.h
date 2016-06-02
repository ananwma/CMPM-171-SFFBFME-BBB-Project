#pragma once
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define BEAT_SPEED 500.0f
#define GROUND WINDOW_WIDTH / 4

enum direction { LEFT, RIGHT, NEUTRAL };

class Entity {

public:

	Entity() = default;
	Entity(const Entity&) = delete;
	Entity(Entity&&) = delete;
	Entity& operator= (const Entity&) = delete;
	Entity& operator= (Entity&&) = delete;

	void setTexture(sf::Texture&);
	void setAnimTexture(sf::Texture&, int, int, int);
	void setPosition(float, float);
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	void updateSide(Entity&);
	int updateAnimFrame();

	void updatePhysics();

	void setSide(direction);
	direction getSide();


	~Entity() = default;

	sf::Sprite sprite;
	sf::Texture *texture;

	std::vector<sf::FloatRect> collisionVolumes;
	sf::FloatRect collisionVolume;
	void setCollisionVolume(sf::FloatRect);

protected:

	float xpos;
	float ypos;
	float xvel = 0;
	float yvel = 0;
	float xacc = 0;
	float yacc = 0;
	float gravity = 0;
	float friction = 0;

	int spriteWidth;
	int spriteHeight;
	int numAnimFrames = 1;
	int currAnimFrame = 0;
	direction side;

	friend class CollisionManager;

};