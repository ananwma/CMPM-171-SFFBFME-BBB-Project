#include "GameState.h"
#include "input.h"


GameState::init() {
	__hook(&InputHandler::sendKeysDown, inputHandler, &GameState::recieveKeysDown);
}

GameState::unhookEvent() {
	__unhook(&InputHandler::sendKeysDown, inputHandler.get(), &GameState::recieveKeysDown);
}