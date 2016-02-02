#pragma once

#include "GameState.h"

class FightState : public GameState {
public:
	explicit FightState(GameStateManager*, InputHandler*);
	virtual void init();
	virtual void update();
	virtual void draw();
	virtual void recieveKeysDown(std::list<int> &notes);
private:
	GameStateManager *gsm;
};
