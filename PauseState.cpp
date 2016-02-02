#include "stdafx.h"
#include <iostream>

#include <SFML/Graphics.hpp>
#include "PauseState.h"
#include "GameStateManager.h"

using namespace std;

// Some globals for testing
sf::RenderWindow window2(sf::VideoMode(200, 200), "SFML works!");
sf::CircleShape shape2(100.f);

PauseState::PauseState(GameStateManager *_gsm, InputHandler *inputHandler) : gsm(_gsm) {
	__hook(&InputHandler::sendKeysDown, inputHandler, &GameState::recieveKeysDown);
}


void PauseState::init() {

	shape2.setFillColor(sf::Color::Red);
}

void PauseState::update() {
	cout << "State #2" << endl;
}

void PauseState::draw() {
	window2.clear();
	window2.draw(shape2);
	window2.display();
}

void PauseState::recieveKeysDown(list<int> &notes) {
	gsm->stopState(state_ptr(this));
}