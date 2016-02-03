#include "stdafx.h"
#include <iostream>

#include "FightState.h"
#include "GameStateManager.h"

using namespace std;

// Some globals for testing
sf::CircleShape shape(100.f);

FightState::FightState(GameStateManager *_gsm, InputHandler *_inputHandler, sf::RenderWindow *_window) : gsm(_gsm), inputHandler(_inputHandler), window(_window) {
	//Can possibly move this to GameState.cpp and just call super
	
}

void FightState::init() {
	shape.setFillColor(sf::Color::Green);
	__hook(&InputHandler::sendKeysDown, inputHandler, &GameState::recieveKeysDown);
}

void FightState::update() {
	//cout << "State #1" << endl;
}

void FightState::draw() {
	window->clear();
	window->draw(shape);
	window->display();
}

void FightState::recieveKeysDown(list<int> &notes) {
	cout << " recieve1 ";
	gsm->stopState(this);
}