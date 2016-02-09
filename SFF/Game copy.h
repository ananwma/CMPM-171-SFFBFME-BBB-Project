#pragma once
#include <memory>

#include "input.h"
#include "GameStateManager.h"
#include <SFML/Graphics.hpp>

// Struct for data we want shared between states
// GameStateManager and RenderWindow are references instead of pointers because they should never be reinitialized.
// InputHandler is a pointer because the eventhook method needs a pointer.
// Game itself should also be passed and stored as a reference as it should never need to be reinitialized.
struct Game {
	Game(GameStateManager &_gsm, std::shared_ptr<InputHandler> _inputHandler, sf::RenderWindow &_window) : gsm(_gsm), inputHandler(_inputHandler), window(_window) {
	}

	// Reference to the game state manager for stopping/starting new states within a state
	GameStateManager& gsm;

	// Pointer to the input handler to be passed to event hooking method
	std::shared_ptr<InputHandler> inputHandler;

	// Reference to SFML window
	sf::RenderWindow& window;
};
