#include "stdafx.h"
#include <iostream>

#include "PauseState.h"


using namespace std;

// Some globals for testing
sf::CircleShape shape2(50.f);

PauseState::PauseState(Game &_game) : game(_game) { }

void PauseState::init() {
	running = true;
	__hook(&InputHandler::sendKeysDown, game.inputHandler.get(), &GameState::recieveKeysDown);
	shape2.setFillColor(sf::Color::Red);
}

void PauseState::update() {
	//cout << "State #2" << endl;
}

void PauseState::draw() {
	game.window.clear();
	game.window.draw(shape2);
	game.window.display();
}

// Everything here is run on its own thread!
void PauseState::recieveKeysDown(list<int> &notes) {
	cout << " recieve2 " << endl;
	game.gsm.stopState(*this);
}

void PauseState::unhookEvent() {
	__unhook(&InputHandler::sendKeysDown, game.inputHandler.get(), &GameState::recieveKeysDown);
}