#include "stdafx.h"
#include <iostream>

#include "FightState.h"
#include "PauseState.h"

using namespace std;

// Some globals for testing
sf::CircleShape shape(100.f);

FightState::FightState(Game &_game) : game(_game) { }

void FightState::init() {
	running = true;
	shape.setFillColor(sf::Color::Green);
	__hook(&InputHandler::sendKeysDown, game.inputHandler.get(), &GameState::recieveKeysDown);
}

void FightState::update() {
	//cout << "State #1" << endl;
	if (!running) {
		PauseState pauseState(game);
		game.gsm.stopState(*this, &pauseState);
	}
}

void FightState::draw() {
	game.window.clear();
	game.window.draw(shape);
	game.window.display();
}

// Everything here is run on its own thread!
void FightState::recieveKeysDown(list<int> &notes) {
	cout << " recieve1 " << endl;
	running = false;
}

void FightState::unhookEvent() {
	__unhook(&InputHandler::sendKeysDown, game.inputHandler.get(), &GameState::recieveKeysDown);
}
