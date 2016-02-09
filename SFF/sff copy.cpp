#include "stdafx.h"
#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <SFML/Graphics.hpp>

//DEBUG
#include <vld.h>
//DEBUG

#include "input.h"
#include "GameStateManager.h"
#include "FightState.h"
#include "PauseState.h"
#include "Game.h"

using namespace std;


int main()
{
	// Get a console for debugging with cout
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	
	// View number of connected devices (useful for debugging)
	int numDevs = midiInGetNumDevs();
	cout << endl << "Num Devs: " << numDevs << endl;

	// Initialize the main window, input handler, and gamestate manager
	shared_ptr<InputHandler> inputHandler(new InputHandler());
	inputHandler->prepareDevices();
	GameStateManager gsm;
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	Game game(gsm, inputHandler, window);

	// Run the first state
	FightState fsp(game);
	gsm.runState(fsp);
	return 0;
}