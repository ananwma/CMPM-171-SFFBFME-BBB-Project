#include "stdafx.h"
#include <assert.h>
#include <iostream>

#include "GameStateManager.h"
#include "GameState.h"

#define UPDATERATE 6

using namespace std;

void GameStateManager::runState(GameState &state) {
	assert(!state_is_running && "Error, only one state can be ran at a time");
	state_is_running = true;
	state_stack.push(&state);
	state.init();
	while (state_is_running) {
		//if (updateClock.getElapsedTime().asMilliseconds() > UPDATERATE) {
			state.update();
			state.draw();
			//updateClock.restart();
		//}
	}
	state.unhookEvent();
}

void GameStateManager::stopState(GameState&) {
	state_stack.pop();
	state_is_running = false;
}

//unhook events in here?
void GameStateManager::stopState(GameState &stateStop, GameState *stateRun) {
	state_stack.pop();
	state_is_running = false;
	runState(*stateRun);
}

void GameStateManager::pauseState(GameState &state) {
	state_is_running = false;
}