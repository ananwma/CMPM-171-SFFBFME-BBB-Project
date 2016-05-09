#include "TutorialTask.h"
#include "Player.h"
#include "TutorialState.h"

bool TutorialTask::testTask(Player& player) {


	if ((player.state == checkState || checkState == -1) &&
		(player.xvel > checkXvelGreaterThan) && 
		(player.xvel < checkXvelLessThan) &&
		(player.yvel > checkYvelGreaterThan) &&
		(player.yvel < checkYvelLessThan) && 
		(player.getCurrentMoveNum() == checkMove || checkMove == -1)) {
		numComplete++;
	}
	return numComplete >= checkComplete;
}