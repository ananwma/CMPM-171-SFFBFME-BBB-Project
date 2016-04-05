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
#include "Game.h"
#include "BachSuper.h"
#include "BachGrab.h"

using namespace std;

Bach::Bach() {
	width = 438;
	height = 548;
	walkspeed = 8.0f;
	jumpX = 8.0f;
	jumpY = 35.0f;
	health = 1000;
	wall_offset = 100;
	super = { 7, 0, 2, 4, 5, 7, 0, 0 };
}

void Bach::walk() {

}

void Bach::initMoves() {
	// Clean up these pointers somewhere 
	BachGrab* grab = new BachGrab;
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
	moveList[GRAB] = grab;
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