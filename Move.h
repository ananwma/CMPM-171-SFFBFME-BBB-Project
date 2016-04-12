#pragma once
#include "Frame.h"
#include <iostream>


using namespace std;
using BoxVec = vector<sf::FloatRect>;
using FrameVec = vector<Frame>;

enum state { NO_STATE, WALK_STATE, AIRBORNE_STATE, HITSTUN_STATE, ATTACK_STATE, BLOCKSTUN_STATE, GRAB_STATE, FALLING_STATE, COLLAPSED_STATE };

class Move {
	friend class Player;
public:
	//Move() = default;
	//~Move() = default;
	virtual void initFrames() = 0;
	virtual void initCancelMoves() = 0;
	virtual int getFrameCount() { return frameCount; };
	virtual int getDamage() { return damage; };
	virtual int getMeterGain() { return metergain; };
	void setHitFalse() { for (auto &i : frameVector) i.hit = false; }
protected:
	sf::Texture spritesheet;
	int frameCount;
	vector<Frame> frameVector;
	int damage;
	int metergain;
	int hitstun;
	int blockstun;
	float velX = 0;
	float velY = 0;
	float accX = 0;
	float accY = 0;
	float pushX = 0;
	float pushY = 0;
	vector<int> cancelMoves;
	state state;
};

