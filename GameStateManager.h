#pragma once
#include <stack>

class GameState;
#include "GameState.h"
using state_ptr = std::shared_ptr<GameState>;

class GameStateManager {
public:
	GameStateManager() : state_is_running(false) {}
	void runState(state_ptr state);
	void stopState(state_ptr state);
	void pauseState(state_ptr state);
private:
	bool state_is_running;
	std::stack<state_ptr> state_stack;

};