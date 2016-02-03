#include "stdafx.h"
#include <iostream>

#include <SFML/Graphics.hpp>
#include "PauseState.h"
#include "GameStateManager.h"

using namespace std;

// Some globals for testing
sf::CircleShape shape2(100.f);

PauseState::PauseState(GameStateManager *_gsm, InputHandler *_inputHandler, sf::RenderWindow *_window) : gsm(_gsm), inputHandler(_inputHandler), window(_window) {
	
}


void PauseState::init() {
	__hook(&InputHandler::sendKeysDown, inputHandler, &GameState::recieveKeysDown);
	shape2.setFillColor(sf::Color::Red);
}

void PauseState::update() {
	//cout << "State #2" << endl;
}

void PauseState::draw() {
	window->clear();
	window->draw(shape2);
	window->display();
}

void PauseState::recieveKeysDown(list<int> &notes) {
	cout << " recieve2 ";
	gsm->stopState(this);
}