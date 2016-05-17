#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class SpriteEmitter : public sf::Drawable, public sf::Transformable
{
public:
	SpriteEmitter(int count, std::string filename, int width, int height, int framecount);
	void update(sf::Time);
	void setEmitter(sf::Vector2f position);
	~SpriteEmitter();
private:
	int count;
	int width;
	int height;
	int framecount;
	sf::Texture texture;
	sf::Time maxLifetime;
	sf::Vector2f emitterPos;

	// struct to store sprite, velocity, anim data
	struct Particle {
		sf::Sprite sprite;
		sf::Vector2f velocity;
		sf::Time lifetime;
		sf::Time switchClock;
		float switchFrame;
		int currFrame = 0;
	};
	std::vector<Particle> particleVector;

	void resetParticle(Particle&);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;


};

