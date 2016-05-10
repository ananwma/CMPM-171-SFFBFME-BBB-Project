#pragma once
#include <Windows.h>

#include "GameState.h"
#include "Game.h"

/* State for initializng MIDI devices and assigning devices to players */

class PlayerSelectState : public GameState {
public:
	// CTOR
	explicit PlayerSelectState(Game&);

	// Main game loop functions
	virtual void init();
	virtual void update();
	virtual void draw();

	// Input and event handling
	virtual void receiveKeysDown(int, int);
	virtual void receiveKeysUp(int, int) {};
	virtual void unhookEvent();
	virtual void hookEvent();

private:
	// Reference to Game struct containing window, input handler, and game state manager
	Game &game;

	sf::Text pressAKey;
	sf::Font font;
	sf::Sprite keyboard1;
	sf::Sprite keyboard2;
	sf::Texture keyboardTex;

	// True if state is currently being ran
	bool running;

	bool p1Pressed = false;
	bool p2Pressed = false;
	float rot = 0;
	int fade1 = 255;
	int fade2 = 255;
};