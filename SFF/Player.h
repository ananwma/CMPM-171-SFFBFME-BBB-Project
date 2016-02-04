#pragma once
#include <SFML/Graphics.hpp>
#include "Move.h"
#include <string>
#include <vector>

using namespace std;

class Character
{
public:
	enum possibleMoves { Idle, Walk, Jump, Attack, Hurt };
	possibleMoves currentMove;
	int currentMoveFrame;
	string spritesheet;
	vector <Move> moveList;
	//sf::Vector2i source(0, Idle);
	Character();
	Character(vector<Move> moveList_n, string spritesheet_url);
	~Character();
};

