#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "Character.h"

using namespace std;

class Player
{
public:
	bool isMoveValid();


	Character currentCharacter;

	int x;
	int y;
	int health;
	int meter;
	int roundWins;
	string state;
	sf::Texture pTexture;
	sf::Sprite pImage;
	//Move currentMove;
	
	int inputBuffer;
	bool canCancel;
	// currentSprite;
	int currentFrame;
	Player(Character, int, int);
	~Player();
	
};

