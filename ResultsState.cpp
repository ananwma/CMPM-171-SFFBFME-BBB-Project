#include "stdafx.h"
#include <iostream>

#include "ResultsState.h"


using namespace std;

ResultsState::ResultsState(Game &_game) : game(_game) { }

void ResultsState::init() {
	running = true;

	if (!font.loadFromFile("fonts/Altgotisch.ttf")) {
		cerr << "Font not found!\n";
		exit(EXIT_FAILURE);
	}
	text.setFont(font);
	if (game.playerOne.roundWins > game.playerTwo.roundWins)
		text.setString("Player One Wins!");	
	else if (game.playerOne.roundWins < game.playerTwo.roundWins)
		text.setString("Player Two Wins!");
	else {
		text.setString("Draw!");
	}
	text.setCharacterSize(200);
	text.setColor(sf::Color(200, 40, 40));
	text.setStyle(sf::Text::Bold);
	text.setPosition(100, 100);

}

void ResultsState::hookEvent() {
	__hook(&InputHandler::sendKeysDown, game.inputHandler.get(), &ResultsState::receiveKeysDown);
}

void ResultsState::update() {

}

void ResultsState::draw() {
	game.window.draw(text);
	game.window.display();
}

// Everything here is run on its own thread!
void ResultsState::receiveKeysDown(int note, int playerId) {
	if (note == 60)
		game.gsm.stopState(*this);
}

void ResultsState::unhookEvent() {
	cout << "Result events unhooked\n";
	__unhook(&InputHandler::sendKeysDown, game.inputHandler.get(), &ResultsState::receiveKeysDown);
}