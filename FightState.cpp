#define NOMINMAX
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>

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
	__hook(&InputHandler::sendKeysDown, game.inputHandler.get(), &GameState::receiveKeysDown);
	__hook(&InputHandler::sendKeysUp, game.inputHandler.get(), &GameState::receiveKeysUp);

	// Initialize input vectors, 127 possible midi notes
	for (int i = 0; i < 127; i++) {
		inputP1.push_back(false);
		inputP2.push_back(false);
	}

	game.currentScreen.setStage(chstage);
	game.currentScreen.stage.sprite.move(-200, 0);
	game.currentScreen.stage.window_offset = 200;

	// Beat is in milliseconds, 1000 = 1 beat every 1 second
	beat = 1000;
	// Threshold for acceptable inputs, smaller is harder, also in milliseconds
	beatThreshold = 200;


	// Later move this to character selection state
	Bach* bach = new Bach();
	Bach* bach2 = new Bach();
	game.playerOne.setCharacter(bach);
	game.playerOne.character->initMoves();
	game.playerOne.doMove(IDLE);
	game.playerOne.character->currentMoveFrame = 0;
	game.playerOne.setPosition(20, 100);
	game.playerTwo.setCharacter(bach2);
	game.playerTwo.character->initMoves();
	game.playerTwo.doMove(IDLE);
	game.playerTwo.character->currentMoveFrame = 0;	
	game.playerTwo.setPosition(400, 100);
	game.playerTwo.side = RIGHT;
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

	onBeat = false;
	if ((metronome.getElapsedTime().asMilliseconds() % beat) < beatThreshold || (metronome.getElapsedTime().asMilliseconds() % beat) > beat - beatThreshold) {
		onBeat = true;
	}

	processInput(game.playerOne, inputP1);
	processInput(game.playerTwo, inputP2);

	checkBoxes(game.playerOne, game.playerTwo);
	checkBoxes(game.playerTwo, game.playerOne);

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		game.playerOne.walk(LEFT);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		game.playerOne.walk(RIGHT);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		game.playerOne.doMove(JUMP);
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
	}*/

	game.playerOne.updatePhysics();
	game.playerTwo.updatePhysics();
	//checkMoveBoxes(game.playerOne, game.playerTwo);

	// Camera stuff is kinda rough right now, didn't have time to fully merge Anan's code
	if (game.playerOne.xpos <= 0) {
		game.currentScreen.move_camera_left(game.currentScreen.stage, game.playerTwo, game.playerOne);
		if (game.playerOne.xpos < -200) 
			game.playerOne.setPosition(-200, game.playerOne.ypos);
	}
	if (game.playerOne.xpos + game.playerOne.getSpriteWidth() >= 1280) {
		game.currentScreen.move_camera_right(game.currentScreen.stage, game.playerTwo, game.playerOne);
		if (game.playerOne.xpos > 1480)
			game.playerOne.setPosition(1480, game.playerOne.ypos);
	}

	collision.flip_sprites(game.playerOne, game.playerTwo);
	collision.flip_sprites(game.playerTwo, game.playerOne);

	frameCounter += frameSpeed * clock.restart().asSeconds();
	if (frameCounter >= switchFrame) {
		frameCounter = 0;
		game.playerTwo.updateAnimFrame();
		game.playerOne.updateAnimFrame();
	}
}

void FightState::draw() {
	game.window.draw(game.currentScreen.stage.sprite);
	game.window.draw(game.playerOne.character->sprite);
	game.window.draw(game.playerTwo.character->sprite);
	drawBoxes(game.playerOne, 1, 1);
	drawBoxes(game.playerTwo, 1, 1);
	game.window.display();
}

void FightState::checkMoveBoxes(Player& p1, Player& p2) {
	sf::FloatRect movebox1 = p1.getCurrentFrame().hurtboxes.at(0);
	sf::FloatRect movebox2 = p2.getCurrentFrame().hurtboxes.at(0);
	sf::FloatRect offsetMoveBox1(movebox1.left + p1.xpos, movebox1.top + p1.ypos, movebox1.width, movebox1.height);
	sf::FloatRect offsetMoveBox2(movebox2.left + p2.xpos, movebox2.top + p2.ypos, movebox2.width, movebox2.height);
	//if (offsetMoveBox1.intersects(offsetMoveBox2)) {
		//p2.xvel = p1.xvel;
		//p2.colliding = true;
		//p1.colliding = true;
	//}
	//else
		//p2.colliding = false;
}

void FightState::checkBoxes(Player& attacker, Player& defender) {
	sf::Vector2f attPos = attacker.character->sprite.getPosition();
	sf::Vector2f defPos = defender.character->sprite.getPosition();
	for (auto hitbox : attacker.getCurrentFrame().hitboxes) {
		for (auto hurtbox : defender.getCurrentFrame().hurtboxes) {
			// Make new rects offset by players' current positions and orientations
			sf::FloatRect offsetHit;
			if (attacker.side == LEFT) {
				sf::FloatRect tmp(hitbox.left + attPos.x, hitbox.top + attPos.y, hitbox.width, hitbox.height);
				offsetHit = tmp;
			}
			else if (attacker.side == RIGHT) {
				sf::FloatRect tmp(attPos.x - hitbox.width - hitbox.left + attacker.getSpriteWidth(), hitbox.top + attPos.y, hitbox.width, hitbox.height);
				offsetHit = tmp;
			}

			sf::FloatRect offsetHurt;
			if (defender.side == LEFT) {
				sf::FloatRect tmp(hurtbox.left + defPos.x, hurtbox.top + defPos.y, hurtbox.width, hurtbox.height);
				offsetHurt = tmp;
			}
			else if (defender.side == RIGHT) {
				sf::FloatRect tmp(defPos.x - hurtbox.width - hurtbox.left + defender.getSpriteWidth(), hurtbox.top + defPos.y, hurtbox.width, hurtbox.height);
				offsetHurt = tmp;
			}
			if (offsetHit.intersects(offsetHurt)) {
				cout << "hit!" << endl;
				defender.doMove(HITSTUN);
				return;
			}
		}
	}
}

void FightState::drawBoxes(Player& player, bool hit, bool hurt) {
	// Anan's super secret math formula
	sf::Vector2f v = player.character->sprite.getPosition();
	Frame frame = player.getCurrentFrame();
	if (hit) {
		for (auto box : frame.hitboxes) {
			sf::RectangleShape drawRect(sf::Vector2f(box.width, box.height));
			sf::Vector2f v = player.character->sprite.getPosition();
			if (player.side == LEFT)
				drawRect.setPosition(v.x + box.left, v.y + box.top);
			else
				drawRect.setPosition(v.x - box.width - box.left + player.getSpriteWidth(), v.y + box.top);
			drawRect.setFillColor(sf::Color(200, 40, 40, 120));
			game.window.draw(drawRect);
		}		
	}
	if (hurt) {
		for (auto box : frame.hurtboxes) {
			sf::RectangleShape drawRect(sf::Vector2f(box.width, box.height));
			sf::Vector2f v = player.character->sprite.getPosition();
			if (player.side == LEFT)
				drawRect.setPosition(v.x + box.left, v.y + box.top);
			else
				drawRect.setPosition(v.x - box.width - box.left + player.getSpriteWidth(), v.y + box.top);
			drawRect.setFillColor(sf::Color(40, 200, 40, 120));
			game.window.draw(drawRect);
		}
	}
}

void FightState::processInput(Player& player, vector<bool>& input) {
	if (input.at(48)) 
		player.walk(RIGHT);
	if (input.at(55))
		player.walk(LEFT);

	if (input.at(52) && input.at(48)) {
		player.jump(RIGHT);
		input.at(52) = false;
	}
	else if (input.at(52) && !input.at(48) && !input.at(55)) {
		player.jump(NEUTRAL);
		input.at(52) = false;
	}
	else if (input.at(55) && input.at(52)) {
		player.jump(LEFT);
		input.at(52) = false;
	}

	if (input.at(60) && onBeat) {
		player.doMove(JAB);
		
	}
	if (input.at(62)) {
		player.doMove(STRONG);
		input.at(62) = false;
	}
	cout << onBeat;
	input.at(60) = false;
}

// Everything here is run on its own thread!
// Might need to look into a more efficient way of processing input
void FightState::receiveKeysDown(int note, int playerId) {
	if (playerId == game.playerOne.playerId)
		inputP1.at(note) = true;
	else if (playerId == game.playerTwo.playerId)
		inputP2.at(note) = true;
}

void FightState::receiveKeysUp(int note, int playerId) {
	if (playerId == game.playerOne.playerId)
		inputP1.at(note) = false;
	else if (playerId == game.playerTwo.playerId)
		inputP2.at(note) = false;
}


void FightState::unhookEvent() {
	cout << "FightState events unhooked\n";
	__unhook(&InputHandler::sendKeysDown, game.inputHandler.get(), &GameState::receiveKeysDown);
	__unhook(&InputHandler::sendKeysUp, game.inputHandler.get(), &GameState::receiveKeysUp);
}

FightState::~FightState() {
	//delete player1;
}