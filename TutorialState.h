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
#include "TutorialTask.h"
#include "TutorialStage.h"
#include <SFML/Audio.hpp>

class TutorialState : public GameState {
public:
	// CTOR
	explicit TutorialState(Game&);
	void initTutorial();
	~TutorialState();

	// Main game loop functions
	virtual void init();
	virtual void update();
	virtual void draw();

	// Input and event handling
	virtual void receiveKeysDown(int, int);
	virtual void receiveKeysUp(int, int);
	virtual void unhookEvent();
	virtual void hookEvent();

	int BARSIZE = 628;

	sf::View base_view;
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
	sf::CircleShape player_1_round_win_1;
	sf::CircleShape player_1_round_win_2;
	sf::CircleShape player_2_round_win_1;
	sf::CircleShape player_2_round_win_2;
	sf::Sprite player1portraitart;
	sf::Sprite player2portraitart;
	sf::RectangleShape pauseOverlay;
	sf::RectangleShape timer;
	sf::Sprite HUDOverlay;
	sf::Texture HUDTexture;
	sf::Vector2f camera_center;

	sf::Text timer_text;
	sf::Font font;
	float time;
	sf::RectangleShape player_1_round_wins;
	sf::RectangleShape player_2_round_wins;
	void processInput(Player&, vector<int>&);

	//tutorial stuff
	sf::RectangleShape textbox;
	sf::RectangleShape overlay;
	sf::Texture textBorderTex;
	sf::Sprite textBorder;
	sf::Texture keyboardTexSheet;
	sf::Texture keyboardTexSheet2;
	sf::Sprite keyboardIcon;
	int keyboardWidth = 861;
	int keyboardHeight = 602;
	sf::RectangleShape task;
	sf::Text task_text;
	sf::RectangleShape dialogue;
	sf::Text dialogue_text;
	//

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
	SpriteEmitter hitspark1;
	SpriteEmitter hitspark2;
	SpriteEmitter blockspark1;
	SpriteEmitter blockspark2;
	bool onBeat;
	float beat;
	int intOnBeat;
	int beatThreshold;
	int indicatorFlash;
	bool indicatorFlashOn;
	bool octave;
	bool colliding = false;
	bool acceptingInput = false;
	bool roundstart = true;

	float saveTime = 99.0f;

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
	void drawBoxes(Player&, bool, bool, bool);
	void TutorialState::reset();
	void drawHud();
	void doRoundStart();
	void doRoundEnd();
	bool roundend = false;
	sf::Texture round1;
	sf::Texture round2;
	sf::Texture KO;
	sf::Texture timeUp;
	sf::Texture player1wins;
	sf::Texture player2wins;
	sf::Texture tie;
	sf::Texture roundFinal;
	sf::Sprite roundText;
	float inc = 0;
	//UI timer;

	sf::SoundBuffer metronomeSoundBuffer;
	sf::Sound metronomeSound;
	sf::SoundBuffer hitSoundBuffer;
	sf::Sound hitSound;
	sf::SoundBuffer blockSoundBuffer;
	sf::Sound blockSound;

	sf::Text text;

	//tutorial stuff
	vector<TutorialStage> tutorial;
	int current_stage = 0;
	int current_task_num = 0;
	int dontUpdateEveryFramePlease = 0;
	//string current_task;
	string current_dialogue;
	stack <string> dialogue_stack;
	bool inPretext = true;
	bool inPosttext = false;
	bool stopState = false;
	bool waitToChangeState = false;
	//
	sf::Font font2;
	//sf::Text text;
	//	sf::Font font;
};
