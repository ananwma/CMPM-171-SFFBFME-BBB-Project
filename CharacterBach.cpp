#include "stdafx.h"
#include <iostream>

#include "CharacterBach.h"
#include "BachJab.h"
#include "BachIdle.h"
#include "BachHitstun.h"
#include "BachStrong.h"
#include "BachShoryuken.h"
#include "BachBlockstun.h"
#include "BachShort.h"
#include "BachForward.h"
#include "BachRoundhouse.h"
#include "BachFierce.h"
#include "BachTatsu.h"
#include "BachSuper.h"

using namespace std;

Bach::Bach() {
	width = 438;
	height = 548;
	walkspeed = 8.0f;
	jumpX = 8.0f;
	jumpY = 35.0f;
	health = 1000;
	wall_offset = 100;
}

void Bach::walk() {

}

void Bach::initMoves() {
	// Clean up these pointers somewhere 
	BachJab* jab = new BachJab;
	BachStrong* strong = new BachStrong;
	BachFierce* fierce = new BachFierce;
	BachIdle* idle = new BachIdle;
	BachHitstun* hitstun = new BachHitstun;
	BachShoryuken* srk = new BachShoryuken;
	BachBlockstun* blach = new BachBlockstun;
	BachShort* shrt = new BachShort;
	BachForward* forward = new BachForward;
	BachRoundhouse* roundhouse = new BachRoundhouse;
	BachTatsu* tatsu = new BachTatsu;
	BachSuper* super = new BachSuper;
	jab->initFrames();
	jab->initCancelMoves();
	idle->initFrames();
	hitstun->initFrames();
	strong->initFrames();
	fierce->initFrames();
	blach->initFrames();
	srk->initFrames();
	shrt->initFrames();
	forward->initFrames();
	roundhouse->initFrames();
	tatsu->initFrames();
	super->initFrames();
	moveList[JAB] = jab;
	moveList[IDLE] = idle;
	moveList[WALK] = idle;
	moveList[JUMP] = idle;
	moveList[HITSTUN] = hitstun;
	moveList[STRONG] = strong;
	moveList[FIERCE] = fierce;
	moveList[BLOCK] = blach;
	moveList[SHRT] = shrt;
	moveList[FORWARD] = forward;
	moveList[ROUNDHOUSE] = roundhouse;
	moveList[CMAJ] = srk;
	moveList[GMAJ] = tatsu;
	moveList[SUPER] = super;
}