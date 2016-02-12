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
	virtual void recieveKeysDown(std::list<int>&, int) = 0;

	// Can probably be defined here, most likely will be the same in all states
	virtual void unhookEvent() = 0;
};
