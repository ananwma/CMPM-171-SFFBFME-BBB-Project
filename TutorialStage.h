#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "TutorialTask.h"

using namespace std;

class TutorialStage {
public:
	vector<TutorialTask> tasks;
	bool stagecomplete;
	bool preTextRead;
	TutorialStage();
	TutorialStage(stack<string>, stack<string>, vector<TutorialTask>);
	stack <string> preText;
	stack <string> postText;
};