#pragma once
#include <SFML/Graphics.hpp>
#include "Move.h"
#include <string>
#include <vector>
#include <unordered_map>

using BoxVec = vector<sf::FloatRect>;
using FrameVec = vector<Frame>;

// fix ordering of this later
enum Moves { HITSTUN, BLOCK, STRONG, JAB, IDLE, WALK, FIERCE, JUMP, FORWARD, ROUNDHOUSE, GRAB };

class Character {
friend class Player;
protected:
	int width;
	int height;
	float walkspeed;
	int health;
public:
	sf::Sprite sprite;
	int currentMove;
	int currentMoveFrame;
	unordered_map <int, Move*> moveList;

	virtual void initMoves() = 0;
};

