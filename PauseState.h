#pragma once

#include "GameState.h"

class PauseState : public GameState {
public:
	explicit PauseState(GameStateManager*, InputHandler*);
	virtual void init();
	virtual void update();
	virtual void draw();
	virtual void recieveKeysDown(std::list<int> &notes);
private:
	GameStateManager *gsm;
};