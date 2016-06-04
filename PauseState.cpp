#include "stdafx.h"
#include <iostream>

#include "PauseState.h"
#include "MainMenuState.h"
//#include "FightState.h"

#define PADDING 20

using namespace std;


PauseState::PauseState(Game &_game) : game(_game) { }

void PauseState::init() {
	running = true;

	if (!Ctex.loadFromFile("sprites/C.png") || !Etex.loadFromFile("sprites/E.png") || !Gtex.loadFromFile("sprites/G.png")) {
		std::cerr << "Error missing C/E/G sprites!\n";
		exit(EXIT_FAILURE);
	}
	C.setTexture(Ctex);
	E.setTexture(Etex);
	G.setTexture(Gtex);
	C.scale(0.1, 0.1);
	E.scale(0.1, 0.1);
	G.scale(0.1, 0.1);

	if (!font1.loadFromFile("fonts/Altgotisch.ttf") || !font2.loadFromFile("fonts/asul.regular.ttf")) {
		cerr << "Font not found!\n";
		exit(EXIT_FAILURE);
	}

	window.setSize(sf::Vector2f(WINDOW_WIDTH / 1.5, WINDOW_HEIGHT / 2));
	window.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - window.getLocalBounds().width / 2, WINDOW_HEIGHT / 2 - window.getLocalBounds().height / 2));
	window.setFillColor(sf::Color(91, 15, 0));

	pauseText.setFont(font1);
	pauseText.setColor(sf::Color(255, 174, 1));
	pauseText.setCharacterSize(100);
	pauseText.setString("Paused");
	pauseText.setPosition(window.getPosition().x + window.getSize().x / 2 - pauseText.getLocalBounds().width / 2, window.getPosition().y);

	resumeText.setFont(font2);
	resumeText.setColor(sf::Color(255, 174, 1));
	resumeText.setCharacterSize(50);
	menuText = resumeText;
	restartText = resumeText;
	resumeText.setString("Resume");
	menuText.setString("Main Menu");
	restartText.setString("Restart");

	C.setPosition(window.getPosition().x + PADDING, pauseText.getPosition().y + pauseText.getGlobalBounds().height + PADDING + 30); //+30 is temporary
	E.setPosition(window.getPosition().x + PADDING, C.getPosition().y + C.getGlobalBounds().height + PADDING);
	G.setPosition(window.getPosition().x + PADDING, E.getPosition().y + E.getGlobalBounds().height + PADDING);

	resumeText.setPosition(C.getPosition().x + C.getGlobalBounds().width, C.getPosition().y);
	menuText.setPosition(E.getPosition().x + E.getGlobalBounds().width, E.getPosition().y);
	restartText.setPosition(G.getPosition().x + G.getGlobalBounds().width, G.getPosition().y);
}

void PauseState::hookEvent() {
	__hook(&InputHandler::sendKeysDown, game.inputHandler.get(), &PauseState::receiveKeysDown);
}

void PauseState::update() {
	sf::Event event;
	if (game.window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			game.window.close();
			break;
		}
	}
	if (resume) {
		unhookEvent();
		game.gsm.resumeLastState();
	}
	if (menu) {
		game.playerOne.roundWins = 0;
		game.playerTwo.roundWins = 0;
		game.playerOne.meter = 0;
		game.playerTwo.meter = 0;
		game.playerOne.health = 0;
		game.playerTwo.health = 0;
		unhookEvent();
		MainMenuState menuState(game);
		game.gsm.stopState(*this, &menuState);
	}
	if (restart) {
		//todo
	}
}

void PauseState::draw() {
	game.window.draw(window);
	game.window.draw(pauseText);
	game.window.draw(resumeText);
	game.window.draw(menuText);
	//game.window.draw(restartText);
	game.window.draw(C);
	game.window.draw(E);
	//game.window.draw(G);
	game.window.display();
}

// Everything here is run on its own thread!
void PauseState::receiveKeysDown(int note, int playerId) {
	switch (note % 12) {
	case 0: 
		resume = true;
		break;
	case 4: 
		menu = true;
		break;
	case 7: 
		restart = true;
		break;
	}
}

void PauseState::unhookEvent() {
	cout << "Pause events unhooked\n";
	__unhook(&InputHandler::sendKeysDown, game.inputHandler.get(), &PauseState::receiveKeysDown);
}