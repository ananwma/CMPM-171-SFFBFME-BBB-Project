#pragma once
#include <list>
#include <SFML/Graphics.hpp>

// Abstract base class to make gamestates from
[event_receiver(native)]
class GameState {
public:

	// To be implemented in various state classes
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void receiveKeysDown(int, int) = 0;
	virtual void receiveKeysUp(int, int) = 0;

	// Both can probably be defined/generalized here
	virtual void unhookEvent() = 0;
	virtual void hookEvent() = 0;
};
