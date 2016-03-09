#pragma once
#include <SFML/Graphics.hpp>

enum BeatStates { NOBEAT, NONE, LATE, EARLY, ONBEAT };

class BeatIndicator {
	friend class Player;
protected:
	int width;
	int height;

public:
	sf::Sprite bSprite;
	sf::Texture bTexture;
	BeatStates bState;
	BeatIndicator();
	void updateIndicator(BeatStates);
};


