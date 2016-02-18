#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "Character.h"
#include "Move.h"

using namespace std;
enum direction { FORWARDS, BACKWARDS };

class Player
{
private:
	//Character* character;
public:
	Character* character;
	bool isMoveValid();
	void setCharacter(Character*);

	float xpos;
	float ypos;
	int health;
	int meter;
	int roundWins;
	int playerId;
	bool facing_right;
	string state;
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
	void walk(direction);
	void updateAnimFrame();
	Move getCurrentMove();
	Frame getCurrentFrame();
	int getCurrentMoveNum();
	int getCurrentFrameNum();

	Player();
	~Player();
	
};

