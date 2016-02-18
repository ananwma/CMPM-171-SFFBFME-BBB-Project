#pragma once

#include "GameState.h"
#include "Game.h"
#include "Player.h"
#include "Collision.h"
#include "AssetManager.h"
#include "ConcertHallStage.h"

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
	virtual void recieveKeysDown(std::list<int> &notes, int);
	void recieveKeysUp(std::list<int> &notes, int);
	virtual void unhookEvent();

private:
	// Reference to Game struct containing window, input handler, and game state manager
	Game &game;

	// True if state is currently being ran
	bool running;

	ConcertHallStage chstage;
	AssetManager *am;
	Collision *collision;
	int player1start_x;
	int player1start_y;	
	bool jumping;
	bool falling;
	bool walking;
	bool facing_right;
	int spriteWidth;
	int spriteHeight;
	Player *player1;
	Player *player2;
	sf::Clock clock;
	float frameCounter = 0, switchFrame = 100, frameSpeed = 500;

	void drawBoxes(Player, bool, bool);
};
