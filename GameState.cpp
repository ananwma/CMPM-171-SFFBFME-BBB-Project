#include "GameState.h"
#include "input.h"

//GameState::~GameState() {
//	__unhook(&InputHandler::sendKeysDown, inputHandler, &GameState::recieveKeysDown);
//}

GameState::init() {
	__hook(&InputHandler::sendKeysDown, inputHandler, &GameState::recieveKeysDown);
}