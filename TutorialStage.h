#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "TutorialTask.h"

using namespace std;

class TutorialStage {
private:
	queue <string> preText;
	queue <string> postText;
	queue<TutorialTask> tasks;
	unsigned int animFrame = 0;
public:
	TutorialStage(queue<string>, queue<string>, queue<TutorialTask>);
	bool testNextTask(Player&);
	bool hasTasks();
	bool hasPretext();
	bool hasPosttext();
	string getTaskText();
	string popPretext();
	string popPosttext();
	int getAnimFrame();
};