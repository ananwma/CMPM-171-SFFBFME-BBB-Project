#pragma once
#include <iostream>
#include <string>

using namespace std;

class TutorialTask {
public:
	bool taskComplete;
	bool testTask(int);
	TutorialTask();
	TutorialTask(string);
	string task;
};