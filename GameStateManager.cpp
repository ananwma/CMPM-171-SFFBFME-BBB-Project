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
	if (!resuming_state)
		state.init();
	state.hookEvent();
	resuming_state = false;
	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.f / 60.0f);
	while (state_is_running) {
		while (accumulator > ups) {
			//if (updateClock.getElapsedTime().asMilliseconds() > UPDATERATE) {
			accumulator -= ups;
			state.update();
			//updateClock.restart();
		//}
		}

		state.draw();
		accumulator += clock.restart();
	}
	state.unhookEvent();
}

void GameStateManager::stopState(GameState&) {
	while (!state_stack.empty())
		state_stack.pop();
	state_is_running = false;
}

//unhook events in here?
void GameStateManager::stopState(GameState &stateStop, GameState *stateRun) {
	while (!state_stack.empty())
		state_stack.pop();
	state_is_running = false;
	runState(*stateRun);
}

void GameStateManager::pauseState(GameState &statePause, GameState *stateRun) {
	//GameState* push = &statePause;
	state_is_running = false;
	state_stack.push(&statePause);
	runState(*stateRun);
}

void GameStateManager::resumeLastState() {
	state_is_running = false;
	resuming_state = true;
	state_stack.pop();
	GameState* stateRun = state_stack.top();
	state_stack.pop();
	runState(*stateRun);
}