#pragma once
#include <Windows.h>

#include "GameState.h"
#include "Game.h"

class PauseState : public GameState {
public:
	// CTOR
	explicit PauseState(Game&);

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

	sf::RectangleShape window;
	sf::Font font1, font2;
	sf::Text pauseText, resumeText, menuText, restartText;
	sf::Sprite C;
	sf::Sprite E;
	sf::Sprite G;
	sf::Texture Ctex;
	sf::Texture Etex;
	sf::Texture Gtex;

	bool resume = false;
	bool menu = false;
	bool restart = false;

	// True if state is currently being ran
	bool running;
};