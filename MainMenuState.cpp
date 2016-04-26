#include "stdafx.h"
#include <iostream>

#include "MainMenuState.h"
#include "FightState.h"

#define PADDING WINDOW_HEIGHT/20


using namespace std;

MainMenuState::MainMenuState(Game &_game) : game(_game) { }

void MainMenuState::init() {
	running = true;
	__hook(&InputHandler::sendKeysDown, game.inputHandler.get(), &GameState::receiveKeysDown);

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
	G.setColor(sf::Color(255, 255, 255, 40));

	// Load text
	if (!font.loadFromFile("fonts/Altgotisch.ttf")) {
		cerr << "Font not found!\n";
		exit(EXIT_FAILURE);
	}

	rect1.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT / 40));
	rect1.setFillColor(sf::Color(255, 174, 1));
	rect2 = rect1;
	rect3 = rect1;
	rect3.setFillColor(sf::Color(255, 174, 1, 40));

	versus.setFont(font);
	versus.setColor(sf::Color(255, 174, 1));
	versus.setCharacterSize(100);
	tutorial = versus;
	options = versus;
	options.setColor(sf::Color(255, 174, 1, 40));
	versus.setString("Versus");
	tutorial.setString("Tutorial");
	options.setString("Options");

	versus.setPosition(WINDOW_WIDTH, WINDOW_HEIGHT / 4);
	tutorial.setPosition(WINDOW_WIDTH, WINDOW_HEIGHT / 4 + versus.getLocalBounds().height + PADDING);
	options.setPosition(WINDOW_WIDTH, WINDOW_HEIGHT / 4 + versus.getLocalBounds().height + tutorial.getLocalBounds().height + PADDING);

	versusPos = WINDOW_WIDTH / 2 - versus.getLocalBounds().width / 2;
	tutorialPos = WINDOW_WIDTH / 2 - tutorial.getLocalBounds().width / 2 + versus.getLocalBounds().width;
	optionsPos = WINDOW_WIDTH / 2 - options.getLocalBounds().width / 2 + versus.getLocalBounds().width + tutorial.getLocalBounds().width;

	//tutorial.setPosition(WINDOW_WIDTH / 2 - versus.getLocalBounds().width / 2, WINDOW_HEIGHT / 4 + versus.getLocalBounds().height + PADDING);
	//options.setPosition(WINDOW_WIDTH / 2 - versus.getLocalBounds().width / 2, WINDOW_HEIGHT / 4 + versus.getLocalBounds().height + PADDING + tutorial.getLocalBounds().height + PADDING);

	//tutorial.setPosition((WINDOW_WIDTH / 2 - tutorial.getLocalBounds().width / 2) + versus.getLocalBounds().width, WINDOW_HEIGHT / 4 + versus.getLocalBounds().height + PADDING);
	//options.setPosition(WINDOW_WIDTH / 2 - options.getLocalBounds().width / 2 + versus.getLocalBounds().width + tutorial.getLocalBounds().width, WINDOW_HEIGHT / 4 + versus.getLocalBounds().height + tutorial.getLocalBounds().height + PADDING);

	rect1.setPosition(WINDOW_WIDTH, versus.getPosition().y + versus.getLocalBounds().height);
	rect3.setPosition(WINDOW_WIDTH, options.getPosition().y + options.getLocalBounds().height);
	rect2.setPosition(WINDOW_WIDTH, tutorial.getPosition().y + tutorial.getLocalBounds().height);
	C.setPosition(WINDOW_WIDTH, versus.getPosition().y + PADDING);
	E.setPosition(WINDOW_WIDTH, tutorial.getPosition().y + PADDING);
	G.setPosition(WINDOW_WIDTH, options.getPosition().y+ PADDING);
}

void MainMenuState::update() {

	sf::Event event;
	if (game.window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			game.window.close();
			break;
		}
	}
	if (!versusSelect && !tutorialSelect) {
		if (versus.getPosition().x > versusPos) versus.move(-25, 0);
		if (tutorial.getPosition().x > tutorialPos) tutorial.move(-25, 0);
		if (options.getPosition().x > optionsPos) options.move(-25, 0);
		if (C.getPosition().x > versusPos - C.getGlobalBounds().width - PADDING) C.move(-25, 0);
		if (E.getPosition().x > tutorialPos - E.getGlobalBounds().width - PADDING) E.move(-25, 0);
		if (G.getPosition().x > optionsPos - G.getGlobalBounds().width - PADDING) G.move(-25, 0);
		if (rect1.getPosition().x > versusPos) rect1.move(-25, 0);
		if (rect2.getPosition().x > tutorialPos) rect2.move(-25, 0);
		if (rect3.getPosition().x > optionsPos) rect3.move(-25, 0);
	}

	if (versusSelect) {
		versus.move(25, 0);
		rect1.move(25, 0);
		C.move(25, 0);
		versus.setColor(sf::Color(255, 200, 1));
		if (versus.getPosition().x > WINDOW_WIDTH) {
			loadingText.setFont(font);
			loadingText.setColor(sf::Color(255, 174, 1, 40));
			loadingText.setCharacterSize(200);
			loadingText.setString("Loading...");
			loadingText.setPosition(WINDOW_WIDTH / 2 - loadingText.getLocalBounds().width, WINDOW_HEIGHT / 2);
			game.window.clear(sf::Color(91, 15, 0));
			game.window.draw(loadingText);
			game.window.display();
			unhookEvent();
			FightState fightState(game);
			game.gsm.stopState(*this, &fightState);
		}
	} 
	else if (tutorialSelect) {
		tutorial.move(25, 0);
		rect2.move(25, 0);
		E.move(25, 0);
		tutorial.setColor(sf::Color(255, 200, 1));
		if (tutorial.getPosition().x > WINDOW_WIDTH) {
			loadingText.setFont(font);
			loadingText.setColor(sf::Color(255, 174, 1, 40));
			loadingText.setCharacterSize(200);
			loadingText.setString("Loading...");
			loadingText.setPosition(WINDOW_WIDTH / 2 - loadingText.getLocalBounds().width, WINDOW_HEIGHT / 2);
			game.window.clear(sf::Color(91, 15, 0));
			game.window.draw(loadingText);
			game.window.display();
			unhookEvent();
			FightState fightState(game);
			game.gsm.stopState(*this, &fightState);
		}
	}
}

void MainMenuState::draw() {
	game.window.clear(sf::Color(91, 15, 0));
	game.window.draw(versus);
	game.window.draw(tutorial);
	game.window.draw(options);
	game.window.draw(rect1);
	game.window.draw(rect2);
	game.window.draw(rect3);
	game.window.draw(C);
	game.window.draw(E);
	game.window.draw(G);
	game.window.display();
}

// Everything here is run on its own thread!
void MainMenuState::receiveKeysDown(int note, int playerId) {
	if (playerId == game.playerOne.playerId) {
		if (note % 12 == 0) {
			versusSelect = true;
		}
		else if (note % 12 == 4) {
			tutorialSelect = true;
		}
	}
}

void MainMenuState::unhookEvent() {
	cout << "MainMenuState events unhooked\n";
	__unhook(&InputHandler::sendKeysDown, game.inputHandler.get(), &GameState::receiveKeysDown);
}