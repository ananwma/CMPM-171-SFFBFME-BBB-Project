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
