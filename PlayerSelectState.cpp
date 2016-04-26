#include "stdafx.h"
#include <iostream>

#include "PlayerSelectState.h"
#include "MainMenuState.h"


using namespace std;

PlayerSelectState::PlayerSelectState(Game &_game) : game(_game) { }

void PlayerSelectState::init() {
	running = true;
	__hook(&InputHandler::sendKeysDown, game.inputHandler.get(), &GameState::receiveKeysDown);
	cout << "__Player 1 press a key__" << endl;

	if (!keyboardTex.loadFromFile("sprites/keyboard_small.png")) {
		std::cerr << "Error missing keyboard_small.png sprites!\n";
		exit(EXIT_FAILURE);
	}
	keyboard1.setTexture(keyboardTex);
	keyboard2.setTexture(keyboardTex);
	keyboard1.scale(0.25, 0.25);
	keyboard2.scale(0.25, 0.25);
	keyboard1.setOrigin(keyboard1.getLocalBounds().width / 2, keyboard1.getLocalBounds().height / 2);
	keyboard2.setOrigin(keyboard2.getLocalBounds().width / 2, keyboard2.getLocalBounds().height / 2);
	keyboard1.setPosition(WINDOW_WIDTH / 4, WINDOW_HEIGHT - WINDOW_HEIGHT / 4);
	keyboard2.setPosition(WINDOW_WIDTH - WINDOW_WIDTH / 4, WINDOW_HEIGHT - WINDOW_HEIGHT / 4);


	// Load text
	if (!font.loadFromFile("fonts/Altgotisch.ttf")) {
		cerr << "Font not found!\n";
		exit(EXIT_FAILURE);
	}

	pressAKey.setFont(font);
	pressAKey.setColor(sf::Color(255, 174, 1));
	pressAKey.setCharacterSize(100);
	pressAKey.setString("Player one press a key");
	pressAKey.setPosition(WINDOW_WIDTH / 2 - pressAKey.getLocalBounds().width / 2, WINDOW_HEIGHT / 4);
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
		MainMenuState mainMenuState(game);
		game.gsm.stopState(*this, &mainMenuState);
	}

	if (p1Pressed) {
		keyboard1.setColor(sf::Color(255, 255, 255, fade1));
		keyboard1.scale(1.1, 1.1);
		fade1 -= 20;
		if (fade1 < 0)
			fade1 = 0;
	}
	if (p2Pressed) {
		keyboard2.setColor(sf::Color(255, 255, 255, fade2));
		keyboard2.scale(1.1, 1.1);
		fade2 -= 20;
		if (fade2 < 0)
			fade2 = 0;
		cout << fade2<<endl;
	}
	if (fade2 == 0) {
		running = false;
	}
	keyboard1.rotate(cos(rot));
	keyboard2.rotate(cos(rot));
	rot += 0.1;
}

void PlayerSelectState::draw() {
	game.window.clear(sf::Color(91, 15, 0));
	game.window.draw(keyboard1);
	game.window.draw(keyboard2);
	game.window.draw(pressAKey);
	game.window.display();
}

// Everything here is run on its own thread!
void PlayerSelectState::receiveKeysDown(int note, int playerId) {
	if (game.playerOne.playerId != -1 && playerId != game.playerOne.playerId) {
		game.playerTwo.playerId = playerId;
		p2Pressed = true;
		//running = false;
		//game.inputHandler->prepareOutput(playerId);
	}
	if (game.playerOne.playerId == -1) {
		game.playerOne.playerId = playerId;
		pressAKey.setString("Player two press a key");
		pressAKey.setPosition(WINDOW_WIDTH / 2 - pressAKey.getLocalBounds().width / 2, WINDOW_HEIGHT / 4);
		p1Pressed = true;
		cout << "__Player 2 press a key__" << endl;
	}
}

void PlayerSelectState::unhookEvent() {
	cout << "PlayerSelectState events unhooked\n";
	__unhook(&InputHandler::sendKeysDown, game.inputHandler.get(), &GameState::receiveKeysDown);
}