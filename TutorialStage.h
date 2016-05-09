#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "TutorialTask.h"

using namespace std;

class TutorialStage {
public:
	queue<TutorialTask> tasks;
	TutorialStage(queue<string>, queue<string>, queue<TutorialTask>);
	bool testNextTask(Player&);
	bool hasTasks();
	bool hasPretext();
	bool hasPosttext();
	string getTaskText();
	string popPretext();
	string popPosttext();
	queue <string> preText;
	queue <string> postText;
};