#pragma once
#include <memory>

#include "input.h"
#include "GameStateManager.h"
#include "Player.h"
#include "AssetManager.h"
#include "CollisionManager.h"
#include <SFML/Graphics.hpp>

//#define WINDOW_WIDTH 1280 1920
//#define WINDOW_HEIGHT 600 1080
//#define BEAT_SPEED 250.0f
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define BEAT_SPEED 500.0f
#define GROUND WINDOW_WIDTH / 4


// Struct for data we want shared between states
// GameStateManager and RenderWindow are references instead of pointers because they should never be reinitialized.
// InputHandler is a pointer because the eventhook method needs a pointer.
// Game itself should also be passed and stored as a reference as it should never need to be reinitialized.
struct Game {
	Game(GameStateManager &_gsm, CollisionManager &_collisionManager, std::shared_ptr<InputHandler> _inputHandler, sf::RenderWindow &_window) : 
		gsm(_gsm), 
		collisionManager(_collisionManager),
		inputHandler(_inputHandler), 
		window(_window) 
	{ }

	// Reference to the game state manager for stopping/starting new states within a state
	GameStateManager& gsm;
	CollisionManager& collisionManager;
	// Pointer to the input handler to be passed to event hooking method
	std::shared_ptr<InputHandler> inputHandler;

	// Reference to SFML window
	sf::RenderWindow& window;

	AssetManager currentScreen;
	Player playerOne;
	Player playerTwo;
	
	// Beat is in milliseconds, 1000 = 1 beat every 1 second
	float beat = BEAT_SPEED;
};
