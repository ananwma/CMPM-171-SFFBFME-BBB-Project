#include "stdafx.h"
#include <iostream>

#include "PlayerSelectState.h"
#include "FightState.h"


using namespace std;

PlayerSelectState::PlayerSelectState(Game &_game) : game(_game) { }

void PlayerSelectState::init() {
	running = true;
	__hook(&InputHandler::sendKeysDown, game.inputHandler.get(), &GameState::receiveKeysDown);
	cout << "__Player 1 press a key__" << endl;
}

void PlayerSelectState::update() {

	sf::Event event;
	if (game.window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			game.window.close();
			break;
		}
	}

	if (!running) {
		unhookEvent();
		FightState fightState(game);
		game.gsm.stopState(*this, &fightState);
	}

}

void PlayerSelectState::draw() {

}

// Everything here is run on its own thread!
void PlayerSelectState::receiveKeysDown(int note, int playerId) {
	if (game.playerOne.playerId != -1 && playerId != game.playerOne.playerId) {
		game.playerTwo.playerId = playerId;
		running = false;
		game.inputHandler->prepareOutput(playerId);
	}
	if (game.playerOne.playerId == -1) {
		game.playerOne.playerId = playerId;
		cout << "__Player 2 press a key__" << endl;
	}
}

void PlayerSelectState::unhookEvent() {
	cout << "PlayerSelectState events unhooked\n";
	__unhook(&InputHandler::sendKeysDown, game.inputHandler.get(), &GameState::receiveKeysDown);
}