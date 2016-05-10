#pragma once
#include <Windows.h>

#include "GameState.h"
#include "Game.h"

/* State for initializng MIDI devices and assigning devices to players */

class MainMenuState : public GameState {
public:
	// CTOR
	explicit MainMenuState(Game&);

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

	sf::Text versus;
	sf::Text tutorial;
	sf::Text options;
	sf::Font font;
	sf::Text loadingText;
	sf::RectangleShape rect1;
	sf::RectangleShape rect2;
	sf::RectangleShape rect3;
	float versusPos;
	float tutorialPos;
	float optionsPos;
	float Cpos;
	float Epos;
	float Gpos;

	sf::Sprite C;
	sf::Sprite E;
	sf::Sprite G;
	sf::Texture Ctex;
	sf::Texture Etex;
	sf::Texture Gtex;

	bool versusSelect = false;
	bool tutorialSelect = false;



	// True if state is currently being ran
	bool running;
};