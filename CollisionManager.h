#pragma once
//#include "Entity.h"

class CollisionManager
{
public:
	CollisionManager();

	enum collisionType { STATIC, DYNAMIC, NONE };

	//void registerEntity(Entity e, collisionType);

	~CollisionManager();
};

