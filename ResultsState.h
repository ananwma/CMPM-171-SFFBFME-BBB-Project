#pragma once
#include <Windows.h>

#include "GameState.h"
#include "Game.h"

class ResultsState : public GameState {
public:
	// CTOR
	explicit ResultsState(Game&);

	// Main game loop functions
	virtual void init();
	virtual void update();
	virtual void draw();

	// Input and event handling
	virtual void receiveKeysDown(int, int);
	virtual void receiveKeysUp(int, int) {};
	virtual void unhookEvent();

private:
	// Reference to Game struct containing window, input handler, and game state manager
	Game &game;

	// True if state is currently being ran
	bool running;

	sf::Text text;
	sf::Font font;
};