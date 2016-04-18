#pragma once
#include "GameState.h"
#include "Game.h"
#include "Player.h"
#include "Collision.h"
#include "BeatIndicator.h"
#include "ConcertHallStage.h"
#include "Bassline.h"
#include "TutorialStage.h"
#include <SFML/Audio.hpp>
#include <string>

class TutorialState : public GameState {
public:
	// CTOR
	explicit TutorialState(Game&);
	~TutorialState();

	// Main game loop functions
	virtual void init();
	virtual void update();
	virtual void draw();

	// Input and event handling
	virtual void receiveKeysDown(int, int);
	virtual void receiveKeysUp(int, int);
	virtual void unhookEvent();

	sf::View camera_view;
	sf::View HUD;
	sf::RectangleShape player_1_HP;
	sf::RectangleShape player_2_HP;
	sf::RectangleShape player_1_meter;
	sf::RectangleShape player_2_meter;
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
	bool onBeat;
	float beat;
	int intOnBeat;
	int beatThreshold;
	int indicatorFlash;
	bool indicatorFlashOn;
	bool octave;
	bool colliding = false;

	vector<TutorialStage> tutorial;
	int current_stage;
	string current_dialogue;
	bool inDialogue = false;
	bool checkMovedLeft(Player&);
	bool checkMovedRight(Player&);
	bool checkJumped(Player&);
	bool checkBlocked(Player&);
	bool checkAttacked(Player&);
	bool checkAttackedOnBeat(Player&);
	bool checkSpecial(Player&);
	bool checkSuper(Player&);
	bool checkGrabbed(Player&);
	stack <string> stage1_pre;
	stack <string> stage1_post;
	vector <TutorialTask> stage1_tasks;
	stack <string> stage2_pre;
	stack <string> stage2_pre;
	vector <TutorialTask> stage2_tasks;
	stack <string> stage3_pre;
	stack <string> stage3_pre;
	vector <TutorialTask> stage3_tasks;
	stack <string> stage4_pre;
	stack <string> stage4_pre;
	vector <TutorialTask> stage4_tasks;
	stack <string> stage5_pre;
	stack <string> stage5_pre;
	vector <TutorialTask> stage5_tasks;

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
	void TutorialState::move_camera(Player&, Player&);
	void TutorialState::restrict_movement(Player&, Player&);

	sf::SoundBuffer metronomeSoundBuffer;
	sf::Sound metronomeSound;
	sf::SoundBuffer hitSoundBuffer;
	sf::Sound hitSound;
	sf::SoundBuffer blockSoundBuffer;
	sf::Sound blockSound;
};
