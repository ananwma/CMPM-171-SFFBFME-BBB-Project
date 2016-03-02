#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "Character.h"
#include "Move.h"

using namespace std;
enum direction { LEFT, RIGHT, NEUTRAL };

class Player {
private:
	//Character* character;
public:
	// No copy constructor
	Player(const Player&) = delete;
	Character* character;
	bool isMoveValid();
	void setCharacter(Character*);
	void setPosition(float, float);
	void jump(direction dir);
	bool left, jumping, right;
	float xpos;
	float ypos;
	float xvel;
	float yvel;
	float xacc;
	float yacc;

	//Need to keep track of where the player has moved to update hitboxes
	float deltaX;
	float deltaY;
	float health;
	float meter;
	int hitstunFrames;
	int roundWins;
	int playerId;
	direction side;
	state state;
	bool colliding;
	bool lastMoveHit;
	sf::Texture pTexture;
	sf::Sprite pImage;
	sf::RectangleShape hitboxes_v;
	sf::RectangleShape hurtboxes_v;

	//Move currentMove;
	
	int inputBuffer;
	bool canCancel;
	// currentSprite;
	//int currentFrame;

	void doMove(int);
	void getHit(Move*);
	bool moveCancelable(int, int);
	void walk(direction);
	void updateAnimFrame();
	void updatePhysics();
	Move* getCurrentMove();
	Frame& getCurrentFrame();
	int getCurrentMoveNum();
	int getCurrentFrameNum();
	float getSpriteHeight();
	float getSpriteWidth();


	Player();
	~Player();
	
};

