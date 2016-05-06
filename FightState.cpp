#define NOMINMAX
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <bitset>

#include "FightState.h"
#include "PauseState.h"
#include "ResultsState.h"
#include "BeatIndicator.h"
#include "UI.h"
// tmp
#include "CharacterBach.h"

using namespace std;

FightState::FightState(Game &_game) : game(_game), bassline(game, { C1, C2, F1, F2, G1, G2 }, KEY_CM, 70) {
}

void FightState::init() {

	running = true;

	game.currentScreen.setStage(chstage);
	game.currentScreen.stage.sprite.move(-game.currentScreen.stage.window_offset, 0);
	game.currentScreen.stage.window_offset = 0;

	// Threshold for acceptable inputs, smaller is harder, also in milliseconds
	beatThreshold = 100 * (BEAT_SPEED / 500);

	// Number of frames to leave indicator on, as well as a boolean for when it's on
	indicatorFlash = 5;
	indicatorFlashOn = false;

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
	//100 = ground level
	game.playerOne.setPosition(WINDOW_WIDTH / 50, GROUND);
	game.playerTwo.setPosition(WINDOW_WIDTH / 1.4, GROUND);
	game.playerTwo.side = RIGHT;

	player_1_HP.setSize(sf::Vector2f(400, 30));
	player_1_HP.setFillColor(sf::Color(100, 250, 50));

	player_1_HP_box.setSize(sf::Vector2f(400, 30));
	player_1_HP_box.setOutlineThickness(5);
	player_1_HP_box.setOutlineColor(sf::Color(250, 250, 250));
	player_1_HP_box.setFillColor(sf::Color::Transparent);

	player_2_HP.setSize(sf::Vector2f(400, 30));
	player_2_HP.setFillColor(sf::Color(100, 250, 50));
	player_2_HP.setPosition(WINDOW_WIDTH - 400, 0);

	player_2_HP_box.setSize(sf::Vector2f(400, 30));
	player_2_HP_box.setPosition(WINDOW_WIDTH - 400, 0);
	player_2_HP_box.setOutlineThickness(5);
	player_2_HP_box.setOutlineColor(sf::Color(250,250,250));
	player_2_HP_box.setFillColor(sf::Color::Transparent);

	timer.setSize(sf::Vector2f(175,75));
	timer.setFillColor(sf::Color(250,250,250));
	timer.setPosition(WINDOW_WIDTH/2-100, 0);

	game.playerOne.roundWins = 0;
	game.playerTwo.roundWins = 0;
	game.playerOne.health = 1000;
	game.playerTwo.health = 1000;
	game.playerOne.meter = 0;
	game.playerTwo.meter = 0;

	player_1_round_win_1.setSize(sf::Vector2f(30, 30));
	player_1_round_win_1.setPosition(WINDOW_WIDTH / 2 - 160, 70);
	player_1_round_win_1.setFillColor(sf::Color(255,255,0));

	player_1_round_win_2.setSize(sf::Vector2f(30, 30));
	player_1_round_win_2.setPosition(WINDOW_WIDTH / 2 - 200, 70);
	player_1_round_win_2.setFillColor(sf::Color(255, 255, 0));

	player_2_round_win_1.setSize(sf::Vector2f(30, 30));
	player_2_round_win_1.setPosition(WINDOW_WIDTH / 2 + 100, 70);
	player_2_round_win_1.setFillColor(sf::Color(255, 255, 0));

	player_2_round_win_2.setSize(sf::Vector2f(30, 30));
	player_2_round_win_2.setPosition(WINDOW_WIDTH / 2 + 140, 70);
	player_2_round_win_2.setFillColor(sf::Color(255, 255, 0));

	if (!font.loadFromFile("fonts/Altgotisch.ttf")) {
		cerr << "Font not found!\n";
		exit(EXIT_FAILURE);
	}
	timer_text.setFont(font);
	timer_text.setColor(sf::Color(0, 0, 0));
	time = 60.0f;
	char temp[256];
	sprintf(temp, "%f", time);
	timer_text.setString(temp);
	timer_text.setCharacterSize(50);
	timer_text.setPosition(WINDOW_WIDTH / 2 - 30, 0);


	player_1_meter.setPosition(0, 35);
	player_1_meter.setSize(sf::Vector2f(400, 30));
	player_1_meter.setFillColor(sf::Color(0, 255, 255));

	player_1_meter_box.setOutlineThickness(5);
	player_1_meter_box.setOutlineColor(sf::Color(250, 250, 250));
	player_1_meter_box.setPosition(0, 35);
	player_1_meter_box.setSize(sf::Vector2f(400, 30));
	player_1_meter_box.setFillColor(sf::Color::Transparent);

	player_2_meter.setSize(sf::Vector2f(400, 30));
	player_2_meter.setFillColor(sf::Color(0, 255, 255));
	player_2_meter.setPosition(WINDOW_WIDTH - 400, 35);

	player_2_meter_box.setOutlineThickness(5);
	player_2_meter_box.setOutlineColor(sf::Color(250, 250, 250));
	player_2_meter_box.setSize(sf::Vector2f(400, 30));
	player_2_meter_box.setPosition(WINDOW_WIDTH - 400, 35);
	player_2_meter_box.setFillColor(sf::Color::Transparent);

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
	game.inputHandler->setInstrument(0);

	__hook(&InputHandler::sendKeysDown, game.inputHandler.get(), &GameState::receiveKeysDown);
	__hook(&InputHandler::sendKeysUp, game.inputHandler.get(), &GameState::receiveKeysUp);
	clock.restart();
}

void FightState::reset() {
	game.playerOne.character->initMoves();
	game.playerOne.doMove(IDLE);
	game.playerOne.character->currentMoveFrame = 0;
	game.playerOne.setPosition(20, 100);
	game.playerTwo.character->initMoves();
	game.playerTwo.doMove(IDLE);
	game.playerTwo.character->currentMoveFrame = 0;
	//100 = ground level
	game.playerOne.setPosition(WINDOW_WIDTH / 50, GROUND);
	game.playerTwo.setPosition(WINDOW_WIDTH / 1.2, GROUND);
	game.playerTwo.side = RIGHT;

	time = 60.0f;
	char temp[256];
	sprintf(temp, "%f", time);
	timer_text.setString(temp);
	clock.restart();

	game.playerOne.health = 1000;
	game.playerOne.meter = 0;
	game.playerTwo.health = 1000;
	game.playerTwo.meter = 0;
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
	if ((metronome.getElapsedTime().asMilliseconds()) < beatThreshold || (metronome.getElapsedTime().asMilliseconds()) > game.beat - beatThreshold) {
		onBeat = true;
		
	}


	if (metronome.getElapsedTime().asMilliseconds() > game.beat) {
		//cout << "game.beat" << endl;
		metronome.restart();
		// Play a note in the bassline on each quarter note
		
		if (quarterNote) {
			bassline.playNextNote();
			//metronomeSound.play();
			//flash indicator???
			indicatorFlashOn = true;
			//cout << "indicatorflashon" << endl;
			indicatorFlash = 5;
			game.playerOne.indicator.updateIndicator(NONE);
			game.playerTwo.indicator.updateIndicator(NONE);
			quarterNote = false;
			
		}
		else {
			quarterNote = true;
		}
	}
	//cout << "(" << onBeat << ", " << metronome.getElapsedTime().asMilliseconds() << ")" << endl;
	processInput(game.playerOne, inputP1);
	processInput(game.playerTwo, inputP2);
	//cout << "P1 vel: " << game.playerOne.xvel << endl << "P2 vel: " << game.playerTwo.xvel << endl << endl;
	checkBoxes(game.playerOne, game.playerTwo);
	checkBoxes(game.playerTwo, game.playerOne);
	checkClipBoxes(game.playerOne, game.playerTwo);
	restrict_movement(game.playerOne, game.playerTwo);
	restrict_movement(game.playerTwo, game.playerOne);
	game.playerOne.updatePhysics();
	game.playerTwo.updatePhysics();
	//checkMoveBoxes(game.playerOne, game.playerTwo);

	// Camera stuff is kinda rough right now, didn't have time to fully merge Anan's code

	//***********************
	//** TEMP CAMERA STUFF **
	//***********************

	//if (game.playerOne.xpos <= -game.playerOne.character->wall_offset) {
		//game.currentScreen.move_camera_left(game.currentScreen.stage, game.playerTwo, game.playerOne);
		//camera_view.move(-1, 0);
	//}
	/*
	if (game.playerOne.xpos + game.playerOne.getSpriteWidth() >= 1280) {
		game.currentScreen.move_camera_right(game.currentScreen.stage, game.playerTwo, game.playerOne);
		if (game.playerOne.xpos > 1480)
			game.playerOne.setPosition(1480, game.playerOne.ypos);
	}*/

		collision.flip_sprites(game.playerOne, game.playerTwo);
		collision.flip_sprites(game.playerTwo, game.playerOne);

		time -= clock.getElapsedTime().asSeconds();
		if (time < 0) time = 0.0;
		char temp[256];
		sprintf(temp, "%d", (int)time);
		timer_text.setString(temp);

	if (game.playerOne.health <= 0) {
		game.playerTwo.roundWins++;
		if (game.playerTwo.roundWins == 2) {
			game.window.draw(player_2_round_win_2);
			ResultsState results(game);
			game.gsm.stopState(*this, &results);
		}
		else {
			reset();
		}
	}
	else if (game.playerTwo.health <= 0) {
		game.playerOne.roundWins++;
		if (game.playerOne.roundWins == 2) {
			game.window.draw(player_1_round_win_2);
			ResultsState results(game);
			game.gsm.stopState(*this, &results);
		}
		else {
			reset();
		}
	}
	else if (time <= 0) {
		cout << "entered loop" << endl;
		if (game.playerOne.health < game.playerTwo.health) {
			cout << "sit1" << endl;
			game.playerTwo.roundWins++;
		}
		else if (game.playerTwo.health < game.playerOne.health) {
			cout << "sit2" << endl;
			game.playerOne.roundWins++;
		}
		else {
			cout << "sit3" << endl;
			game.playerOne.roundWins++;
			game.playerTwo.roundWins++;
		}
		if (game.playerOne.roundWins == 2 || game.playerTwo.roundWins == 2) {
			if (game.playerOne.roundWins == 2) {
				game.window.draw(player_1_round_win_2);
			}
			if (game.playerTwo.roundWins == 2) {
				game.window.draw(player_2_round_win_2);
			}
			ResultsState results(game);
			game.gsm.stopState(*this, &results);
		}
		else {
			reset();
		}
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
		game.playerTwo.updateAnimFrame();
		game.playerOne.updateAnimFrame();
	}

	move_camera(game.playerOne, game.playerTwo);
	move_camera(game.playerTwo, game.playerOne);

	//cout << "offset" << endl;
	//cout << game.currentScreen.stage.window_offset << endl;

	sf::Vector2<float> p1HP(400.0*(game.playerOne.health / 1000.0), 30);
	sf::Vector2<float> p2HP(400.0*(game.playerTwo.health / 1000.0), 30);
	sf::Vector2<float> p1M(400.0*(game.playerOne.meter / 1000.0), 30);
	sf::Vector2<float> p2M(400.0*(game.playerTwo.meter / 1000.0), 30);
	//cout << game.playerOne.meter << endl;
	//cout << p2HP.x << endl;
	player_1_HP.setSize(p1HP);
	player_2_HP.setSize(p2HP);
	player_1_meter.setSize(p1M);
	player_2_meter.setSize(p2M);

	cout << dec<<game.currentScreen.stage.window_offset << endl;
	//cout << dec << game.playerTwo.xpos << endl;
	//cout << game.playerOne.roundWins << endl;
}

void FightState::draw() {
	game.window.clear();
	game.window.setView(camera_view);
	game.window.draw(game.currentScreen.stage.sprite);
	game.window.draw(game.playerOne.character->sprite);
	game.window.draw(game.playerTwo.character->sprite);
	drawBoxes(game.playerOne, 0, 0, 0);
	drawBoxes(game.playerTwo, 0, 0, 0);
	game.window.setView(HUD);
	game.window.draw(player_1_HP);
	game.window.draw(player_2_HP);
	game.window.draw(player_1_meter);
	game.window.draw(player_2_meter);
	game.window.draw(player_1_HP_box);
	game.window.draw(player_2_HP_box);
	game.window.draw(player_1_meter_box);
	game.window.draw(player_2_meter_box);
	game.window.draw(timer);
	game.window.draw(timer_text);
	game.window.draw(game.playerOne.indicator.bSprite);
	game.window.draw(game.playerTwo.indicator.bSprite);
	if (game.playerOne.roundWins > 0) {
		game.window.draw(player_1_round_win_1);
	}
	if (game.playerOne.roundWins > 1) {
		game.window.draw(player_1_round_win_2);
	}
	if (game.playerTwo.roundWins > 0) {
		game.window.draw(player_2_round_win_1);
	}
	if (game.playerTwo.roundWins > 1) {
		game.window.draw(player_2_round_win_2);
	}
	/*
	game.window.draw(player_1_round_win_1);
	game.window.draw(player_1_round_win_2);
	game.window.draw(player_2_round_win_1);
	game.window.draw(player_2_round_win_2);*/


	game.window.display();
}

void FightState::move_camera(Player& cp, Player& op){
	//right

	if ((!(op.xpos + op.character->wall_offset <= game.currentScreen.stage.window_offset))&&(cp.xpos + cp.getSpriteWidth() - cp.character->wall_offset >= WINDOW_WIDTH + game.currentScreen.stage.window_offset) && (game.currentScreen.stage.window_offset < game.currentScreen.stage.window_limit)) {
		camera_view.move(cp.character->walkspeed, 0);
		game.currentScreen.stage.window_offset += cp.character->walkspeed;
	}

	//left

	if ((!(op.xpos + op.getSpriteWidth() - op.character->wall_offset >= WINDOW_WIDTH + game.currentScreen.stage.window_offset))&&(cp.xpos + cp.character->wall_offset <= game.currentScreen.stage.window_offset) && (game.currentScreen.stage.window_offset > -game.currentScreen.stage.window_limit)) {
		camera_view.move(-cp.character->walkspeed, 0);
		game.currentScreen.stage.window_offset -= cp.character->walkspeed;
	}

}

void FightState::restrict_movement(Player& p1, Player& p2) {
	//right

	if ((p2.xpos + p2.character->wall_offset <= game.currentScreen.stage.window_offset) && (p1.xpos + p1.getSpriteWidth() - p1.character->wall_offset >= WINDOW_WIDTH + game.currentScreen.stage.window_offset) &&(p1.xvel>0)){
		p1.xvel = 0;
	}

	//left

	if ((p1.xpos + p1.character->wall_offset <= game.currentScreen.stage.window_offset) && (p2.xpos + p2.getSpriteWidth() - p2.character->wall_offset >= WINDOW_WIDTH + game.currentScreen.stage.window_offset) && (p1.xvel<0)){
		p1.xvel = 0;
	}
}


//Change some copies to moves in future
void FightState::checkClipBoxes(Player& p1, Player& p2) {
	if (!p1.getCurrentFrame().clipboxes.empty() && !p2.getCurrentFrame().clipboxes.empty()) {
		sf::FloatRect clipbox1 = p1.getCurrentFrame().clipboxes.at(0);
		sf::FloatRect clipbox2 = p2.getCurrentFrame().clipboxes.at(0);
		sf::FloatRect offsetClipBox1;
		sf::FloatRect offsetClipBox2;
		if (p1.side == LEFT)
			offsetClipBox1 = sf::FloatRect(clipbox1.left + p1.xpos, clipbox1.top + p1.ypos, clipbox1.width, clipbox1.height);
		else if (p1.side == RIGHT)
			offsetClipBox1 = sf::FloatRect(p1.xpos - clipbox1.width - clipbox1.left + p1.getSpriteWidth(), clipbox1.top + p1.ypos, clipbox1.width, clipbox1.height);
		if (p2.side == LEFT)
			offsetClipBox2 = sf::FloatRect(clipbox2.left + p2.xpos, clipbox2.top + p2.ypos, clipbox2.width, clipbox2.height);
		else if (p2.side == RIGHT)
			offsetClipBox2 = sf::FloatRect(p2.xpos - clipbox2.width - clipbox2.left + p2.getSpriteWidth(), clipbox2.top + p2.ypos, clipbox2.width, clipbox2.height);
		sf::FloatRect intersectBox;
		if (offsetClipBox1.intersects(offsetClipBox2)) {
			// If player 1 is moving in the x direction and player 2 is standing still
			if (abs(p1.xvel) > 0 && p2.xvel == 0) {
				if (p1.xvel > 0 && p1.side == LEFT) {
					p2.xvel = p1.xvel;
					if (p2.againstWall)
						p1.xvel = 0;
				}
				else if (p1.xvel < 0 && p1.side == RIGHT) {
					p2.xvel = p1.xvel;
					if (p2.againstWall)
						p1.xvel = 0;
				}
			}
			// If player 2 is moving in the x direction and player 1 is standing still
			else if (abs(p2.xvel) > 0 && p1.xvel == 0) {
				if (p2.xvel > 0 && p2.side == LEFT) {
					p1.xvel = p2.xvel;
					if (p1.againstWall)
						p2.xvel = 0;
				}
				else if (p2.xvel < 0 && p2.side == RIGHT) {
					p1.xvel = p2.xvel;
					if (p1.againstWall)
						p2.xvel = 0;
				}
			}
			// If both are moving in opposing directions, set both vels to 0
			else if (abs(p1.xvel) > 0 && abs(p2.xvel) > 0) {
				if ((p1.xvel > 0) != (p2.xvel > 0)) {
					p2.xvel = 0;
					p1.xvel = 0;
				}
			}

			if (p2.againstWall && p2.state == WALK_STATE && p1.state == WALK_STATE) {
				p2.xvel = 0;
				p1.xvel = 0;
			}
			else if (p1.againstWall && p1.state == WALK_STATE && p2.state == WALK_STATE) {
				p2.xvel = 0;
				p1.xvel = 0;
			}

			// Airborne stuff
			if (abs(p1.yvel) > 0.0f) {
				float p1Center = (offsetClipBox1.left + offsetClipBox1.width / 2);
				float p2Center = (offsetClipBox2.left + offsetClipBox2.width / 2);
				if (p1Center < p2Center) {
					
				}

				if (p1.jumpSide == LEFT) {
					if (p2.side == RIGHT) {
						p1.xvel = 0;
						p2.xvel = p1.character->jumpX;
					}
					else if (p2.side == LEFT) {
						p2.xvel = -p1.character->jumpX;
					}
			}
				else if (p1.jumpSide == RIGHT) {
					if (p2.side == LEFT) {
				p1.xvel = 0;
						p2.xvel = -p1.character->jumpX;
					}
					else if (p2.side == RIGHT) {
						p2.xvel = p1.character->jumpX;
					}
				}
			}
			else if (abs(p2.yvel) > 0.0f) {

				if (p2.jumpSide == LEFT) {
					if (p1.side == RIGHT) {
						p2.xvel = 0;
						p1.xvel = p2.character->jumpX;
					}
					else if (p1.side == LEFT) {
						p1.xvel = -p2.character->jumpX;
					}
				}
				else if (p2.jumpSide == RIGHT) {
					if (p1.side == LEFT) {
				p2.xvel = 0;
						p1.xvel = -p2.character->jumpX;
					}
					else if (p1.side == RIGHT) {
						p1.xvel = p2.character->jumpX;
					}
				}
			}
		}
		/*if (offsetClipBox1.left < 0 || offsetClipBox1.width + offsetClipBox1.left > WINDOW_WIDTH) {
			if (p1.xvel < 0 && p1.side == LEFT)
				p1.xvel = 0;
			if (p1.xvel > 0 && p1.side == RIGHT)
				p1.xvel = 0;
			p1.againstWall = true;
		}
		else
			p1.againstWall = false;
		if (offsetClipBox2.left < 0 || offsetClipBox2.width + offsetClipBox2.left > WINDOW_WIDTH) {
			if (p2.xvel < 0 && p2.side == LEFT)
				p2.xvel = 0;
			if (p2.xvel > 0 && p2.side == RIGHT)
				p2.xvel = 0;
			p2.againstWall = true;
		}
		else
			p2.againstWall = false;
			*/
		//change window width to background width
		if (offsetClipBox1.left < -440 || offsetClipBox1.width + offsetClipBox1.left > WINDOW_WIDTH + 440) {
			if (p1.xvel < 0 && p1.side == LEFT)
				p1.xvel = 0;
			if (p1.xvel > 0 && p1.side == RIGHT)
				p1.xvel = 0;
			p2.againstWall = false;
			p1.againstWall = true;
		}
		else if (offsetClipBox2.left < -440 || offsetClipBox2.width + offsetClipBox2.left > WINDOW_WIDTH + 440) {
			if (p2.xvel < 0 && p2.side == LEFT)
				p2.xvel = 0;
			if (p2.xvel > 0 && p2.side == RIGHT)
				p2.xvel = 0;
			p2.againstWall = true;
			p1.againstWall = false;
		}
		else {
			p2.againstWall = false;
			p1.againstWall = false;
		}
	}

	if (p2.againstWall && p1.againstWall && abs(p1.yvel) > 0 && p1.jumpSide == LEFT) {
		p2.xvel = -p1.character->jumpX;
	}
	else if (p2.againstWall && p1.againstWall && abs(p1.yvel) > 0 && p1.jumpSide == RIGHT) {
		p2.xvel = p1.character->jumpX;
	}
	if (p1.againstWall && p2.againstWall && abs(p2.yvel) > 0 && p2.jumpSide == LEFT) {
		p1.xvel = -p2.character->jumpX;
	}
	else if (p1.againstWall && p2.againstWall && abs(p2.yvel) > 0 && p2.jumpSide == RIGHT) {
		p1.xvel = p2.character->jumpX;
	}
	/*
	cout << "p1: " << endl;
	cout << p1.againstWall << endl;
	cout << "p2: " << endl;
	cout << p2.againstWall << endl;*/
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
				//on collision, checks first if player getting hit was holding block while being in the correct state
				if (attacker.state != GRAB_STATE && defender.holdingBlock && defender.state != HITSTUN_STATE && defender.state != ATTACK_STATE && defender.state != AIRBORNE_STATE) {
					defender.block(attacker.getCurrentMove());
					blockSound.play();
				}
				else if (defender.state == AIRBORNE_STATE && attacker.state == GRAB_STATE) {
					//nothing happens
				}
				else {
					//if not blocking, player gets hit
					if (!attacker.getCurrentFrame().hit) {
						//cout << "hit!" << endl;
						defender.getHit(attacker.getCurrentMove());
						attacker.getCurrentFrame().hit = true;
						hitSound.play();
					}
					attacker.canCancel = true;
					return;
				}
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
		player.holdingBlock = false;
		player.jump(NEUTRAL);
	}
	else if (!player.left && player.jumping && player.right) {
		player.holdingBlock = false;
		player.jump(RIGHT);
	}
	else if (player.left && !player.jumping && player.right) {
		player.holdingBlock = true;
		player.doMove(IDLE);
	}
	else if (player.left && player.jumping && !player.right) {
		player.holdingBlock = false;
		player.jump(LEFT);
	}
	else if (!player.left && !player.jumping && player.right) {

		player.walk(RIGHT);
		//check if player is holding correct direction to block
		if (player.side == RIGHT) {
			player.holdingBlock = true;
		}
		else {
			player.holdingBlock = false;
		}
	}
	else if (player.left && !player.jumping && !player.right) {
		player.walk(LEFT);
		//check if player is holding correct direction to block
		if (player.side == LEFT) {
			player.holdingBlock = true;
		}
		else {
			player.holdingBlock = false;
		}
	}
	else if (!player.left && player.jumping && !player.right) {
		player.holdingBlock = false;
		player.jump(NEUTRAL);
	}
	else if (!player.left && !player.jumping && !player.right) {
		player.holdingBlock = false;
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
				//cout << hex << acc << endl;
				//cout << "indicatorflashon" << endl;
				indicatorFlashOn = true;

				player.indicator.updateIndicator(ONBEAT);


				if (acc == C_NATURAL) {
					player.doMove(JAB);
				}
				else if (acc == D_NATURAL) {
					player.doMove(STRONG);
				}
				else if (acc == E_NATURAL) {
					player.doMove(FIERCE);
				}
				else if (acc == F_NATURAL) {
					player.doMove(SHRT);
				}
				else if (acc == G_NATURAL) {
					player.doMove(FORWARD);
				}
				else if (acc == A_NATURAL) {
					player.doMove(ROUNDHOUSE);
				}
				else if (acc == B_NATURAL) {
					player.doMove(GRAB);
				}
				else if (acc == C_MAJOR) {
					player.doMove(CMAJ);
				}
				else if (acc == C_MAJOR_6) {
					player.doMove(CMAJ, 2, 4);
					if (player.meter < 1000)player.meter += player.getCurrentMove()->getMeterGain();
				}
				else if (acc == C_MAJOR_64) {
					player.doMove(CMAJ, 4, 6);
					if (player.meter < 1000)player.meter += player.getCurrentMove()->getMeterGain();
				}
				else if (acc == F_MAJOR_64) {
					player.doMove(CMAJ);
				}
				else if (acc == G_MAJOR) {
					player.doMove(GMAJ);
				}
				else if (acc == G_MAJOR_6) {
					player.doMove(CMAJ, 0, 3);
					if (player.meter < 1000)player.meter += player.getCurrentMove()->getMeterGain();
				}
				else if (acc == G_MAJOR_64) {
					player.doMove(CMAJ, 0, 5);
					if (player.meter < 1000)player.meter += player.getCurrentMove()->getMeterGain();
				}
				//cheats
				else if (acc == 0x540) {
					player.health = 1000;
				}
				else {
					player.hitstunFrames = 3;
					player.doMove(HITSTUN);
					player.health -= 50;
				}
				if (player.meter > 1000)player.meter = 1000;
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
	//delete player1;
}