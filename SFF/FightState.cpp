#include "stdafx.h"
#include <iostream>
#include <vector>

#include "FightState.h"
#include "PauseState.h"

// tmp
#include "CharacterBach.h"

using namespace std;

// Some globals for testing
sf::CircleShape shape(100.f);
FightState::FightState(Game &_game) : game(_game) { }

void FightState::init() {
	cout << game.playerOne.playerId << endl;
	cout << game.playerTwo.playerId << endl;
	running = true;
	__hook(&InputHandler::sendKeysDown, game.inputHandler.get(), &GameState::recieveKeysDown);

	// Later move this to character selection state
	Bach* bach = new Bach();
	game.playerOne.setCharacter(bach);
	game.playerOne.character->initMoves();
	game.playerOne.character->currentMove = IDLE;
	game.playerOne.character->currentMoveFrame = 0;
}

void FightState::update() {
	//cout << "State #1" << endl;
	if (!running) {
		PauseState pauseState(game);
		game.gsm.stopState(*this, &pauseState);
	}

	sf::Event event;
	if (game.window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			game.window.close();
			break;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		game.playerOne.walk(FORWARDS);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		game.playerOne.walk(BACKWARDS);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		game.playerOne.character->currentMove = JUMP;
		game.playerOne.character->currentMoveFrame = 0;
		game.playerOne.pImage.move(0.0f, 0.100000000f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
		game.playerOne.character->currentMove = JAB;
		game.playerOne.character->currentMoveFrame = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		game.playerOne.character->currentMove = HITSTUN;
		game.playerOne.character->currentMoveFrame = 0;
	}
	else {
		game.playerOne.character->currentMove = IDLE;
	}

	frameCounter += frameSpeed * clock.restart().asSeconds();
	if (frameCounter >= switchFrame) {
		frameCounter = 0;
		game.playerOne.updateAnimFrame();
	}
}

void FightState::draw() {
	game.window.clear(sf::Color(0, 200, 100, 255));
	game.window.draw(game.playerOne.character->sprite);
	drawBoxes(game.playerOne, 1, 1);
	game.window.display();
}

void FightState::drawBoxes(Player player, bool hit, bool hurt) {
	Move currentMove = player.getCurrentMove();
	Frame frame = player.getCurrentFrame();
	if (hit) {
		for (auto box : frame.hitboxes) {
			sf::RectangleShape drawRect(sf::Vector2f(box.width, box.height));
			drawRect.setPosition(player.xpos + box.left, player.ypos + box.top);
			drawRect.setFillColor(sf::Color(200, 40, 40));
			game.window.draw(drawRect);
		}
	}
	if (hurt) {
		for (auto box : frame.hurtboxes) {
			sf::RectangleShape drawRect(sf::Vector2f(box.width, box.height));
			drawRect.setPosition(player.xpos + box.left, player.ypos + box.top);
			drawRect.setFillColor(sf::Color(40, 200, 40));
			game.window.draw(drawRect);
		}
	}
}

// Everything here is run on its own thread!
void FightState::recieveKeysDown(list<int> &notes, int playerId) {
	cout << " recieve1 " << endl;
	running = false;
}

void FightState::unhookEvent() {
	__unhook(&InputHandler::sendKeysDown, game.inputHandler.get(), &GameState::recieveKeysDown);
}

FightState::~FightState() {
	//delete player1;
}