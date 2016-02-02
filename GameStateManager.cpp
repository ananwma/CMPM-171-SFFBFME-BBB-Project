#include "stdafx.h"
#include <assert.h>
#include <iostream>

#include "GameStateManager.h"
#include "GameState.h"
using namespace std;

void GameStateManager::runState(state_ptr state) {
	assert(!state_is_running && "Error, only one state can be ran at a time");
	state_is_running = true;
	state_stack.push(state);
	state->init();
	while (state_is_running) {
		state->update();
		state->draw();
	}
}

void GameStateManager::stopState(state_ptr state) {
	state_is_running = false;
	state_stack.pop();
	// Runs next state in stack, not sure if that's what we want but I left it in just in case
	if (!state_stack.empty()) {
		runState(state_stack.top());
	}
}

void GameStateManager::pauseState(state_ptr state) {
	state_is_running = false;
	state_stack.push(state);
}