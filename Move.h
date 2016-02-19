#pragma once
#include "Frame.h"
#include <iostream>


using namespace std;
using BoxVec = vector<sf::FloatRect>;
using FrameVec = vector<Frame>;

enum state { NONE, WALKING, AIRBORNE, HITSTUN_STATE, ATTACKING, COLLIDING };

class Move {
	friend class Player;
public:
	//Move() = default;
	//~Move() = default;
	virtual void initFrames() = 0;
	virtual int getFrameCount() { return frameCount; };
protected:
	sf::Texture spritesheet;
	int frameCount;
	vector<Frame> frameVector;
	int damage;
	int deltax;
	int deltay;
	vector<Move> cancelMoves;
	state state;
};

