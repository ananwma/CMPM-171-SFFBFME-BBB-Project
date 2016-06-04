#include "stdafx.h"
#include <iostream>

#include "ResultsState.h"
#include "MainMenuState.h"
#include "FightState.h"

#define PADDING 20

using namespace std;

ResultsState::ResultsState(Game &_game) : game(_game) { }

void ResultsState::init() {
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

	window.setSize(sf::Vector2f(WINDOW_WIDTH / 1.5, WINDOW_HEIGHT / 3.5));
	window.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - window.getLocalBounds().width / 2, WINDOW_HEIGHT / 2 - window.getLocalBounds().height / 4));
	window.setFillColor(sf::Color(91, 15, 0, 20));
	window.setOutlineThickness(20);
	window.setOutlineColor(sf::Color(43, 43, 43));

	pauseText.setFont(font1);
	pauseText.setColor(sf::Color(255, 174, 1));
	pauseText.setCharacterSize(100);
	pauseText.setString("Game Over");
	pauseText.setPosition(window.getPosition().x + window.getSize().x / 2 - pauseText.getLocalBounds().width / 2, window.getPosition().y);

	resumeText.setFont(font2);
	resumeText.setColor(sf::Color(255, 174, 1));
	resumeText.setCharacterSize(50);
	menuText = resumeText;
	restartText = resumeText;
	resumeText.setString("Rematch");
	menuText.setString("Main Menu");
	restartText.setString("Restart");

	C.setPosition(window.getPosition().x + PADDING, pauseText.getPosition().y + pauseText.getGlobalBounds().height + PADDING + 30); //+30 is temporary
	E.setPosition(window.getPosition().x + PADDING, C.getPosition().y + C.getGlobalBounds().height + PADDING);
	G.setPosition(window.getPosition().x + PADDING, E.getPosition().y + E.getGlobalBounds().height + PADDING);

	resumeText.setPosition(C.getPosition().x + C.getGlobalBounds().width, C.getPosition().y);
	menuText.setPosition(E.getPosition().x + E.getGlobalBounds().width, E.getPosition().y);
	restartText.setPosition(G.getPosition().x + G.getGlobalBounds().width, G.getPosition().y);

	p1WinTex.loadFromFile("sprites/p1win.png");
	p2WinTex.loadFromFile("sprites/p2win.png");
	drawTex.loadFromFile("sprites/draw.png");
	if (game.playerOne.roundWins > game.playerTwo.roundWins)
		endText.setTexture(p1WinTex);
	else if (game.playerOne.roundWins < game.playerTwo.roundWins)
		endText.setTexture(p2WinTex);
	else {
		endText.setTexture(drawTex);
	}
	endText.setPosition(WINDOW_WIDTH / 2 - endText.getGlobalBounds().width / 2, WINDOW_HEIGHT / 2 - endText.getGlobalBounds().height - 20);
	game.playerOne.roundWins = 0;
	game.playerTwo.roundWins = 0;
	game.playerOne.meter = 0;
	game.playerTwo.meter = 0;
	game.playerOne.health = 0;
	game.playerTwo.health = 0;
}

void ResultsState::hookEvent() {
	__hook(&InputHandler::sendKeysDown, game.inputHandler.get(), &ResultsState::receiveKeysDown);
}

void ResultsState::update() {
	sf::Event event;
	if (game.window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			game.window.close();
			break;
		}
	}
	if (resume) {
		resumeText.setColor(sf::Color(255, 200, 200));
		C.setColor(sf::Color(255, 200, 200));
		game.window.draw(resumeText);
		game.window.draw(C);
		game.window.display();
		unhookEvent();
		FightState fightState(game);
		game.gsm.stopState(*this, &fightState);
	}
	if (menu) {
		menuText.setColor(sf::Color(255, 200, 200));
		E.setColor(sf::Color(255, 200, 200));
		game.window.draw(menuText);
		game.window.draw(E);
		game.window.display();
		unhookEvent();
		MainMenuState menuState(game);
		game.gsm.stopState(*this, &menuState);
	}
	if (restart) {
		//todo
	}
}

void ResultsState::draw() {
	game.window.draw(window);
	game.window.draw(pauseText);
	game.window.draw(resumeText);
	game.window.draw(menuText);
	//game.window.draw(restartText);
	game.window.draw(C);
	game.window.draw(E);
	//game.window.draw(G);
	game.window.draw(endText);
	game.window.display();
}

// Everything here is run on its own thread!
void ResultsState::receiveKeysDown(int note, int playerId) {
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

void ResultsState::unhookEvent() {
	cout << "Result events unhooked\n";
	__unhook(&InputHandler::sendKeysDown, game.inputHandler.get(), &ResultsState::receiveKeysDown);
}