#pragma once
#include "Entity.h"
#include "Player.h"
#include <stack>

class CollisionManager
{
public:
	CollisionManager();

	enum collisionType { STATIC, DYNAMIC, NONE };

	void registerEntity(Entity&);

	void updateCollision();

	void checkClipBoxes(Player & p1, Player & p2);

	~CollisionManager();

private:
	std::stack<Entity*> entities;
};

