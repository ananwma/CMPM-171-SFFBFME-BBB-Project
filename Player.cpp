#include "stdafx.h"
#include "Character.h"
#include "Player.h"
#include "BeatIndicator.h"

#include "tinyxml2.h"
//#include "Game.h"
#include <time.h> 
#include <math.h>
#include <sstream>

#define WALL_WIDTH 1280
#define INIT_XPOS 20
#define INIT_YPOS 400
#define GRAVITY 0.98f * pow((500.0f/BEAT_SPEED),2.0f)
//#define GROUND 100
#define SUPER_TIMEOUT 4000



Player::Player()
{
	playerId = -1;
	hitstunFrames = 0;
	meter = 1000.0f;
	gravity = 0.98f;
	state = NO_STATE;
	colliding = false;
	canCancel = false;
	lastMoveHit = false;
	left = false;
	jumping = false;
	holdingBlock = false;
	right = false;
}

bool Player::loadCharacter(string filename) {

	unordered_map<string, State> stateMap = {
		{ "NO_STATE", NO_STATE },
		{ "WALK_STATE", WALK_STATE },
		{ "AIRBORNE_STATE", AIRBORNE_STATE },
		{ "HITSTUN_STATE", HITSTUN_STATE },
		{ "ATTACK_STATE", ATTACK_STATE },
		{ "BLOCKSTUN_STATE", BLOCKSTUN_STATE } };

	// Load XML File
	tinyxml2::XMLDocument characterFile;
	characterFile.LoadFile(filename.c_str());

	// Parse data from file into class variables
	tinyxml2::XMLElement* characterData = characterFile.FirstChildElement("character");
	walkspeed = atof(characterData->FirstChildElement("walkspeed")->GetText());
	jumpX = atof(characterData->FirstChildElement("jumpX")->GetText());
	jumpY = atof(characterData->FirstChildElement("jumpY")->GetText());
	maxHealth = atoi(characterData->FirstChildElement("health")->GetText());
	walloffset = atoi(characterData->FirstChildElement("walloffset")->GetText());
	health = maxHealth;

	// Parse string of ints into int vector for super
	string superStr = characterData->FirstChildElement("super")->GetText();
	stringstream stream(superStr);
	int n;
	while (stream >> n)
		super.push_back(n);

	tinyxml2::XMLElement* nextMove = characterData->FirstChildElement("move");
	while (nextMove != NULL) {
		Move move;
		move.moveName = nextMove->FirstAttribute()->Value();
		move.spritesheet.loadFromFile(nextMove->FirstChildElement("sprite")->GetText());
		move.width = atoi(nextMove->FirstChildElement("width")->GetText());
		move.height = atoi(nextMove->FirstChildElement("height")->GetText());
		move.frameCount = atoi(nextMove->FirstChildElement("framecount")->GetText());
		move.damage = atoi(nextMove->FirstChildElement("damage")->GetText());
		move.hitstun = atoi(nextMove->FirstChildElement("hitstun")->GetText());
		move.blockstun = atoi(nextMove->FirstChildElement("blockstun")->GetText());
		move.velX = atof(nextMove->FirstChildElement("velx")->GetText());
		move.velY = atof(nextMove->FirstChildElement("vely")->GetText());
		move.pushX = atof(nextMove->FirstChildElement("pushx")->GetText());
		move.pushY = atof(nextMove->FirstChildElement("pushy")->GetText());
		move.knockback = atof(nextMove->FirstChildElement("knockback")->GetText());
		move.inAir = atoi(nextMove->FirstChildElement("inair")->GetText());
		move.state = stateMap[nextMove->FirstChildElement("state")->GetText()];

		tinyxml2::XMLElement* frameData = nextMove->FirstChildElement("framedata");
		tinyxml2::XMLElement* nextBox = frameData->FirstChildElement("hitbox");
		unordered_map<int, Frame> frameMap;
		while (nextBox != NULL) {
			int frameIndex = atoi(nextBox->Attribute("frame"));

			//If not found create new
			if (frameMap.find(frameIndex) == frameMap.end())
				frameMap[frameIndex] = Frame();

			frameMap.at(frameIndex).addBox(nextBox->Attribute("userdata"), sf::FloatRect(atof(nextBox->Attribute("x")),
				atof(nextBox->Attribute("y")),
				atof(nextBox->Attribute("width")),
				atof(nextBox->Attribute("height"))));

			frameData->DeleteChild(nextBox);
			nextBox = frameData->FirstChildElement("hitbox");
		}
		move.frameMap = frameMap;


		moveMap[nextMove->Attribute("name")] = move;
		characterData->DeleteChild(nextMove);
		nextMove = characterData->FirstChildElement("move");
	}

	return true;
}

void Player::update() {
	updatePhysics();
	if (state == ATTACK_STATE && currAnimFrame == numAnimFrames - 1) {
		state = NO_STATE;
		doMove("idle");
	}
	else if (state == AIRBORNE_STATE && ypos == GROUND) {
		state = NO_STATE;
		doMove("idle");
	}
	else if (state == AIRBORNE_STATE && yvel > 0) {
		doMove("fall");
	}
	else if (state == HITSTUN_STATE) {
		if (hitstunFrames == 0) {
			state = NO_STATE;
			doMove("idle");
		}
	}
	else if (state == BLOCKSTUN_STATE) {
		if (blockstunFrames == 0) {
			state = NO_STATE;
			doMove("idle");
		}
	}
}

void Player::doMove(string moveName) {
	if (state == NO_STATE || state == WALK_STATE) {
		if (currentMove != &moveMap[moveName]) {
			currentMove = &moveMap[moveName];
			setAnimTexture(currentMove->spritesheet, currentMove->width, currentMove->height, currentMove->frameCount);
		}
		currentMove->setHitFalse();
		xvel = currentMove->velX;
		yvel = currentMove->velY;
		state = currentMove->state;
	}
	else if (state == AIRBORNE_STATE) {
		if (moveMap[moveName].inAir) {
			if (currentMove != &moveMap[moveName]) {
				currentMove = &moveMap[moveName];
				setAnimTexture(currentMove->spritesheet, 438, 548, currentMove->frameCount);
			}
			xvel += currentMove->velX;
			yvel += currentMove->velY;
			state = currentMove->state;
		}
	}

	/*if (state != ATTACK_STATE && state != BLOCKSTUN_STATE && state != HITSTUN_STATE && state != AIRBORNE_STATE) {
	if (state == WALK_STATE)
	xvel = 0;
	if (moveName == IDLE)
	xvel = 0;
	character->currentMove = move;
	getCurrentMove()->setHitFalse();
	//character->sprite.setTexture(character->moveList.at(move)->spritesheet);
	setAnimTexture(character->moveList.at(moveName)->spritesheet, 438, 548, character->moveList.at(moveName)->frameCount);
	character->currentMoveFrame = 0;
	state = getCurrentMove()->state;
	yvel = getCurrentMove()->velY * (500 / beat);
	if (side == LEFT)
	xvel = getCurrentMove()->velX * (500 / beat);
	else if (side == RIGHT)
	xvel = -getCurrentMove()->velX * (500 / beat);
	}
	else if (state == ATTACK_STATE && canCancel && moveCancelable(character->currentMove, moveName)) {
	character->currentMove = moveName;
	character->sprite.setTexture(character->moveList.at(moveName)->spritesheet);
	character->currentMoveFrame = 0;
	state = getCurrentMove()->state;
	}*/
}

void Player::getHit(Move *move) {
	if (holdingBlock) {
		blockstunFrames = move->blockstun;
		xvel = move->pushX;
		yvel = move->pushY;
		doMove("blockstun");
	}
	else {
		hitstunFrames = move->hitstun;
		health -= move->damage;
		xvel = move->pushX;
		yvel = move->pushY;
		doMove("hitstun");
	}
	//if (state != BLOCKING) {
	/*character->currentMove = HITSTUN;
	character->currentMoveFrame = 0;
	hitstunFrames = move->hitstun + ezmode;
	character->sprite.setTexture(character->moveList.at(HITSTUN)->spritesheet);
	state = HITSTUN_STATE;
	health -= move->damage;
	int direction;
	if (side == RIGHT) {
	direction = 1;
	}
	else {
	direction = -1;
	}
	xvel = move->pushX*direction;
	yvel = move->pushY;
	if (yvel < 0 || ypos < GROUND) state = AIRBORNE_STATE;
	//}
	/*else {
	character->currentMove = BLOCKSTUN;
	character->currentMoveFrame = 0;
	character->sprite.setTexture(character->moveList.at(BLOCKSTUN)->spritesheet);
	state = BLOCKSTUN_STATE;
	health -= move->damage;
	}*/
}

void Player::block(Move *move) {
	//if (state != BLOCKING) {
	/*character->currentMove = BLOCK;
	character->currentMoveFrame = 0;
	blockstunFrames = move->blockstun;
	character->sprite.setTexture(character->moveList.at(BLOCK)->spritesheet);
	state = BLOCKSTUN_STATE;
	//health -= move->damage;
	int direction;
	if (side == RIGHT) {
	direction = 1;
	}
	else {
	direction = -1;
	}
	xvel = move->pushX*direction;
	//yvel = move->pushY;
	if (yvel < 0 || ypos < GROUND) state = AIRBORNE_STATE;
	//}
	/*else {
	character->currentMove = BLOCKSTUN;
	character->currentMoveFrame = 0;
	character->sprite.setTexture(character->moveList.at(BLOCKSTUN)->spritesheet);
	state = BLOCKSTUN_STATE;
	health -= move->damage;
	}*/
}

bool Player::moveCancelable(int currMove, int newMove) {
	/*for (int i = 0; i < character->moveList.at(currMove)->cancelMoves.size(); i++) {
	if (newMove == character->moveList.at(currMove)->cancelMoves.at(i)) {
	return true;
	}
	}
	return false;*/
	return 0;
}

void Player::walk(direction dir) {
	// will need to add more later for figuring out which side player is on
	/*if (state != ATTACK_STATE && state != BLOCKSTUN_STATE && state != HITSTUN_STATE && state != AIRBORNE_STATE) {
	character->currentMove = WALK;
	character->sprite.setTexture(character->moveList.at(WALK)->spritesheet);
	state = WALK_STATE;
	if (dir == LEFT) {
	//character->sprite.move(character->walkspeed, 0);
	//xpos += character->walkspeed;
	if (!(character->sprite.getPosition().x + character->wall_offset <= -200)) {
	xvel = -character->walkspeed * (500 / beat);
	}
	}
	else if (dir == RIGHT) {
	//character->sprite.move(-character->walkspeed, 0);
	//xpos -= character->walkspeed;
	if (!(character->sprite.getPosition().x + character->width - character->wall_offset >= WALL_WIDTH + 200)) {
	xvel = character->walkspeed * (500 / beat);
	}
	}
	}*/
}

void Player::jump(direction dir) {
	/*if (state != ATTACK_STATE && state != BLOCKSTUN_STATE && state != HITSTUN_STATE && state != AIRBORNE_STATE) {
	character->currentMove = WALK;
	character->sprite.setTexture(character->moveList.at(WALK)->spritesheet);
	state = AIRBORNE_STATE;
	if (dir == RIGHT) {
	yvel = -character->jumpY * (500 / beat);
	xvel = character->jumpX *  (500 / beat);
	jumpSide = side;
	}
	if (dir == LEFT) {
	yvel = -character->jumpY * (500 / beat);
	xvel = -character->jumpX * (500 / beat);
	jumpSide = side;
	}
	if (dir == NEUTRAL) {
	yvel = -character->jumpY * (500 / beat);
	// Neutral jump = opposite side for crossunders
	side == LEFT ? jumpSide = RIGHT : jumpSide = LEFT;
	}
	}*/
}

void Player::checkSuper(int note) {
	if (super.at(superIndex) == note && superTimeout.restart().asMilliseconds() < SUPER_TIMEOUT) {
		superIndex++;
		if (superIndex == super.size()) {
			state = NO_STATE;
			doMove("super");
			superIndex = 0;
		}
	}
	else {
		superIndex = 0;
	}
}

bool Player::isInSuper() {
	return superIndex > 0;
}

string Player::getCurrentMoveName() {
	return currentMove->moveName;
}

int Player::getCurrentFrameNum() {
	return currAnimFrame;
}


Move* Player::getCurrentMove() {
	return currentMove;
}

Frame& Player::getCurrentFrame() {
	return currentMove->frameMap[currAnimFrame];
}

float Player::getSpriteWidth() {
	return spriteWidth;
}

float Player::getSpriteHeight() {
	return spriteHeight;
}

int Player::getMaxHealth() {
	return maxHealth;
}

int Player::getHealth() {
	return health;
}

State Player::getState() {
	return state;
}

void Player::setBeat(float beat) {
	this->beat = beat;
	gravity = 0.98f * pow((500.0f / beat), 2.0f);
}

Player::~Player()
{
}