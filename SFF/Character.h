#pragma once
#include <SFML/Graphics.hpp>
#include "Move.h"
#include <string>
#include <vector>
#include <unordered_map>

using BoxVec = vector<sf::FloatRect>;
using FrameVec = vector<Frame>;
enum Moves { IDLE, WALK, JUMP, HITSTUN, JAB, STRONG, FIERCE, SHRT, FORWARD, ROUNDHOUSE, GRAB };

class Character {
friend class Player;
protected:
	int width;
	int height;
	float walkspeed;
	sf::Texture spritesheet;
public:
	sf::Sprite sprite;
	int currentMove;
	int currentMoveFrame;
	unordered_map <int, Move> moveList;

	virtual void initMoves() = 0;
};

