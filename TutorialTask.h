#pragma once
#include <iostream>
#include <string>
#include "TutorialState.h"

using namespace std;

class TutorialTask {
public:
	bool taskComplete;
	bool testTask(int);
	TutorialTask();
	TutorialTask(string);
	string task;
};