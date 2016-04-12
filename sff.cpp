#include "stdafx.h"
#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <SFML/Graphics.hpp>

//DEBUG
#include <vld.h>
//DEBUG

#include "input.h"
#include "PlayerSelectState.h"
#include "GameStateManager.h"
#include "CollisionManager.h"
#include "FightState.h"
#include "PauseState.h"
#include "Game.h"

//tmp
#include "Player.h"

using namespace std;


int main()
{
	// Get a console for debugging with cout
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	
	// View number of connected devices (useful for debugging)
	cout << endl << "Num Input Devs: " << midiInGetNumDevs() << endl;
	cout << endl << "Num Output Devs: " << midiOutGetNumDevs() << endl;

	// Initialize the main window, input handler, and gamestate manager
	shared_ptr<InputHandler> inputHandler(new InputHandler());
	inputHandler->prepareDevices();
	GameStateManager gsm;
	Collision collisionManager;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Super Fugue Fighter");
	//window.setFramerateLimit(60);
	Game game(gsm, collisionManager, inputHandler, window);

	// Run the first state
	PlayerSelectState pss(game);
	gsm.runState(pss);
	//FightState fs(game);
	//gsm.runState(fs);
	return 0;
}