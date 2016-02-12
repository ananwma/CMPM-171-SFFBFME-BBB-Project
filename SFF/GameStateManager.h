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

	// Stops state, pops off stack
	void stopState(GameState&);

	// Stops current state and runs given state
	void stopState(GameState&, GameState*);

	// Stops current state, does not pop off stack
	void pauseState(GameState&);

private:
	bool state_is_running;
	std::stack<GameState*> state_stack;
	std::unique_ptr<GameState> currentState;
};