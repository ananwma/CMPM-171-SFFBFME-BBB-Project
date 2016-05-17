#pragma once
#include <iostream>
#include <string>
#include <climits>
#include "Player.h"

//
using namespace std;

class TutorialTask {
public:
	bool testTask(Player&);
	TutorialTask() = default;
	string taskText;
	vector<int> leftIconFrames;
	
	int checkState = -1;
	int checkXvelGreaterThan = INT_MIN;
	int checkXvelLessThan = INT_MAX;
	int checkYvelGreaterThan = INT_MIN;
	int checkYvelLessThan = INT_MAX;
	int checkMove = -1;
	int checkComplete = 1;
	int numComplete = 0;
};