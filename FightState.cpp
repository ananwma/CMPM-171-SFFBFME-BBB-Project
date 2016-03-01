#define NOMINMAX
#include "stdafx.h"
#include <iostream>
#include <vector>

#include <bitset>

#include "FightState.h"
#include "PauseState.h"
#include "ResultsState.h"
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
	//for (int i = 0; i < 127; i++) {
	//	inputP1.push_back(false);
	//	inputP2.push_back(false);
	//}

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
	
	// Possibly move this to asset manager in future
	if (!metronomeSoundBuffer.loadFromFile("sounds/metronome_tick.wav")) {
		cerr << "Could not load sound!\n";
		exit(EXIT_FAILURE);
	}
	metronomeSound.setBuffer(metronomeSoundBuffer);

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
	if ((metronome.getElapsedTime().asMilliseconds()) < beatThreshold || (metronome.getElapsedTime().asMilliseconds()) > beat - beatThreshold) {
		onBeat = true;
	}
	if (metronome.getElapsedTime().asMilliseconds() > beat) {
		//cout << "beat" << endl;
		metronome.restart();
		metronomeSound.play();
	}
	//cout << "(" << onBeat << ", " << metronome.getElapsedTime().asMilliseconds() << ")" << endl;
	processInput(game.playerOne, inputP1);
	processInput(game.playerTwo, inputP2);

	checkBoxes(game.playerOne, game.playerTwo);
	checkBoxes(game.playerTwo, game.playerOne);
	checkClipBoxes(game.playerOne, game.playerTwo);
	checkClipBoxes(game.playerTwo, game.playerOne);

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

	if (game.playerOne.health <= 0) {
		game.playerTwo.roundWins++;
		ResultsState results(game);
		game.gsm.stopState(*this, &results);
	}
	else if (game.playerTwo.health <= 0) {
		game.playerOne.roundWins++;
		ResultsState results(game);
		game.gsm.stopState(*this, &results);
	}

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
	drawBoxes(game.playerOne, 0, 0, 1);
	drawBoxes(game.playerTwo, 0, 0, 1);
	game.window.display();
}

void FightState::checkClipBoxes(Player& p1, Player& p2) {
	sf::FloatRect clipbox1 = p1.getCurrentFrame().clipboxes.at(0);
	sf::FloatRect clipbox2 = p2.getCurrentFrame().clipboxes.at(0);
	sf::FloatRect offsetClipBox1(clipbox1.left + p1.xpos, clipbox1.top + p1.ypos, clipbox1.width, clipbox1.height);
	sf::FloatRect offsetClipBox2(clipbox2.left + p2.xpos, clipbox2.top + p2.ypos, clipbox2.width, clipbox2.height);
	if (offsetClipBox1.intersects(offsetClipBox2)) {
		if (p2.state == WALKING) {
			// If velocities ahve opposite signs
			if ((p1.xvel < 0) == (p2.xvel < 0)) {
				p2.xvel = 0;
				p1.xvel = 0;
			}
		}
	}
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
				if (!attacker.getCurrentFrame().hit) {
					cout << "hit!" << endl;
					defender.getHit(attacker.getCurrentMove());
					attacker.getCurrentFrame().hit = true;
				}
				attacker.canCancel = true;
				return;
			}
		}
	}
}

void FightState::drawBoxes(Player& player, bool hit, bool hurt, bool clip) {
	// Anan's super secret math formula
	sf::Vector2f v = player.character->sprite.getPosition();
	Frame &frame = player.getCurrentFrame();
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
	if (clip) {
		for (auto box : frame.clipboxes) {
			sf::RectangleShape drawRect(sf::Vector2f(box.width, box.height));
			sf::Vector2f v = player.character->sprite.getPosition();
			if (player.side == LEFT)
				drawRect.setPosition(v.x + box.left, v.y + box.top);
			else
				drawRect.setPosition(v.x - box.width - box.left + player.getSpriteWidth(), v.y + box.top);
			drawRect.setFillColor(sf::Color(200, 200, 40, 120));
			game.window.draw(drawRect);
		}
	}
}

void FightState::processInput(Player& player, vector<int>& input) {
	// Handle every possible combination of movement keys
	if (player.left && player.jumping && player.right) {
		player.jump(NEUTRAL);
	}
	else if (!player.left && player.jumping && player.right) {
		player.jump(RIGHT);
	}
	else if (player.left && !player.jumping && player.right) {
		player.doMove(IDLE);
	}
	else if (player.left && player.jumping && !player.right) {
		player.jump(LEFT);
	}
	else if (!player.left && !player.jumping && player.right) {
		player.walk(RIGHT);
	}
	else if (player.left && !player.jumping && !player.right) {
		player.walk(LEFT);
	}
	else if (!player.left && player.jumping && !player.right) {
		player.jump(NEUTRAL);
	}
	else if (!player.left && !player.jumping && !player.right) {
		player.doMove(IDLE);
	}
	
	if (!input.empty()) {
		if (!inputOpen) {
			inputClock.restart();
		}
		inputOpen = true;
		if (inputClock.getElapsedTime().asMilliseconds() > 10) {
			inputOpen = false;
			/* This code is kind of hard to read; each note starting at 60 (Middle C) is
			   left shifted its distance away from middle C, ie C is 1, D is 10, E is 100,
			   and so on. These numbers are OR'd together to make something like 10010001,
			   which represents a C Major triad. To handle octaves, the number is right shifted
			   12 times again and again until there are at most eleven trailing 0's in the 
			   binary number. When that happens, we know the octave has been normalized. */
			if (input.size() < 5) {
				DWORD_PTR acc = 0;
				// Don't use an iterator on input vector
				for (int i = 0; i < input.size(); i++) {
					int shift = input.at(i);
					DWORD_PTR note = 1;
					if (shift > 59) {
						shift -= 60;
						note = note << shift;
					}
					acc |= note;
				}
				input.clear();
				while (!(acc & 0xFFF)) acc = acc >> 12;
				bitset<64> bin(acc);
				cout << hex << acc << endl;
				if (onBeat) {
					if (acc == C_NATURAL) {
						player.doMove(JAB);
					}
					else if (acc == D_NATURAL) {
						player.doMove(STRONG);
					}
					else if (acc == F_NATURAL) {
						player.doMove(STRONG);
					}
				}
			}
			else {
				input.clear();
			}
		}
	}
}

// Everything here is run on its own thread!
void FightState::receiveKeysDown(int note, int playerId) {
	if (playerId == game.playerOne.playerId) {
		// Movement keys
		if (note == 48) game.playerOne.left = true;
		else if (note == 52) game.playerOne.jumping = true;
		else if (note == 55) game.playerOne.right = true;
		// Attack keys
		else {
			inputP1.push_back(note);
		}
	}
	else if (playerId == game.playerTwo.playerId) {
		// Movement keys
		if (note == 48) game.playerTwo.left = true;
		else if (note == 52) game.playerTwo.jumping = true;
		else if (note == 55) game.playerTwo.right = true;
		// Attack keys
		else {
			inputP2.push_back(note);
		}
	}
}

void FightState::receiveKeysUp(int note, int playerId) {
	if (playerId == game.playerOne.playerId) {
		// Movement keys
		if (note == 48) game.playerOne.left = false;
		else if (note == 52) game.playerOne.jumping = false;
		else if (note == 55) game.playerOne.right = false;
		// Attack keys
		else {
			//inputP1.at(note) = false;
		}
	}
	else if (playerId == game.playerTwo.playerId) {
		// Movement keys
		if (note == 48) game.playerTwo.left = false;
		else if (note == 52) game.playerTwo.jumping = false;
		else if (note == 55) game.playerTwo.right = false;
		// Attack keys 
		else {
			//inputP2.at(note) = false;
		}
	}
}

void FightState::unhookEvent() {
	cout << "FightState events unhooked\n";
	__unhook(&InputHandler::sendKeysDown, game.inputHandler.get(), &GameState::receiveKeysDown);
	__unhook(&InputHandler::sendKeysUp, game.inputHandler.get(), &GameState::receiveKeysUp);
}

FightState::~FightState() {
	//delete player1;
}