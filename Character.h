#pragma once
#include <SFML/Graphics.hpp>
#include "Move.h"
#include <string>
#include <vector>
#include <unordered_map>

using BoxVec = vector<sf::FloatRect>;
using FrameVec = vector<Frame>;

// fix ordering of this later
enum Moves { HITSTUN, BLOCK, STRONG, JAB, IDLE, WALK, FIERCE, JUMP, SHRT, FORWARD, ROUNDHOUSE, GRAB, CMAJ, GMAJ, SUPER };

class Character {
friend class Player;
protected:
	int width;
	int height;
	float jumpY;
	int health;
	vector<int> super;
public:
	float jumpX;

	float walkspeed;
	int wall_offset;
	sf::Sprite sprite;
	int currentMove;
	int currentMoveFrame;
	unordered_map <int, Move*> moveList;

	virtual void initMoves() = 0;
};

