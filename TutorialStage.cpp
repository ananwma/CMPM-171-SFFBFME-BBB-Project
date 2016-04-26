#include "stdafx.h"
#include "TutorialStage.h"

TutorialStage::TutorialStage()
{

}

TutorialStage::TutorialStage(stack<string> pre, stack<string> post , vector<TutorialTask> tsks)
{
	stagecomplete = false;
	preTextRead = false;
	preText = pre;
	postText = post;
	tasks = tsks;
}