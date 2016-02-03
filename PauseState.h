#pragma once

#include "GameState.h"

class PauseState : public GameState {
public:
	explicit PauseState(GameStateManager*, InputHandler*, sf::RenderWindow*);
	virtual void init();
	virtual void update();
	virtual void draw();
	virtual void recieveKeysDown(std::list<int> &notes);
	virtual void unhookEvent();
private:
	GameStateManager *gsm;
	InputHandler *inputHandler;
	sf::RenderWindow *window;
};