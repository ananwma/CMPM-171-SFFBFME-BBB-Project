#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <SFML/Audio.hpp>
#include "Entity.h"
#include "Move.h"
#include "BeatIndicator.h"
#include "sfx.h"

class Player : public Entity {
private:
	//Character* character;
	float walkspeed;
	float jumpX;
	float jumpY;
	//int health;
	int walloffset;
	vector<int> super;
	unordered_map<string, Move> moveMap;
	Move* currentMove = NULL;
	unordered_map<string, shared_ptr<sfx>> sfxMap;
	sf::SoundBuffer hitSoundBuffer;
	sf::SoundBuffer blockSoundBuffer;
	sf::Sound hitSound;
	sf::Sound blockSound;

public:
	sf::Texture portrait;
	// No copy constructor
	Player(const Player&) = delete;
	BeatIndicator indicator;
	bool isMoveValid();
	//void setPosition(float, float);
	void jump(direction dir);
	bool left, jumping, right;
	direction jumpSide;
	//float xvel;
	//float yvel;
	//float xacc;
	//float yacc;

	int health;
	int maxHealth;
	float meter = 0;

	// change where this is initialized later 
	float beat = 500.0f;
	//float gravity = 0.98f * pow((500.0f / 500.0f), 2.0f);

	int hitstunFrames = 0;
	int blockstunFrames = 0;
	int roundWins = 0;
	int playerId;
	//direction side;
	State state;
	bool colliding;
	bool againstWall = false;
	bool lastMoveHit;
	int superIndex = 0;
	//sf::Texture pTexture;
	//sf::Sprite pImage;
	sf::RectangleShape hitboxes_v;
	sf::RectangleShape hurtboxes_v;
	sf::Clock superTimeout;

	//Move currentMove;

	int inputBuffer;
	bool canCancel;
	bool holdingBlock;
	// currentSprite;
	//int currentFrame;
	int ezmode = 0;

	void update();

	void doMove(string);
	void getHit(Move*);
	void playSound(string name);
	void block(Move*);
	bool moveCancelable(int, int);
	void walk(direction);
	//void updateAnimFrame();
	//void updatePhysics();
	Move* getCurrentMove();
	Frame& getCurrentFrame();
	void checkSuper(int);
	bool isInSuper();

	sf::Vector2f getRealPos();

	string getCurrentMoveName();
	int getCurrentFrameNum();
	float getSpriteHeight();
	float getSpriteWidth();
	int getMaxHealth();
	int getHealth();
	State getState();
	void setBeat(float);

	bool loadCharacter(string);
	bool collapse = false;
	Player();
	~Player();

};
