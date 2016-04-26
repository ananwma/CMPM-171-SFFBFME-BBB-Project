#pragma once
#include <iostream>
#include <string>
#include "Player.h"

using namespace std;

class TutorialTask {
public:
	bool taskComplete;
	void testTask(Player&);
	TutorialTask();
	TutorialTask(string);
	string task;
};