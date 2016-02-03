#pragma once
#include <stack>

class GameState;
#include "GameState.h"
using state_ptr = std::shared_ptr<GameState>;

class GameStateManager {
public:
	GameStateManager() : state_is_running(false) {}
	void runState(GameState* state);
	void stopState(GameState* state);
	void pauseState(GameState* state);
private:
	bool state_is_running;
	std::stack<GameState*> state_stack;

};