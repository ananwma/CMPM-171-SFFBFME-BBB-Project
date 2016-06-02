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

// still want to generalize this further but its too late so w/e
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
				if (p1.side == LEFT) {
					p1.xvel = -8;
					p2.xvel = 8;
				}
				else if (p1.side == RIGHT) {
					p1.xvel = 8;
					p2.xvel = -8;
				}
			}
			if (abs(p2.yvel) > 0.0f) {
				if (p2.side == LEFT) {
					p2.xvel = -8;
					p1.xvel = 8;
				}
				else if (p2.side == RIGHT) {
					p2.xvel = 8;
					p1.xvel = -8;
				}
			}
		}
		if ((offsetClipBox1.left < 0 && p1.side == LEFT) || (offsetClipBox1.width + offsetClipBox1.left > WINDOW_WIDTH) && p1.side == RIGHT) {
			if (p1.xvel < 0 && p1.side == LEFT)
				p1.xvel = 0;
			if (p1.xvel > 0 && p1.side == RIGHT)
				p1.xvel = 0;
			p1.againstWall = true;
		}
		else
			p1.againstWall = false;
		if ((offsetClipBox2.left < 0 && p2.side == LEFT) || (offsetClipBox2.width + offsetClipBox2.left > WINDOW_WIDTH) && p2.side == RIGHT) {
			if (p2.xvel < 0 && p2.side == LEFT)
				p2.xvel = 0;
			if (p2.xvel > 0 && p2.side == RIGHT)
				p2.xvel = 0;
			p2.againstWall = true;
		}
		else
			p2.againstWall = false;
	}

	/*if (p2.againstWall && p1.againstWall && abs(p1.yvel) > 0 && p1.jumpSide == LEFT) {
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
	}*/
}

void CollisionManager::checkBoxes(Player& attacker, Player& defender) {
	for (auto hitbox : attacker.getCurrentFrame().hitboxes) {
		for (auto hurtbox : defender.getCurrentFrame().hurtboxes) {
			// Make new rects offset by players' current positions and orientations
			sf::FloatRect offsetHit;
			if (attacker.side == LEFT) {
				sf::FloatRect tmp(hitbox.left + attacker.xpos, hitbox.top + attacker.ypos, hitbox.width, hitbox.height);
				offsetHit = tmp;
			}
			else if (attacker.side == RIGHT) {
				sf::FloatRect tmp(attacker.xpos - hitbox.width - hitbox.left + attacker.spriteWidth, hitbox.top + attacker.ypos, hitbox.width, hitbox.height);
				offsetHit = tmp;
			}

			sf::FloatRect offsetHurt;
			if (defender.side == LEFT) {
				sf::FloatRect tmp(hurtbox.left + defender.xpos, hurtbox.top + defender.ypos, hurtbox.width, hurtbox.height);
				offsetHurt = tmp;
			}
			else if (defender.side == RIGHT) {
				sf::FloatRect tmp(defender.xpos - hurtbox.width - hurtbox.left + defender.getSpriteWidth(), hurtbox.top + defender.ypos, hurtbox.width, hurtbox.height);
				offsetHurt = tmp;
			}
			if (offsetHit.intersects(offsetHurt)) {
				cout << "!!!" << endl;
				//on collision, checks first if player getting hit was holding block while being in the correct state
				if (defender.holdingBlock && defender.state != HITSTUN_STATE && defender.state != ATTACK_STATE && defender.state != AIRBORNE_STATE) {
					defender.getHit(attacker.getCurrentMove());
					cout << "blocked?";
				}
				else {
					//if not blocking, player gets hit
					if (!attacker.getCurrentFrame().hit) {
						cout << "hit!" << endl;
						defender.getHit(attacker.getCurrentMove());
						attacker.getCurrentFrame().hit = true;
					}
					attacker.canCancel = true;
					return;
				}
			}
		}
	}
}




CollisionManager::~CollisionManager()
{

}
