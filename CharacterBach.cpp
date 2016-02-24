#include "stdafx.h"
#include <iostream>

#include "CharacterBach.h"
#include "BachJab.h"
#include "BachIdle.h"
#include "BachHitstun.h"
#include "BachStrong.h"

using namespace std;

Bach::Bach() {
	width = 438;
	height = 548;
	walkspeed = 1.0f;
	health = 1000;
}

void Bach::walk() {

}

void Bach::initMoves() {
	// Clean up these pointers somewhere 
	BachJab* jab = new BachJab;
	BachStrong* strong = new BachStrong;
	BachIdle* idle = new BachIdle;
	BachHitstun* hitstun = new BachHitstun;
	jab->initFrames();
	idle->initFrames();
	hitstun->initFrames();
	strong->initFrames();
	moveList[JAB] = jab;
	moveList[IDLE] = idle;
	moveList[WALK] = idle;
	moveList[JUMP] = idle;
	moveList[HITSTUN] = hitstun;
	moveList[STRONG] = strong;
}