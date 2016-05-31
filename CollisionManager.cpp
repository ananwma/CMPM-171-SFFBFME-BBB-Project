#define NOMINMAX
#include "stdafx.h"
#include<iostream>
#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
}

void CollisionManager::registerEntity(Entity& entity) {
	entities.push(&entity);
}

/*void CollisionManager::updateCollision() {
	while (!entities.empty()) {
		Entity* entity = entities.top();
		entities.pop();
	}


	for (auto &entity : entities) {
		for (auto &other : entities) {
			sf::FloatRect offsetClipBox1;
			sf::FloatRect offsetClipBox2;
			//if (entity->side == LEFT)
				offsetClipBox1 = sf::FloatRect(entity->collisionVolume.left + entity->xpos, entity->collisionVolume.top + entity->ypos, entity->collisionVolume.width, entity->collisionVolume.height);
		//	else if (entity->side == RIGHT)
		//		offsetClipBox1 = sf::FloatRect(entity->xpos - entity->collisionVolume.width - entity->collisionVolume.left + entity->spriteWidth, entity->collisionVolume.top + entity->ypos, entity->collisionVolume.width, entity->collisionVolume.height);
		//	if (other->side == LEFT)
				offsetClipBox2 = sf::FloatRect(other->collisionVolume.left + other->xpos, other->collisionVolume.top + other->ypos, other->collisionVolume.width, other->collisionVolume.height);
		//	else if (other->side == RIGHT)
	//			offsetClipBox2 = sf::FloatRect(other->xpos - other->collisionVolume.width - other->collisionVolume.left + other->spriteWidth, other->collisionVolume.top + other->ypos, other->collisionVolume.width, other->collisionVolume.height);

			if (offsetClipBox1.intersects(offsetClipBox2)) {
				std::cout << "now";
			}
		}
	}
}*/

void CollisionManager::checkClipBoxes(Player& p1, Player& p2) {
	if (!p1.getCurrentFrame().clipboxes.empty() && !p2.getCurrentFrame().clipboxes.empty()) {
		sf::FloatRect clipbox1 = p1.getCurrentFrame().clipboxes.at(0);
		sf::FloatRect clipbox2 = p2.getCurrentFrame().clipboxes.at(0);
		sf::FloatRect offsetClipBox1;
		sf::FloatRect offsetClipBox2;
		if (p1.side == LEFT)
			offsetClipBox1 = sf::FloatRect(clipbox1.left + p1.xpos, clipbox1.top + p1.ypos, clipbox1.width, clipbox1.height);
		else if (p1.side == RIGHT)
			offsetClipBox1 = sf::FloatRect(p1.xpos - clipbox1.width - clipbox1.left + p1.spriteWidth, clipbox1.top + p1.ypos, clipbox1.width, clipbox1.height);
		if (p2.side == LEFT)
			offsetClipBox2 = sf::FloatRect(clipbox2.left + p2.xpos, clipbox2.top + p2.ypos, clipbox2.width, clipbox2.height);
		else if (p2.side == RIGHT)
			offsetClipBox2 = sf::FloatRect(p2.xpos - clipbox2.width - clipbox2.left + p2.spriteWidth, clipbox2.top + p2.ypos, clipbox2.width, clipbox2.height);
		sf::FloatRect intersectBox;
		if (offsetClipBox1.intersects(offsetClipBox2, intersectBox)) {
			// If player 1 is moving in the x direction and player 2 is standing still
			if (abs(p1.xvel) > 0 && p2.xvel == 0) {
				if (p1.xvel > 0 && p1.side == LEFT) {
					p2.xvel = intersectBox.width;
					if (p2.againstWall)
						p1.xvel = 0;
				}
				else if (p1.xvel < 0 && p1.side == RIGHT) {
					p2.xvel = -intersectBox.width;
					if (p2.againstWall)
						p1.xvel = 0;
				}
			}
			// If player 2 is moving in the x direction and player 1 is standing still
			else if (abs(p2.xvel) > 0 && p1.xvel == 0) {
				if (p2.xvel > 0 && p2.side == LEFT) {
					p1.xvel = intersectBox.width;
					if (p1.againstWall)
						p2.xvel = 0;
				}
				else if (p2.xvel < 0 && p2.side == RIGHT) {
					p1.xvel = -intersectBox.width;
					if (p1.againstWall)
						p2.xvel = 0;
				}
			}
			// If both are moving in opposing directions, set both vels to 0
			else if (abs(p1.xvel) > 0 && abs(p2.xvel) > 0) {
				if ((p1.xvel > 0) != (p2.xvel > 0)) {
					p2.xvel = 0;
					p1.xvel = 0;
				}
			}

			if (p2.againstWall && p2.state == WALK_STATE && p1.state == WALK_STATE) {
				p2.xvel = 0;
				p1.xvel = 0;
			}
			else if (p1.againstWall && p1.state == WALK_STATE && p2.state == WALK_STATE) {
				p2.xvel = 0;
				p1.xvel = 0;
			}

			// Airborne stuff
			if (abs(p1.yvel) > 0.0f) {
				float p1Center = (offsetClipBox1.left + offsetClipBox1.width / 2);
				float p2Center = (offsetClipBox2.left + offsetClipBox2.width / 2);
				if (p1Center < p2Center) {
					p2.xvel = 8;
					cout << "left";
				} 
				else if (p1Center > p2Center) {
					p2.xvel = -8;
					cout << intersectBox.width / 6 <<endl;
					cout << "right";
				}


				/*if (p1.jumpSide == LEFT) {
					if (p2.side == RIGHT) {
						p1.xvel = 0;
						p2.xvel = p1.character->jumpX;
					}
					else if (p2.side == LEFT) {
						p2.xvel = -p1.character->jumpX;
					}
				}
				else if (p1.jumpSide == RIGHT) {
					if (p2.side == LEFT) {
						p1.xvel = 0;
						p2.xvel = -p1.character->jumpX;
					}
					else if (p2.side == RIGHT) {
						p2.xvel = p1.character->jumpX;
					}
				}*/
			}
			/*else if (abs(p2.yvel) > 0.0f) {

				if (p2.jumpSide == LEFT) {
					if (p1.side == RIGHT) {
						p2.xvel = 0;
						p1.xvel = p2.character->jumpX;
					}
					else if (p1.side == LEFT) {
						p1.xvel = -p2.character->jumpX;
					}
				}
				else if (p2.jumpSide == RIGHT) {
					if (p1.side == LEFT) {
						p2.xvel = 0;
						p1.xvel = -p2.character->jumpX;
					}
					else if (p1.side == RIGHT) {
						p1.xvel = p2.character->jumpX;
					}
				}
			}*/
		}
		if (offsetClipBox1.left < 0 || offsetClipBox1.width + offsetClipBox1.left > WINDOW_WIDTH) {
			if (p1.xvel < 0 && p1.side == LEFT)
				p1.xvel = 0;
			if (p1.xvel > 0 && p1.side == RIGHT)
				p1.xvel = 0;
			p1.againstWall = true;
		}
		else
			p1.againstWall = false;
		if (offsetClipBox2.left < 0 || offsetClipBox2.width + offsetClipBox2.left > WINDOW_WIDTH) {
			if (p2.xvel < 0 && p2.side == LEFT)
				p2.xvel = 0;
			if (p2.xvel > 0 && p2.side == RIGHT)
				p2.xvel = 0;
			p2.againstWall = true;
		}
		else
			p2.againstWall = false;
	}

	if (p2.againstWall && p1.againstWall && abs(p1.yvel) > 0 && p1.jumpSide == LEFT) {
		p2.xvel = -p1.character->jumpX;
	}
	else if (p2.againstWall && p1.againstWall && abs(p1.yvel) > 0 && p1.jumpSide == RIGHT) {
		p2.xvel = p1.character->jumpX;
	}
	if (p1.againstWall && p2.againstWall && abs(p2.yvel) > 0 && p2.jumpSide == LEFT) {
		p1.xvel = -p2.character->jumpX;
	}
	else if (p1.againstWall && p2.againstWall && abs(p2.yvel) > 0 && p2.jumpSide == RIGHT) {
		p1.xvel = p2.character->jumpX;
	}
}




CollisionManager::~CollisionManager()
{

}
