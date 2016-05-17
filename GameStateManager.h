#pragma once
#include <memory>
#include <stack>

#include "GameState.h"

class GameStateManager {
public:
	// CTOR
	GameStateManager() : state_is_running(false) {}

	// Runs state, pushes onto stack
	void runState(GameState&);

	// Stops state, clears state stack
	void stopState(GameState&);

	// Stops current state, clears state stack, runs given state
	void stopState(GameState&, GameState*);

	// Stops current state, does not pop off stack
	void pauseState(GameState & statePause, GameState * stateRun);

	// Stops and pops current state; runs the next state on the stack
	void resumeLastState();

private:
	bool state_is_running;
	bool resuming_state = false;
	std::stack<GameState*> state_stack;
	std::unique_ptr<GameState> currentState;
	sf::Clock updateClock;
};