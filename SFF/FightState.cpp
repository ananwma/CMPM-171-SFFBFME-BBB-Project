#include "stdafx.h"
#include <iostream>
#include <vector>

#include "FightState.h"
#include "PauseState.h"

// tmp
#include "Collision.h"
#include "CharacterBach.h"

using namespace std;

// Some globals for testing
FightState::FightState(Game &_game) : game(_game) { }

void FightState::init() {//create Bach and his moves, from frames up
	int player1start_x = 300;
	int player1start_y = 400;
	int player2start_x = 300;
	int player2start_y = 400;
	bool facing_right = true;
	jumping = false;
	falling = false;
	walking = false;
	//p1_facing_right = true;
	spriteWidth = 68;
	spriteHeight = 105;

	collision = new Collision();

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

	Bach* bach2 = new Bach();
	game.playerTwo.setCharacter(bach2);
	game.playerTwo.character->initMoves();
	game.playerTwo.character->currentMove = IDLE;
	game.playerTwo.character->currentMoveFrame = 0;
	//enum bachPossibleMoves { Idle, Walk, Jump, Attack, Hurt };
	//sf::Vector2i source(0, Idle);
	game.playerOne.character->sprite.setPosition(100, 500);
	game.playerTwo.character->sprite.setPosition(800, 500);
	game.playerTwo.character->sprite.scale(-1, 1);
	game.playerTwo.character->sprite.move(spriteWidth, 1);
}

void FightState::update() {
	//cout << "State #1" << endl;
	if (!running) {
		PauseState pauseState(game);
		game.gsm.stopState(*this, &pauseState);
	}

	sf::Event event;
	while (game.window.pollEvent(event))
	{
		switch (event.type) {
		case sf::Event::Closed:
			game.window.close();
			break;
		}
	}
	int window_width = 1280;

	collision->flip_sprites(game.playerOne, game.playerTwo);


	if (jumping) {
		if (game.playerOne.character->sprite.getPosition().y <= 300) {
			jumping = false;
			falling = true;
		}
		else {
			game.playerOne.character->sprite.move(0, -0.500000000f);
		}
	}

	if (falling) {
		if (game.playerOne.character->sprite.getPosition().y >= 500) {
			falling = false;
		}
		else if ((game.playerOne.character->sprite.getPosition().x + (spriteWidth / 2)) >= (game.playerTwo.character->sprite.getPosition().x - (spriteWidth / 2)) && (game.playerOne.character->sprite.getPosition().x + (spriteWidth / 2)) <= (game.playerTwo.character->sprite.getPosition().x + (spriteWidth / 2)) && ((game.playerOne.character->sprite.getPosition().y + spriteWidth / 2) >= (game.playerTwo.character->sprite.getPosition().y - spriteWidth / 2))) {
			float move_left = (game.playerOne.character->sprite.getPosition().x + (spriteWidth / 2)) - (game.playerTwo.character->sprite.getPosition().x - (spriteWidth / 2));
			game.playerOne.character->sprite.move(-move_left, 0.500000000f);
		}
		else if ((game.playerOne.character->sprite.getPosition().x - (spriteWidth / 2)) >= (game.playerTwo.character->sprite.getPosition().x - (spriteWidth / 2)) && (game.playerOne.character->sprite.getPosition().x - (spriteWidth / 2)) <= (game.playerTwo.character->sprite.getPosition().x + (spriteWidth / 2)) && ((game.playerOne.character->sprite.getPosition().y + spriteWidth / 2) >= (game.playerTwo.character->sprite.getPosition().y - spriteWidth / 2))) {
			float move_right = (game.playerTwo.character->sprite.getPosition().x + (spriteWidth / 2)) - (game.playerOne.character->sprite.getPosition().x - (spriteWidth / 2));
			game.playerOne.character->sprite.move(move_right, 0.500000000f);
		}
		else {
			game.playerOne.character->sprite.move(0, 0.500000000f);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		//game.playerOne.walk(FORWARDS);
		collision->move_right(game.playerOne, game.playerTwo, window_width);
	}


	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		//game.playerOne.walk(BACKWARDS);
		collision->move_left(game.playerOne, game.playerTwo);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		game.playerOne.character->currentMove = JUMP;
		if (!jumping && !falling) jumping = true;
		game.playerOne.character->currentMove = 2;
		game.playerOne.character->currentMoveFrame = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
		game.playerOne.character->currentMove = JAB;
		game.playerOne.character->currentMove = 3;
		game.playerOne.character->currentMoveFrame = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		game.playerOne.character->currentMove = HITSTUN;
		game.playerOne.character->currentMove = 4;
		game.playerOne.character->currentMoveFrame = 0;
	}
	else {
		game.playerOne.character->currentMove = IDLE;
	}
	//std::cout << clock.getElapsedTime().asSeconds() << std::endl;
	//find move based on input read, if0 state allows it and is different from currentMove:
	//set player1.currentMove, set player1.currentMoveFrame to 0
	//else player1.currentMoveFrame++
	frameCounter += frameSpeed * clock.restart().asSeconds();
	if (frameCounter >= switchFrame) {
		frameCounter = 0;
		game.playerOne.character->currentMoveFrame++;
		if (game.playerOne.character->currentMoveFrame > (game.playerOne.character->moveList.at(game.playerOne.character->currentMove).frames.size()) - 1) {
			game.playerOne.character->currentMove = 0;
			game.playerOne.character->currentMoveFrame = 0;
		}

	}
	//if player1.currentMoveFrame > player1.currentMove.frames.length:
	//set player1.currentMove to idle 
	//player1Image.setTextureRect(sf::IntRect(player1.currentMoveFrame * spriteWidth, player1.currentMove.spriteRow * spriteHeight, spriteWidth, SpriteHeight));
	game.playerOne.character->sprite.setTextureRect(sf::IntRect(game.playerOne.character->currentMoveFrame * spriteWidth, game.playerOne.character->currentMove * spriteHeight, spriteWidth, spriteHeight));
	game.playerTwo.character->sprite.setTextureRect(sf::IntRect(game.playerTwo.character->currentMoveFrame * spriteWidth, game.playerTwo.character->currentMove * spriteHeight, spriteWidth, spriteHeight));

	frameCounter += frameSpeed * clock.restart().asSeconds();
	if (frameCounter >= switchFrame) {
		frameCounter = 0;
		game.playerOne.updateAnimFrame();
	}
}

void FightState::draw() {
	game.window.clear(sf::Color(0, 200, 100, 255));
	game.window.draw(game.playerOne.character->sprite);
	game.window.draw(game.playerTwo.character->sprite);
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