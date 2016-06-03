#pragma once
#include <string>
#include <SFML/Audio.hpp>
struct sfx {
	sfx() = default;
	sfx(std::string filename) {
		buffer.loadFromFile(filename);
		sound.setBuffer(buffer);
	}
	void play() { sound.play(); }
	sf::SoundBuffer buffer;
	sf::Sound sound;
};
