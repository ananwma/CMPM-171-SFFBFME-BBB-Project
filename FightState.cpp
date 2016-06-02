#define NOMINMAX
#include "stdafx.h"
#include <iostream>
#include <vector>

#include <bitset>

#include "FightState.h"
#include "PauseState.h"
#include "ResultsState.h"
#include "BeatIndicator.h"
// tmp
#include "CharacterBach.h"

using namespace std;

FightState::FightState(Game &_game) : game(_game), bassline(game, { C1, C2, F1, F2, G1, G2 }, KEY_CM, 70) {
}

void FightState::init() {
	cout << game.playerOne.playerId << endl;
	cout << game.playerTwo.playerId << endl;
	running = true;
	 
	game.currentScreen.setStage(chstage);
	game.currentScreen.stage.sprite.move(-200, 0);
	game.currentScreen.stage.window_offset = 0;

	// Threshold for acceptable inputs, smaller is harder, also in milliseconds
	beatThreshold = 100 * (BEAT_SPEED / 500);

	// Number of frames to leave indicator on, as well as a boolean for when it's on
	indicatorFlash = 5;
	indicatorFlashOn = false;

	// Later move this to character selection state
	game.playerOne.loadCharacter("Bach.xml");
	game.playerOne.doMove("idle");

	game.playerTwo.loadCharacter("Bach.xml");
	game.playerTwo.doMove("idle");

	game.playerOne.setPosition(WINDOW_WIDTH / 50, GROUND);
	game.playerTwo.setPosition(WINDOW_WIDTH / 1.2, GROUND);

	game.collisionManager.registerEntity(game.playerOne);
	game.collisionManager.registerEntity(game.playerTwo);

	//game.playerOne.setSide(LEFT);
	//game.playerTwo.setSide(RIGHT);

	player_1_HP.setSize(sf::Vector2f(400, 30));
	player_1_HP.setFillColor(sf::Color(100, 250, 50));
	player_2_HP.setSize(sf::Vector2f(400, 30));
	player_2_HP.setFillColor(sf::Color(100, 250, 50));
	player_2_HP.setPosition(WINDOW_WIDTH - 400, 0);

	player_1_meter.setPosition(0, 35);
	player_1_meter.setSize(sf::Vector2f(400, 30));
	player_1_meter.setFillColor(sf::Color(0, 255, 255));
	player_2_meter.setSize(sf::Vector2f(400, 30));
	player_2_meter.setFillColor(sf::Color(0, 255, 255));
	player_2_meter.setPosition(WINDOW_WIDTH - 400, 35);

	game.playerOne.indicator.bSprite.setPosition(0, 50);
	game.playerTwo.indicator.bSprite.setPosition(WINDOW_WIDTH - 400, 50);

	camera_view.setCenter(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
	camera_view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	HUD.setCenter(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
	HUD.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	game.window.setView(camera_view);

	// Possibly move this to asset manager in future
	if (!metronomeSoundBuffer.loadFromFile("sounds/metronome_tick.wav")) {
		cerr << "Could not load sound!\n";
		exit(EXIT_FAILURE);
	}
	metronomeSound.setBuffer(metronomeSoundBuffer);

	if (!hitSoundBuffer.loadFromFile("sounds/hit.wav")) {
		cerr << "Could not load sound!\n";
		exit(EXIT_FAILURE);
	}
	hitSound.setBuffer(hitSoundBuffer);

	if (!blockSoundBuffer.loadFromFile("sounds/block.wav")) {
		cerr << "Could not load sound!\n";
		exit(EXIT_FAILURE);
	}
	blockSound.setBuffer(blockSoundBuffer);

	hitSound.setVolume(50);

	bassline.setInstrument(32);
	game.inputHandler->setInstrument(6);

	__hook(&InputHandler::sendKeysDown, game.inputHandler.get(), &GameState::receiveKeysDown);
	__hook(&InputHandler::sendKeysUp, game.inputHandler.get(), &GameState::receiveKeysUp);
}

void FightState::update() {

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
	if ((metronome.getElapsedTime().asMilliseconds()) < beatThreshold || (metronome.getElapsedTime().asMilliseconds()) > game.beat - beatThreshold) {
		onBeat = true;
		
	}


	if (metronome.getElapsedTime().asMilliseconds() > game.beat) {
		metronome.restart();
		// Play a note in the bassline on each quarter note
		//flash indicator???
			indicatorFlashOn = true;
			indicatorFlash = 5;
			game.playerOne.indicator.updateIndicator(NONE);
			game.playerTwo.indicator.updateIndicator(NONE);
		if (quarterNote) {
			bassline.playNextNote();
			//metronomeSound.play();
			quarterNote = false;
			
		}
		else {
			quarterNote = true;
		}
	}
	processInput(game.playerOne, inputP1);
	processInput(game.playerTwo, inputP2);
	game.collisionManager.checkBoxes(game.playerOne, game.playerTwo);
	game.collisionManager.checkBoxes(game.playerTwo, game.playerOne);

	//keep here or move to fightstate?
	game.collisionManager.checkClipBoxes(game.playerOne, game.playerTwo);
	game.playerOne.update();
	game.playerTwo.update();
	game.playerOne.updateSide(game.playerTwo);
	game.playerTwo.updateSide(game.playerOne);

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

	if ((game.playerOne.health < game.playerOne.getMaxHealth() / 1.333f || game.playerTwo.health < game.playerTwo.getMaxHealth() / 1.333f) && phase == 0) {
		phase = 1;
		game.beat = 425.0f;
		beatThreshold = 100 * (game.beat / 500);
		frameSpeed = 1000 * (500 / game.beat);
		game.playerOne.setBeat(game.beat);
		game.playerTwo.setBeat(game.beat);
		bassline.setBassline({ C1, C1, D1, D1, G1, G1, C2, C2 });
	}
	else if ((game.playerOne.health < game.playerOne.getMaxHealth() / 2 || game.playerTwo.health < game.playerTwo.getMaxHealth() / 2) && phase == 1) {
		phase = 2;
		game.beat = 350.0f;
		beatThreshold = 100 * (game.beat / 500);
		frameSpeed = 1000 * (500 / game.beat);
		game.playerOne.setBeat(game.beat);
		game.playerTwo.setBeat(game.beat);
		bassline.setBassline({ C1, G1, E1, C2 });
	}
	else if ((game.playerOne.health < game.playerOne.getMaxHealth() / 4 || game.playerTwo.health < game.playerTwo.getMaxHealth() / 4) && phase == 2) {
		phase = 3;
		game.beat = 275.0f;
		beatThreshold = 100 * (game.beat / 500);
		frameSpeed = 1000 * (500 / game.beat);
		game.playerOne.setBeat(game.beat);
		game.playerTwo.setBeat(game.beat);
		bassline.setBassline({ C1, F1, E1, F1, G1, A1, C2, B1, A1, B1 });
	}
	

	//possibly move into entity updateanimframe
	frameCounter += frameSpeed * clock.restart().asSeconds();
	if (frameCounter >= switchFrame) {
		frameCounter = 0;
		if (indicatorFlashOn) {
		indicatorFlash -= 1;
		}
		if (indicatorFlash == 0) {
			game.playerOne.indicator.updateIndicator(NOBEAT);
			game.playerTwo.indicator.updateIndicator(NOBEAT);
			indicatorFlashOn = false;    
			indicatorFlash = 5;
		}
		game.playerOne.hitstunFrames--;
		game.playerOne.blockstunFrames--;
		game.playerTwo.hitstunFrames--;
		game.playerTwo.blockstunFrames--;
		game.playerTwo.updateAnimFrame();
		game.playerOne.updateAnimFrame();
	}


	sf::Vector2<float> p1HP(400.0*(game.playerOne.health / 1000.0), 30);
	sf::Vector2<float> p2HP(400.0*(game.playerTwo.health / 1000.0), 30);
	sf::Vector2<float> p1M(400.0*(game.playerOne.meter / 1000.0), 30);
	sf::Vector2<float> p2M(400.0*(game.playerOne.meter / 1000.0), 30);

	player_1_HP.setSize(p1HP);
	player_2_HP.setSize(p2HP);
	player_1_meter.setSize(p1M);
	player_2_meter.setSize(p2M);


}

void FightState::draw() {
	game.window.clear();
	game.window.setView(camera_view);
	game.window.draw(game.currentScreen.stage.sprite);
	game.window.draw(game.playerOne.sprite);
	game.window.draw(game.playerTwo.sprite);
	drawBoxes(game.playerOne, 1, 1, 1);
	drawBoxes(game.playerTwo, 1, 1, 1);
	game.window.setView(HUD);
	game.window.draw(player_1_HP);
	game.window.draw(player_2_HP);
	game.window.draw(player_1_meter);
	game.window.draw(player_2_meter);
	game.window.draw(game.playerOne.indicator.bSprite);
	game.window.draw(game.playerTwo.indicator.bSprite);
	game.window.display();
}


void FightState::drawBoxes(Player& player, bool hit, bool hurt, bool clip) {
	Frame &frame = player.getCurrentFrame();
	if (hit) {
		for (auto box : frame.hitboxes) {
			sf::RectangleShape drawRect(sf::Vector2f(box.width, box.height));
			sf::Vector2f v = player.getPosition();
			if (player.getSide() == LEFT)
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
			sf::Vector2f v = player.getPosition();
			if (player.getSide() == LEFT)
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
			sf::Vector2f v = player.getPosition();
			if (player.getSide() == LEFT)
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
		player.holdingBlock = false;
		player.doMove("njump");
	}
	else if (!player.left && player.jumping && player.right) {
		player.holdingBlock = false;
		player.doMove("fjump");
	}
	else if (player.left && !player.jumping && player.right) {
		player.holdingBlock = true;
		player.doMove("idle");
	}
	else if (player.left && player.jumping && !player.right) {
		player.holdingBlock = false;
		player.doMove("bjump");
	}
	else if (!player.left && !player.jumping && player.right) {

		player.doMove("walk");
		//check if player is holding correct direction to block
		if (player.getSide() == RIGHT) {
			player.holdingBlock = true;
		}
		else {
			player.holdingBlock = false;
		}
	}
	else if (player.left && !player.jumping && !player.right) {
		player.doMove("backwalk");
		//check if player is holding correct direction to block
		if (player.getSide() == LEFT) {
			player.holdingBlock = true;
		}
		else {
			player.holdingBlock = false;
		}
	}
	else if (!player.left && player.jumping && !player.right) {
		player.holdingBlock = false;
		player.doMove("njump");
	}
	else if (!player.left && !player.jumping && !player.right) {
		player.holdingBlock = false;
		player.doMove("idle");
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
				indicatorFlashOn = true;

				player.indicator.updateIndicator(ONBEAT);


				if (acc == C_NATURAL) {
					player.doMove("jab");
				}
				else if (acc == D_NATURAL) {
					player.doMove("strong");
				}
				else if (acc == E_NATURAL) {
					player.doMove("fierce");
				}
				else if (acc == F_NATURAL) {
					player.doMove("short");
				}
				else if (acc == G_NATURAL) {
					player.doMove("forward");
				}
				else if (acc == A_NATURAL) {
					player.doMove("roundhouse");
				}
				else if (acc == C_MAJOR) {
					player.doMove("shoryuken");
				}
				else if (acc == F_MAJOR_64) {
					player.doMove("shoryuken");
				}
				else if (acc == G_MAJOR) {
					player.doMove("tatsu");
				}
				//cheats
				else if (acc == 0x540) {
					player.health = 1000;
				}
				else {
					player.hitstunFrames = 3;
					player.doMove("hitstun");
					player.health -= 50;
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
		else if (note > 59) {
			if (onBeat || game.playerOne.isInSuper()) {
				inputP1.push_back(note);
				game.inputHandler->playNote(note, 80);
				game.playerOne.checkSuper(note % 12);
			}
		}
		else if (note == 39) {
			game.playerTwo.ezmode = 5;
		}
	}
	else if (playerId == game.playerTwo.playerId) {
		// Movement keys
		if (note == 48) game.playerTwo.left = true;
		else if (note == 52) game.playerTwo.jumping = true;
		else if (note == 55) game.playerTwo.right = true;
		// Attack keys
		else if (note > 59) {
			if (onBeat || game.playerTwo.isInSuper()) {
				inputP2.push_back(note);
				game.inputHandler->playNote(note, 80);
				game.playerTwo.checkSuper(note % 12);
			}
		}
		else if (note == 39) {
			game.playerOne.ezmode = 5;
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
		else if (note > 59) {
			game.inputHandler->playNote(note, 0);
		}
	}
	else if (playerId == game.playerTwo.playerId) {
		// Movement keys
		if (note == 48) game.playerTwo.left = false;
		else if (note == 52) game.playerTwo.jumping = false;
		else if (note == 55) game.playerTwo.right = false;
		// Attack keys 
		else if (note > 59) {
			game.inputHandler->playNote(note, 0);
		}
	}
}

void FightState::unhookEvent() {
	cout << "FightState events unhooked\n";
	__unhook(&InputHandler::sendKeysDown, game.inputHandler.get(), &GameState::receiveKeysDown);
	__unhook(&InputHandler::sendKeysUp, game.inputHandler.get(), &GameState::receiveKeysUp);
}

FightState::~FightState() {
}