#include "stdafx.h"
#include <iostream>

#include "PlayerSelectState.h"
#include "FightState.h"


using namespace std;

PlayerSelectState::PlayerSelectState(Game &_game) : game(_game) { }

void PlayerSelectState::init() {
	running = true;
	__hook(&InputHandler::sendKeysDown, game.inputHandler.get(), &GameState::recieveKeysDown);
	cout << "__Player 1 press a key__" << endl;
}

void PlayerSelectState::update() {
	if (!running) {
		FightState fightState(game);
		game.gsm.stopState(*this, &fightState);
	}
}

void PlayerSelectState::draw() {

}

// Everything here is run on its own thread!
void PlayerSelectState::recieveKeysDown(std::list<int>& notes, int playerId) {
	if (game.playerOne.playerId != -1 /*&& playerId != game.playerOne.playerId*/) {
		game.playerTwo.playerId = playerId;
		running = false;
	}
	if (game.playerOne.playerId == -1) {
		game.playerOne.playerId = playerId;
		cout << "__Player 2 press a key__" << endl;
	}
}

void PlayerSelectState::unhookEvent() {
	__unhook(&InputHandler::sendKeysDown, game.inputHandler.get(), &GameState::recieveKeysDown);
}