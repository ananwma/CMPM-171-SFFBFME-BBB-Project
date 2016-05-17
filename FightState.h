#pragma once

#include "GameState.h"
#include "Game.h"
#include "Player.h"
#include "Collision.h"
#include "BeatIndicator.h"
#include "ConcertHallStage.h"
#include "Bassline.h"
#include "UI.h"
#include "SpriteEmitter.h"
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
	virtual void hookEvent();

	sf::View camera_view;
	sf::View HUD;
	sf::RectangleShape player_1_HP;
	sf::RectangleShape player_2_HP;
	sf::RectangleShape player_1_meter;
	sf::RectangleShape player_2_meter;	
	sf::RectangleShape player_1_HP_box;
	sf::RectangleShape player_2_HP_box;
	sf::RectangleShape player_1_meter_box;
	sf::RectangleShape player_2_meter_box;
	sf::RectangleShape player_1_round_win_1;
	sf::RectangleShape player_1_round_win_2;
	sf::RectangleShape player_2_round_win_1;
	sf::RectangleShape player_2_round_win_2;
	sf::RectangleShape pauseOverlay;
	sf::RectangleShape timer;
	sf::Text timer_text;
	sf::Font font;
	float time;
	sf::RectangleShape player_1_round_wins;
	sf::RectangleShape player_2_round_wins;
	void processInput(Player&, vector<int>&);

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
	sf::Clock metronome;
	sf::Clock emitterClock;
	SpriteEmitter dust1;
	SpriteEmitter dust2;
	bool onBeat;
	float beat;
	int intOnBeat;
	int beatThreshold;
	int indicatorFlash;
	bool indicatorFlashOn;
	bool octave;
	bool colliding = false;

	float saveTime = 60.0f;

	bool played;
	Bassline bassline;
	bool quarterNote = true;
	int phase = 0;
	vector<int> inputP1;
	vector<int> inputP2;
	vector<int> inputBuffer;
	sf::Clock inputClock;
	bool inputOpen = false;
	Collision collision;
	ConcertHallStage chstage;
	// Should fine tune these numbers at some point
	float frameCounter = 0, switchFrame = 60, frameSpeed = 1000 * (500 / BEAT_SPEED);
	void checkBoxes(Player&, Player&);
	void checkClipBoxes(Player&, Player&);
	void drawBoxes(Player&, bool, bool, bool);
	void FightState::move_camera(Player&, Player&);
	void FightState::restrict_movement(Player&, Player&);
	void FightState::reset();
	void drawHud();
	//UI timer;

	sf::SoundBuffer metronomeSoundBuffer;
	sf::Sound metronomeSound;
	sf::SoundBuffer hitSoundBuffer;
	sf::Sound hitSound;
	sf::SoundBuffer blockSoundBuffer;
	sf::Sound blockSound;

	sf::Text text;
	//sf::Font font;
	//sf::Text text;
//	sf::Font font;
};
