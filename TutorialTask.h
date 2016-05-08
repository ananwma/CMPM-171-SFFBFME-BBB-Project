#pragma once
#include <iostream>
#include <string>
#include "Player.h"

using namespace std;

class TutorialTask {
public:
	bool taskComplete;
	virtual bool testTask(Player&) = 0;
	TutorialTask();
	TutorialTask(string);
	string task;
};

class MoveBack : public TutorialTask {
	virtual bool testTask(Player& player) {
		return player.state == WALK_STATE && player.xvel < 0;
	}
};

class MoveForward : public TutorialTask {
	virtual bool testTask(Player& player) {
		return player.state == WALK_STATE && player.xvel > 0;
	}
};