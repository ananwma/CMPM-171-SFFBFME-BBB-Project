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

FightState::FightState(Game &_game) :
	game(_game),
	bassline(game, { C1, C2, F1, F2, G1, G2 }, KEY_CM, 70),
	dust1(10, "sprites/smoke.png", 128, 128, 10, 0),
	dust2(10, "sprites/smoke.png", 128, 128, 10, 0),
	hitspark1(10, "sprites/hit_spark2.png", 245, 260, 10, 200),
	hitspark2(10, "sprites/hit_spark2.png", 245, 260, 10, 200),
	blockspark1(10, "sprites/block_spark3.png", 245, 260, 10, 100),
	blockspark2(10, "sprites/block_spark3.png", 245, 260, 10, 100)
{
}

void FightState::init() {

	running = true;

	game.currentScreen.setStage(chstage);
	game.currentScreen.stage.front.move(-game.currentScreen.stage.window_offset, 0);
	game.currentScreen.stage.med.move(-game.currentScreen.stage.window_offset, 0);
	game.currentScreen.stage.window_offset = 0;
	game.currentScreen.stage.base.setPosition(-440, 0);

	// CHANGE LATER // 
	game.currentScreen.stage.front.setPosition(-230, WINDOW_HEIGHT - 200);
	game.currentScreen.stage.med.setPosition(-200, WINDOW_HEIGHT - 400);
	// CHANGE LATER // 

	hitspark1.setContinuous(false);
	hitspark2.setContinuous(false);
	blockspark1.setContinuous(false);
	blockspark2.setContinuous(false);

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

	if (!HUDTexture.loadFromFile("UIDraft.png")) {
		std::cerr << "Could not find image file!\n";
		exit(EXIT_FAILURE);
	}
	round1.loadFromFile("sprites/round1.png");
	round2.loadFromFile("sprites/round2.png");
	roundFinal.loadFromFile("sprites/roundFinal.png");
	KO.loadFromFile("sprites/KO.png");
	timeUp.loadFromFile("sprites/time.png");
	player1wins.loadFromFile("sprites/p1win.png");
	player2wins.loadFromFile("sprites/p2win.png");
	tie.loadFromFile("sprites/draw.png");
	roundText.setTexture(round1);
	roundText.setPosition(WINDOW_WIDTH / 2 - roundText.getGlobalBounds().width/2, WINDOW_HEIGHT / 2 - roundText.getGlobalBounds().height);

	HUDOverlay.setTexture(HUDTexture);

	player1portraitart.setPosition(70, 39);
	///////todo
	player1portraitart.setTexture(game.playerOne.portrait);

	player2portraitart.setPosition(WINDOW_WIDTH - 66, 39);
	player2portraitart.setTexture(game.playerOne.portrait);
	///////
	player2portraitart.scale(sf::Vector2f(-1, 1));

	player_1_HP.setSize(sf::Vector2f(BARSIZE, 28));
	player_1_HP.setFillColor(sf::Color(100, 250, 50));
	player_1_HP.setPosition(190, 80);

	player_2_HP.setSize(sf::Vector2f(BARSIZE, 28));
	player_2_HP.setFillColor(sf::Color(100, 250, 50));
	player_2_HP.setPosition(WINDOW_WIDTH - BARSIZE - 188, 80);

	player_1_meter.setPosition(155, 116);
	player_1_meter.setSize(sf::Vector2f(BARSIZE, 28));
	player_1_meter.setFillColor(sf::Color(0, 255, 255));

	player_2_meter.setPosition(WINDOW_WIDTH - BARSIZE - 151, 116);
	player_2_meter.setSize(sf::Vector2f(BARSIZE, 28));
	player_2_meter.setFillColor(sf::Color(0, 255, 255));

	/*player_1_HP_box.setSize(sf::Vector2f(400, 30));
	player_1_HP_box.setOutlineThickness(5);
	player_1_HP_box.setOutlineColor(sf::Color(250, 250, 250));
	player_1_HP_box.setFillColor(sf::Color::Transparent);

	player_2_HP_box.setSize(sf::Vector2f(700, 30));
	player_2_HP_box.setPosition(WINDOW_WIDTH - 400, 0);
	player_2_HP_box.setOutlineThickness(5);
	player_2_HP_box.setOutlineColor(sf::Color(250,250,250));
	player_2_HP_box.setFillColor(sf::Color::Transparent);

	player_1_meter_box.setOutlineThickness(5);
	player_1_meter_box.setOutlineColor(sf::Color(250, 250, 250));
	player_1_meter_box.setPosition(0, 35);
	player_1_meter_box.setSize(sf::Vector2f(400, 30));
	player_1_meter_box.setFillColor(sf::Color::Transparent);

	player_2_meter_box.setOutlineThickness(5);
	player_2_meter_box.setOutlineColor(sf::Color(250, 250, 250));
	player_2_meter_box.setSize(sf::Vector2f(400, 30));
	player_2_meter_box.setPosition(WINDOW_WIDTH - 400, 35);
	player_2_meter_box.setFillColor(sf::Color::Transparent);*/

	timer.setSize(sf::Vector2f(175, 75));
	timer.setFillColor(sf::Color(250, 250, 250));
	timer.setPosition(WINDOW_WIDTH / 2 - 100, 0);

	player_1_round_win_1.setRadius(13);
	player_1_round_win_1.setPosition(WINDOW_WIDTH / 2 - 170, 169);
	player_1_round_win_1.setFillColor(sf::Color(255, 255, 0));

	player_1_round_win_2.setRadius(13);
	player_1_round_win_2.setPosition(WINDOW_WIDTH / 2 - 125, 169);
	player_1_round_win_2.setFillColor(sf::Color(255, 255, 0));

	player_2_round_win_1.setRadius(13);
	player_2_round_win_1.setPosition(WINDOW_WIDTH / 2 + 147, 169);
	player_2_round_win_1.setFillColor(sf::Color(255, 255, 0));

	player_2_round_win_2.setRadius(13);
	player_2_round_win_2.setPosition(WINDOW_WIDTH / 2 + 102, 169);
	player_2_round_win_2.setFillColor(sf::Color(255, 255, 0));

	if (!font.loadFromFile("fonts/Altgotisch.ttf")) {
		cerr << "Font not found!\n";
		exit(EXIT_FAILURE);
	}
	timer_text.setFont(font);
	timer_text.setColor(sf::Color(250, 250, 250));
	time = 99.0f;
	char temp[256];
	sprintf(temp, "%f", time);
	timer_text.setString(temp);
	timer_text.setCharacterSize(80);
	timer_text.setPosition(WINDOW_WIDTH / 2 - 30, 42);

	game.playerOne.indicator.bSprite.setPosition(0, 150);
	game.playerTwo.indicator.bSprite.setPosition(WINDOW_WIDTH - 150, 150);

	pauseOverlay.setFillColor(sf::Color(0, 0, 0, 200));
	pauseOverlay.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));

	camera_view.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	camera_view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	HUD.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
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
	clock.restart();
}

void FightState::hookEvent() {
	time = saveTime;
	clock.restart();
	__hook(&InputHandler::sendKeysDown, game.inputHandler.get(), &GameState::receiveKeysDown);
	__hook(&InputHandler::sendKeysUp, game.inputHandler.get(), &GameState::receiveKeysUp);
}

void FightState::reset() {
	roundstart = true;
	acceptingInput = false;
	inc = 0;
	game.playerOne.doMove("idle");
	game.playerTwo.doMove("idle");
	//100 = ground level
	game.playerOne.setPosition(WINDOW_WIDTH / 50, GROUND);
	game.playerTwo.setPosition(WINDOW_WIDTH / 1.2, GROUND);

	time = 99.0f;
	char temp[256];
	sprintf(temp, "%f", time);
	timer_text.setString(temp);
	clock.restart();

	game.playerOne.health = game.playerOne.getMaxHealth();
	game.playerOne.meter = 0;
	game.playerTwo.health = game.playerOne.getMaxHealth();
	game.playerTwo.meter = 0;
	game.beat = 425.0f;
	beatThreshold = 100 * (game.beat / 500);
	frameSpeed = 1000 * (500 / game.beat);
	game.playerOne.setBeat(game.beat);
	game.playerTwo.setBeat(game.beat);
	bassline.setBassline({ C1, C2, F1, F2, G1, G2 });
	phase = 0;
}

void FightState::doRoundStart() {
	int round = game.playerOne.roundWins + game.playerTwo.roundWins;
	if (round == 0) {
		roundText.setTexture(round1);
		roundText.setTextureRect(sf::IntRect(0, 0, round1.getSize().x, round1.getSize().y));
	}
	else if (round == 1) {
		roundText.setTexture(round2);
		roundText.setTextureRect(sf::IntRect(0, 0, round2.getSize().x, round2.getSize().y));
	}
	else if (round == 2) {
		roundText.setTexture(roundFinal);
		roundText.setTextureRect(sf::IntRect(0, 0, roundFinal.getSize().x, roundFinal.getSize().y));
	}
	roundText.setPosition(WINDOW_WIDTH / 2 - roundText.getGlobalBounds().width / 2, WINDOW_HEIGHT / 2 - roundText.getGlobalBounds().height);
	//roundText.setScale(inc, inc);
	roundText.setColor(sf::Color(255, 255, 255, 255 - inc));
	if (inc > 255) {
		roundstart = false;
		acceptingInput = true;
	}
	inc += 3;
}

void FightState::doRoundEnd() {
	if (time <= 0) {
		roundText.setTexture(timeUp);
		roundText.setTextureRect(sf::IntRect(0, 0, timeUp.getSize().x, timeUp.getSize().y));
	}
	else {
		roundText.setTexture(KO);
		roundText.setTextureRect(sf::IntRect(0, 0, KO.getSize().x, KO.getSize().y));
	}
	roundText.setPosition(WINDOW_WIDTH / 2 - roundText.getGlobalBounds().width / 2, WINDOW_HEIGHT / 2 - roundText.getGlobalBounds().height);
	roundText.setColor(sf::Color(255, 255, 255, 255));
	if (inc > 255) {
		roundend = false;
		reset();
	}
	inc += 1;
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		saveTime = time;
		game.window.draw(pauseOverlay);
		unhookEvent();
		PauseState pauseState(game);
		game.gsm.pauseState(*this, &pauseState);
	}

	if (roundstart)
		doRoundStart();
	else if (roundend)
		doRoundEnd();

	// gonna change this later
	if (game.playerOne.getSide() == LEFT) {
		dust1.setEmitter(sf::Vector2f(game.playerOne.getPosition().x + 100, game.playerOne.getPosition().y + 400));
		dust2.setEmitter(sf::Vector2f(game.playerTwo.getPosition().x + 80, game.playerTwo.getPosition().y + 400));
	}
	else if (game.playerOne.getSide() == RIGHT) {
		dust1.setEmitter(sf::Vector2f(game.playerOne.getPosition().x + 80, game.playerOne.getPosition().y + 400));
		dust2.setEmitter(sf::Vector2f(game.playerTwo.getPosition().x + 100, game.playerTwo.getPosition().y + 400));
	}
	sf::Time elapsed = emitterClock.restart();
	dust1.update(elapsed);
	dust2.update(elapsed);
	//

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

	if (acceptingInput) {
		processInput(game.playerOne, inputP1);
		processInput(game.playerTwo, inputP2);
	}

	//camera controls 
	camera_center = sf::Vector2f((game.playerOne.getPosition().x + game.playerTwo.getPosition().x + 438) / 2, WINDOW_HEIGHT / 2);
	if (camera_center.x > WINDOW_WIDTH - 550) camera_center.x = WINDOW_WIDTH - 550;
	if (camera_center.x < 550) camera_center.x = 550;
	camera_view.setCenter(camera_center);

	//constrain like camera
	game.currentScreen.stage.med.setPosition((game.playerOne.getPosition().x + game.playerTwo.getPosition().x + 438) / 4 - 1000, WINDOW_HEIGHT - 400);

	//collision and hitsparks
	sf::FloatRect* p = game.collisionManager.checkBoxes(game.playerOne, game.playerTwo);
	sf::FloatRect collisionPoint;
	if (p != NULL) {
		collisionPoint = *p;
		hitspark1.setEmitter(sf::Vector2f(collisionPoint.left - 245, collisionPoint.top - 260));
		blockspark1.setEmitter(sf::Vector2f(collisionPoint.left - 122, collisionPoint.top - 130));
		if (game.playerTwo.getCurrentMove()->moveName == "hitstun") {
			hitspark1.activate();
			hitSound.play();
		}
		else if (game.playerTwo.getCurrentMove()->moveName == "blockstun") {
			blockspark1.activate();
			blockSound.play();
		}
	}
	p = game.collisionManager.checkBoxes(game.playerTwo, game.playerOne);
	if (p != NULL) {
		collisionPoint = *p;
		hitspark2.setEmitter(sf::Vector2f(collisionPoint.left - 245, collisionPoint.top - 260));
		blockspark2.setEmitter(sf::Vector2f(collisionPoint.left - 122, collisionPoint.top - 130));
		if (game.playerOne.getCurrentMove()->moveName == "hitstun") {
			hitspark2.activate();
			hitSound.play();
		}
		else if (game.playerOne.getCurrentMove()->moveName == "blockstun") {
			blockspark2.activate();
			blockSound.play();
		}
	}
	hitspark1.update(elapsed);
	hitspark2.update(elapsed);
	blockspark1.update(elapsed);
	blockspark2.update(elapsed);
	game.collisionManager.checkClipBoxes(game.playerOne, game.playerTwo, camera_view.getCenter().x - 988, camera_view.getCenter().x + 988);

	game.playerOne.update();
	game.playerTwo.update();
	game.playerOne.updateSide(game.playerTwo);
	game.playerTwo.updateSide(game.playerOne);

	time -= clock.getElapsedTime().asSeconds();
	if (time < 0) time = 0.0;
	char temp[256];
	sprintf(temp, "%d", (int)time);
	timer_text.setString(temp);

	if (!roundend) {
		if (game.playerOne.health <= 0) {
			game.playerTwo.roundWins++;
			if (game.playerTwo.roundWins == 2) {
				game.window.draw(player_2_round_win_2);
				ResultsState results(game);
				game.gsm.stopState(*this, &results);
			}
			else {
				inc = 0;
				acceptingInput = false;
				roundend = true;
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
				inc = 0;
				acceptingInput = false;
				roundend = true;
			}
		}
		else if (time <= 0) {
			cout << "entered loop" << endl;
			if (game.playerOne.health < game.playerTwo.health) {
				cout << "sit1" << endl;
				game.playerTwo.roundWins++;
				inc = 0;
				acceptingInput = false;
				roundend = true;
			}
			else if (game.playerTwo.health < game.playerOne.health) {
				cout << "sit2" << endl;
				game.playerOne.roundWins++;
				inc = 0;
				acceptingInput = false;
				roundend = true;
			}
			else {
				cout << "sit3" << endl;
				game.playerOne.roundWins++;
				game.playerTwo.roundWins++;
				inc = 0;
				acceptingInput = false;
				roundend = true;
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
		//game.beat = 275.0f;
		//temp fix
		game.beat = 350.0f;
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
		game.playerOne.hitstunFrames--;
		game.playerOne.blockstunFrames--;
		game.playerTwo.hitstunFrames--;
		game.playerTwo.blockstunFrames--;
		game.playerTwo.updateAnimFrame();
		game.playerOne.updateAnimFrame();
	}

	//move_camera(game.playerOne, game.playerTwo);
	//move_camera(game.playerTwo, game.playerOne);

	//cout << "offset" << endl;
	//cout << game.currentScreen.stage.window_offset << endl;

	sf::Vector2<float> p1HP(BARSIZE*(game.playerOne.health / 1000.0), 30);
	sf::Vector2<float> p2HP(BARSIZE*(game.playerTwo.health / 1000.0), 30);
	sf::Vector2<float> p1M(BARSIZE*(game.playerOne.meter / 1000.0), 30);
	sf::Vector2<float> p2M(BARSIZE*(game.playerTwo.meter / 1000.0), 30);
	//cout << game.playerOne.meter << endl;
	//cout << p2HP.x << endl;
	player_1_HP.setSize(p1HP);
	player_2_HP.setSize(p2HP);
	player_1_meter.setSize(p1M);
	player_2_meter.setSize(p2M);

	//cout << dec<<game.currentScreen.stage.window_offset << endl;
	//cout << dec << game.playerTwo.xpos << endl;
	//cout << game.playerOne.roundWins << endl;
}

void FightState::draw() {
	game.window.clear();
	game.window.setView(camera_view);
	game.window.draw(game.currentScreen.stage.base);
	game.window.draw(game.currentScreen.stage.med);
	game.window.draw(game.currentScreen.stage.front);
	game.window.draw(game.playerOne.sprite);
	game.window.draw(game.playerTwo.sprite);
	drawBoxes(game.playerOne, 1, 1, 1);
	drawBoxes(game.playerTwo, 1, 1, 1);

	//gonna change this later
	if (game.playerOne.getVelocity().x != 0 || game.playerOne.getVelocity().y != 0) {
		game.window.draw(dust1);
	}
	if (game.playerTwo.getVelocity().x != 0 || game.playerTwo.getVelocity().y != 0) {
		game.window.draw(dust2);
	}
	//
	game.window.draw(hitspark1);
	game.window.draw(hitspark2);
	game.window.draw(blockspark1);
	game.window.draw(blockspark2);

	game.window.setView(HUD);
	if (roundstart)
		game.window.draw(roundText);
	if (roundend) {
		game.window.draw(roundText);
	}

	game.window.draw(HUDOverlay);
	game.window.draw(player_1_HP);
	game.window.draw(player_2_HP);
	game.window.draw(player_1_meter);
	game.window.draw(player_2_meter);
	//game.window.draw(player_1_HP_box);
	//game.window.draw(player_2_HP_box);
	//game.window.draw(player_1_meter_box);
	//game.window.draw(player_2_meter_box);
	//game.window.draw(timer);
	game.window.draw(player1portraitart);
	game.window.draw(player2portraitart);
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
		if (player.getSide() == LEFT)
			player.doMove("fjump");
		else if (player.getSide() == RIGHT)
			player.doMove("bjump");
	}
	else if (player.left && !player.jumping && player.right) {
		player.holdingBlock = true;
		player.doMove("idle");
	}
	else if (player.left && player.jumping && !player.right) {
		player.holdingBlock = false;
		if (player.getSide() == LEFT)
			player.doMove("bjump");
		else if (player.getSide() == RIGHT)
			player.doMove("fjump");
	}
	else if (!player.left && !player.jumping && player.right) {

		if (player.getSide() == LEFT)
			player.doMove("walk");
		else if (player.getSide() == RIGHT)
			player.doMove("backwalk");
		//check if player is holding correct direction to block
		if (player.getSide() == RIGHT) {
			player.holdingBlock = true;
		}
		else {
			player.holdingBlock = false;
		}
	}
	else if (player.left && !player.jumping && !player.right) {
		if (player.getSide() == LEFT)
			player.doMove("backwalk");
		else if (player.getSide() == RIGHT)
			player.doMove("walk");
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
				//cout << hex << acc << endl;
				//cout << "indicatorflashon" << endl;
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
				else if (acc == B_NATURAL) {
					player.doMove("grab");
				}
				else if (acc == C_MAJOR) {
					player.doMove("shoryuken");
				}
				else if (acc == C_MAJOR_6) {
					//todo re add power adjust 
					player.doMove("shoryuken");
					//if (player.meter < 1000)player.meter += player.getCurrentMove()->getMeterGain();
				}
				else if (acc == C_MAJOR_64) {
					player.doMove("shoryuken");
					//if (player.meter < 1000)player.meter += player.getCurrentMove()->getMeterGain();
				}
				else if (acc == F_MAJOR_64) {
					player.doMove("shoryuken");
				}
				else if (acc == G_MAJOR) {
					player.doMove("tatsu");
				}
				else if (acc == G_MAJOR_6) {
					player.doMove("tatsu");
					//if (player.meter < 1000)player.meter += player.getCurrentMove()->getMeterGain();
				}
				else if (acc == G_MAJOR_64) {
					player.doMove("tatsu");
					//if (player.meter < 1000)player.meter += player.getCurrentMove()->getMeterGain();
				}
				//cheats
				else if (acc == 0x540) {
					player.health = -1;
				}
				else {
					player.hitstunFrames = 3;
					player.doMove("hitstun");
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
}