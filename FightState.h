#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.h"

class FightState : public GameState {
public:
	explicit FightState(GameStateManager*, InputHandler*, sf::RenderWindow*);
	virtual void init();
	virtual void update();
	virtual void draw();
	virtual void recieveKeysDown(std::list<int> &notes);
	virtual void unhookEvent();
	//Need function (possibly dtor) to unhook event

private:
	GameStateManager *gsm;
	InputHandler *inputHandler;
	sf::RenderWindow *window;
};
