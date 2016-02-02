#include "stdafx.h"
#include <iostream>

#include <SFML/Graphics.hpp>
#include "FightState.h"
#include "GameStateManager.h"

using namespace std;

// Some globals for testing
sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
sf::CircleShape shape(100.f);

FightState::FightState(GameStateManager *_gsm, InputHandler *inputHandler) : gsm(_gsm) {
	//Can probably move this to GameState.cpp and just call super
	__hook(&InputHandler::sendKeysDown, inputHandler, &GameState::recieveKeysDown);
}

void FightState::init() {
	shape.setFillColor(sf::Color::Green);
}

void FightState::update() {
	cout << "State #1" << endl;
}

void FightState::draw() {
	window.clear();
	window.draw(shape);
	window.display();
}

void FightState::recieveKeysDown(list<int> &notes) {
	gsm->stopState(state_ptr(this));
}