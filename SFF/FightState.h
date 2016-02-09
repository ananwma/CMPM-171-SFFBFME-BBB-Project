#pragma once

#include "GameState.h"
#include "Game.h"
#include "Player.h"

class FightState : public GameState {
public:
	// CTOR
	explicit FightState(Game&);
	~FightState();

	// Main game loop functions
	virtual void init();
	virtual void update();
	virtual void draw();

	// Input and event handling
	virtual void recieveKeysDown(std::list<int> &notes);
	virtual void unhookEvent();

private:
	// Reference to Game struct containing window, input handler, and game state manager
	Game &game;

	// True if state is currently being ran
	bool running;

	int player1start_x;
	int player1start_y;
	int spriteWidth;
	int spriteHeight;
	Player *player1;
	sf::Clock clock;
	float frameCounter = 0, switchFrame = 100, frameSpeed = 500;
};
