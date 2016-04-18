#include "stdafx.h"
#include "TutorialStage.h"
#include "TutorialTask.h"

TutorialStage::TutorialStage()
{

}

TutorialStage::TutorialStage(stack<string> pre, stack<string> post , vector<TutorialTask> tsks)
{
	stagecomplete = false;
	preText = pre;
	postText = post;
	tasks = tsks;
}