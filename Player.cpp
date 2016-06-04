#include <memory>
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
	meter = 0.0f;
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
		{ "AIR_ATTACK_STATE", AIR_ATTACK_STATE },
		{ "BLOCKSTUN_STATE", BLOCKSTUN_STATE },
		{ "COLLAPSED_STATE", COLLAPSED_STATE } };

	// Load XML File
	tinyxml2::XMLDocument characterFile;
	characterFile.LoadFile(filename.c_str());

	// Parse data from file into class variables
	tinyxml2::XMLElement* characterData = characterFile.FirstChildElement("character");
	walkspeed = atof(characterData->FirstChildElement("walkspeed")->GetText());
	jumpX = atof(characterData->FirstChildElement("jumpX")->GetText());
	jumpY = atof(characterData->FirstChildElement("jumpY")->GetText());
	maxHealth = atoi(characterData->FirstChildElement("health")->GetText());
	health = maxHealth;
	walloffset = atoi(characterData->FirstChildElement("walloffset")->GetText());
	portrait.loadFromFile(characterData->FirstChildElement("portrait")->GetText());
	tinyxml2::XMLElement* sounds = characterData->FirstChildElement("sounds");
	tinyxml2::XMLElement* nextSound = sounds->FirstChildElement("sound");
	while (nextSound != NULL) {
		shared_ptr<sfx> tmp(new sfx(nextSound->Attribute("file")));
		sfxMap[nextSound->Attribute("name")] = tmp;
		//sfxMap.emplace(nextSound->Attribute("name"), sfx(nextSound->Attribute("file")));
		sounds->DeleteChild(nextSound);
		nextSound = sounds->FirstChildElement("sound");
	}


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
		move.knocksdown = atoi(nextMove->FirstChildElement("knocksdown")->GetText());
		move.metergain = atoi(nextMove->FirstChildElement("metergain")->GetText());
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

	hitSoundBuffer.loadFromFile("sounds/hit.wav");
	blockSoundBuffer.loadFromFile("sounds/block.wav");
	hitSound.setBuffer(hitSoundBuffer);
	blockSound.setBuffer(blockSoundBuffer);
	return true;
}

void Player::update() {
	updatePhysics();
	if (state == ATTACK_STATE && currAnimFrame == numAnimFrames - 1) {
		state = NO_STATE;
		doMove("idle");
	}
	else if ((state == AIRBORNE_STATE || state == AIR_ATTACK_STATE) && ypos == GROUND) {
		state = NO_STATE;
		doMove("idle");
	}
	else if (state == AIRBORNE_STATE && yvel > 0) {
		doMove("fall");
	}
	else if (state == HITSTUN_STATE) {
		if (hitstunFrames <= 0 && ypos == GROUND) {
			state = NO_STATE;
			if (collapse) {
				doMove("collapse");
			}
			doMove("idle");
		}
	}
	else if (state == BLOCKSTUN_STATE) {
		if (blockstunFrames == 0) {
			state = NO_STATE;
			doMove("idle");
		}
	}
	else if (state == COLLAPSED_STATE && currAnimFrame == numAnimFrames - 1) {
		state = NO_STATE;
		doMove("idle");
	}
}

void Player::doMove(string moveName) {
	if (state == NO_STATE || state == WALK_STATE) {
		if (currentMove != &moveMap[moveName]) {
			currentMove = &moveMap[moveName];
			setAnimTexture(currentMove->spritesheet, currentMove->width, currentMove->height, currentMove->frameCount);
		}
		currentMove->setHitFalse();
		xvel = currentMove->velX * side * (500 / beat);
		yvel += currentMove->velY * (500 / beat);
		state = currentMove->state;
		meter += currentMove->metergain;

		if (moveName == "jab" || moveName == "strong" || moveName == "fierce" || moveName == "short" || moveName == "forward" || moveName == "roundhouse")
			playSound("attack" + to_string(rand() % 3 + 1));
		else if (moveName == "shoryuken")
			playSound("uppercut");
		else if (moveName == "toccata")
			playSound("toccata");
	}
	else if (state == AIRBORNE_STATE) {
		if (moveName == "short" || moveName == "forward" || moveName == "roundhouse")
			moveName = "air_kick";
		else if (moveName == "jab" || moveName == "strong" || moveName == "fierce")
			moveName = "air_punch";
		if (moveMap[moveName].inAir) {
			if (currentMove != &moveMap[moveName]) {
				currentMove = &moveMap[moveName];
				setAnimTexture(currentMove->spritesheet, currentMove->width, currentMove->height, currentMove->frameCount);
				meter += currentMove->metergain;
				currentMove->setHitFalse();
			}
			xvel += currentMove->velX * (500 / beat);
			yvel += currentMove->velY * (500 / beat);
			state = currentMove->state;
		}
	}

}

void Player::getHit(Move *move) {
	if (holdingBlock && move->moveName != "grab" && move->moveName != "super") {
		blockstunFrames = move->blockstun;
		//xvel = move->pushX;
		//yvel = move->pushY;
		blockSound.play();
		doMove("blockstun");
	}
	else {
		if (ypos != GROUND && move->moveName == "grab")
			return;
		hitstunFrames = move->hitstun;
		health -= move->damage;
		xvel = move->pushX * (500 / beat);
		yvel = move->pushY * (500 / beat);
		state = NO_STATE;
		collapse = move->knocksdown;
		hitSound.play();
		doMove("hitstun");
	}
}

void Player::playSound(string name) {
	sfxMap[name]->play();
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

void Player::checkSuper(int note) {
	if (super.at(superIndex) == note && superTimeout.restart().asMilliseconds() < SUPER_TIMEOUT) {
		superIndex++;
		if (superIndex == super.size()) {
			state = NO_STATE;
			if (meter >= 1000)
				doMove("super");
			superIndex = 0;
			meter = 0;
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