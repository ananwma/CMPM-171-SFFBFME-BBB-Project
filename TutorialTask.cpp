#include "TutorialTask.h"
#include "TutorialState.h"

bool TutorialTask::testTask(Player& player) {


	if ((player.state == checkState || checkState == -1) &&
		(player.getVelocity().x > checkXvelGreaterThan) && 
		(player.getVelocity().x < checkXvelLessThan) &&
		(player.getVelocity().y > checkYvelGreaterThan) &&
		(player.getVelocity().y < checkYvelLessThan) &&
		(player.getCurrentMoveName() == checkMove || checkMove == "")) {
		numComplete++;
	}
	return numComplete >= checkComplete;
}