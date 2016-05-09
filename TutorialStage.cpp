#include "stdafx.h"
#include "TutorialStage.h"

TutorialStage::TutorialStage(queue<string> _pre, queue<string> _post , queue<TutorialTask> _tasks) : 
	preText(_pre),
	postText(_post),
	tasks (_tasks)
{ }

bool TutorialStage::testNextTask(Player& player) {
	if (tasks.front().testTask(player)) {
		tasks.pop();
		return true;
	}
	return false;
}

bool TutorialStage::hasTasks() {
	return !tasks.empty();
}

bool TutorialStage::hasPretext() {
	return !preText.empty();
}

bool TutorialStage::hasPosttext() {
	return !postText.empty();
}

string TutorialStage::getTaskText() {
	return tasks.front().taskText;
}

string TutorialStage::popPretext() {
	string ret = preText.front();
	preText.pop();
	return ret;
}

string TutorialStage::popPosttext() {
	string ret = postText.front();
	postText.pop();
	return ret;
}