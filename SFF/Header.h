#pragma once

#include "input.h"
#include "GameStateManager.h"
#include <SFML/Graphics.hpp>

// Struct for data we want shared between states
struct context {
	context(InputHandler* _input_handler, GameStateManager* _game_state_manager, sf::RenderWindow* _window) :
		input_handler(_input_handler), game_state_manager(_game_state_manager), window(_window) {}

	~context() {
		delete input_handler;
		delete game_state_manager;
		delete window;
	}

	InputHandler* input_handler;
	GameStateManager* game_state_manager;
	sf::RenderWindow* window;

};
