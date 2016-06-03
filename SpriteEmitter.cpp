#include "stdafx.h"
#include "SpriteEmitter.h"

SpriteEmitter::SpriteEmitter(int _count, std::string filename, int _width, int _height, int _framecount, int _alpha) : 
	count(_count), 
	width(_width),
	height(_height),
	framecount(_framecount),
	alpha(_alpha),
	maxLifetime(sf::seconds(3))
{
	texture.loadFromFile(filename);
	for (int x = 0; x < count; x++) {
		Particle p;
		p.sprite.setTexture(texture);
		p.sprite.scale(2, 2);
		particleVector.push_back(p);
	}
}

void SpriteEmitter::update(sf::Time elapsed) {
	for (auto &particle : particleVector) {
		// update the particle lifetime
		particle.lifetime -= elapsed;

		// if the particle is dead, respawn it
		if (particle.lifetime <= sf::Time::Zero)
			resetParticle(particle);

		// update the position of the corresponding vertex
		particle.sprite.move(particle.velocity);

		// update the alpha (transparency) of the particle according to its lifetime
		float ratio = (particle.lifetime.asSeconds() + alpha) / maxLifetime.asSeconds();
		particle.sprite.setColor(sf::Color(255, 255, 255, ratio * 255));

		// update anim frame based on lifetime
		if (particle.switchClock.asSeconds() > particle.switchFrame) {
			particle.switchClock = sf::Time::Zero;
			++particle.currFrame %= framecount;
		}
		particle.switchClock += elapsed;
		particle.sprite.setTextureRect(sf::IntRect(width * particle.currFrame, 0, width, height));
	}
}

void SpriteEmitter::resetParticle(Particle& particle) {
	// give a random velocity and lifetime to the particle
	float angle = (std::rand() % 360) * 3.14f / 180.f;
	float speed = 0.1f;//(std::rand() % 3) + 1.f;
	particle.velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
	particle.lifetime = sf::milliseconds((std::rand() % 700));

	// reset anim data
	particle.switchFrame = particle.lifetime.asSeconds() / framecount;
	particle.currFrame = 0;

	particle.sprite.setPosition(emitterPos);
	if (!continuous)
		particle.active = false;
}

void SpriteEmitter::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// draw particles
	for (auto &particle : particleVector) {
		if (particle.active) 
			target.draw(particle.sprite);
	}
}

void SpriteEmitter::setEmitter(sf::Vector2f position) {
	emitterPos = position;
	if (!continuous)
		for (auto &particle : particleVector) 
			particle.sprite.setPosition(emitterPos);
}

void SpriteEmitter::setContinuous(bool set) {
	continuous = set;
}

void SpriteEmitter::activate() {
	for (auto &particle : particleVector) {
		particle.active = true;
	}
}


SpriteEmitter::~SpriteEmitter()
{
}
