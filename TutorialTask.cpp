#include "TutorialTask.h"
#include "Player.h"
#include "TutorialState.h"

TutorialTask::TutorialTask()
{

}

TutorialTask::TutorialTask(string tsk)
{
	taskComplete = false;
	task = tsk;
	
}

void TutorialTask::testTask(Player& player) {
	if (task == "Move Backward") {
		if (player.state == WALK_STATE && player.xvel < 0) {
			taskComplete = true;
		}
	}
	if (task == "Move Forward") {
		if (player.state == WALK_STATE && player.xvel > 0) {
			taskComplete = true;
		}
	}
	
	taskComplete = false;
}
