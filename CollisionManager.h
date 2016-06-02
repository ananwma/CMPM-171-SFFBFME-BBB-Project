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

	void checkClipBoxes(Player & p1, Player & p2, float, float);

	void checkBoxes(Player &, Player &);

	~CollisionManager();

private:
	std::stack<Entity*> entities;
};