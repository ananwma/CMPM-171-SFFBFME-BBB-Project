#pragma once
#include "Frame.h"
#include <unordered_map>
#include <iostream>


using namespace std;
using BoxVec = vector<sf::FloatRect>;
using FrameVec = vector<Frame>;

enum State { NO_STATE, WALK_STATE, AIRBORNE_STATE, HITSTUN_STATE, ATTACK_STATE, BLOCKSTUN_STATE, GRAB_STATE, FALLING_STATE, COLLAPSED_STATE, AIR_ATTACK_STATE };

class Move {
	friend class Player;
	friend class CollisionManager;
public:
	Move() = default;
	~Move() = default;
	unordered_map<int, Frame> frameMap;
	int getFrameCount() { return frameCount; };
	int getDamage() { return damage; };
	void setHitFalse() { for (auto &i : frameMap) i.second.hit = false; }
	string moveName;
protected:
	sf::Texture spritesheet;
	int frameCount;
	int damage;
	int hitstun;
	int blockstun;
	int metergain;
	int width;
	int height;
	float velX = 0;
	float velY = 0;
	float accX = 0;
	float accY = 0;
	float pushX = 0;
	float pushY = 0;
	float knockback = 0;
	bool inAir = 0;
	bool knocksdown = false;
	vector<int> cancelMoves;
	State state;
};
