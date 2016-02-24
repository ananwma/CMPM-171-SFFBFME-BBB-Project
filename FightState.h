#pragma once

#include "GameState.h"
#include "Game.h"
#include "Player.h"
#include "Collision.h"
#include "ConcertHallStage.h"
#include <SFML/Audio.hpp>

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
	virtual void receiveKeysDown(int, int);
	virtual void receiveKeysUp(int, int);
	virtual void unhookEvent();

	void processInput(Player&, vector<bool>&);

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
	sf::Clock inputClock;
	sf::Clock metronomeSoundTimer;
	sf::Clock metronome;
	bool onBeat;
	int intOnBeat;
	int beat;
	int beatThreshold;
	vector<bool> inputP1;
	vector<bool> inputP2;
	Collision collision;
	ConcertHallStage chstage;
	float frameCounter = 0, switchFrame = 100, frameSpeed = 500;
	void checkBoxes(Player&, Player&);
	void checkMoveBoxes(Player&, Player&);
	void drawBoxes(Player&, bool, bool);

	sf::SoundBuffer metronomeSoundBuffer;
	sf::Sound metronomeSound;
};
