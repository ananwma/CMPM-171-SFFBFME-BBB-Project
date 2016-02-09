#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <mmsystem.h>
#include <map>
#include <list>

//DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
//DEBUG

#include "input.h"
#include "GameStateManager.h"
#include "FightState.h"
#include "PauseState.h"
#include "Player.h"

#include "test.h"

#define NOTE_ON 144
using namespace std;

list<int> notes;
vector<HMIDIIN> activeDevices;

[event_receiver(native)]
class TestEventReceiver
{
public:
	void init() {
		//sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
		//sf::CircleShape shape(100.f);
		//shape.setFillColor(sf::Color::Green);
	}
	void recieveKeysDown(std::list<int> &notes) {
		// For now this just prints the list of notes pressed down
		/*for (auto i = notes.begin(); i != notes.end(); ++i)
			cout << *i << ' ';
		cout << endl;*/
	}
	void recieveKeysUp() {}
	void hookEvent(InputHandler* inputHandler) {
		__hook(&InputHandler::sendKeysDown, inputHandler, &TestEventReceiver::recieveKeysDown);
	}
	void unhookEvent(InputHandler* inputHandler) {
		__unhook(&InputHandler::sendKeysDown, inputHandler, &TestEventReceiver::recieveKeysDown);
	}
};

struct context {
	InputHandler input_handler;
	GameStateManager game_state_manager;
	sf::RenderWindow* window;

};


int main()
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	//sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);
	// Get a console for debugging with cout

	MIDIINCAPS device_capabilities;
	//cout << midiInGetNumDevs() << endl;
	//for (int dev_num = 0; dev_num < midiInGetNumDevs(); dev_num++) {
	//	midiInGetDevCaps(dev_num, &device_capabilities, sizeof device_capabilities);
	//	cout << device_capabilities.wMid;
	//}

	int numDevs = midiInGetNumDevs();
	//cout << endl << "Num Devs: " << numDevs << endl;
	HMIDIIN midi_device_handle;
	HMIDIIN midi_device_handle2;

	//Testing functor
	//midiFunctor mf = midiFunctor();
	//int address = &mf;

	// Open devices and push handles on to vector
	vector<HMIDIIN> devices;
	/*for (int i = 0; i < midiInGetNumDevs(); i++) {
	HMIDIIN device;
	cout<<midiInOpen(&device, i, (DWORD_PTR)mf, 0, CALLBACK_FUNCTION);
	cout<<midiInStart(device);
	devices.push_back(device);
	}*/


	InputHandler  inputHandler = InputHandler();
	InputHandler  inputHandler2 = InputHandler();
	inputHandler.prepareDevice();
	inputHandler2.prepareDevice();
	MIDIINCAPS caps;
	//midiInGetDevCaps(i, &caps, sizeof(MIDIINCAPS));

	//TestEventReceiver test;
	//test.hookEvent(&inputHandler2);

	// SFML Stuff
	sf::Texture texture;
	/*if (!texture.loadFromFile("sprites/bach_default.png"))
	{
	cerr << "Error loading texture" << endl;
	system("PAUSE");
	return EXIT_FAILURE;
	}
	texture.setSmooth(true);
	sf::Sprite sprite;
	sprite.setTexture(texture);*/

	/*while (window.isOpen())
	{
	sf::Event event;
	while (window.pollEvent(event))
	{
	if (event.type == sf::Event::Closed)
	window.close();
	}

	window.clear();
	window.draw(shape);
	sprite.move(sf::Vector2f(0.1, 0));
	window.draw(sprite);
	window.display();
	}*/

	//test t;
	//t.testing();

	//end of input
	int window_width = 1080;
	int window_height = 720;
	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Super Fugue Fighter");
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);
	float frameCounter = 0, switchFrame = 100, frameSpeed = 500;
	sf::Clock clock;


	//input 
	//sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	/*context c;
	GameStateManager gsm;
	c.game_state_manager = gsm;
	c.input_handler = inputHandler2;
	c.window = &window;

	state_ptr fight_state_ptr(new FightState(&gsm, &inputHandler2, &window));
	FightState *fsp = new FightState(&gsm, &inputHandler2, &window);
	gsm.runState(fsp);
	//state_ptr pause_state_ptr(new PauseState(&gsm, &inputHandler2));
	PauseState *psp = new PauseState(&gsm, &inputHandler2, &window);
	gsm.runState(psp);
	delete fsp;
	delete psp;
	_CrtDumpMemoryLeaks();
	return 0;*/
	//end input


	//create Bach and his moves, from frames up
	float player1start_x = 1000.0f;
	float player1start_y = 1000.0f;

	float player2start_x = 1000.0f;
	float player2start_y = 1000.0f;

	int spriteWidth = 68;
	int spriteHeight = 105;

	//move to frame?

	//idle frame 1 hitboxes
	vector <sf::FloatRect> idle1_hit;
	idle1_hit.push_back(sf::FloatRect());
	//idle frame 1 hurtboxes
	vector <sf::FloatRect> idle1_hurt;
	idle1_hurt.push_back(sf::FloatRect(player1start_x, player1start_y, 60, 100));
	//idle frame 1 visible hitboxes
	vector <sf::RectangleShape> idle1_hit_v;
	idle1_hit_v.push_back(sf::RectangleShape());
	//idle frame 1 visible hurtboxes
	vector <sf::RectangleShape> idle1_hurt_v;
	sf::RectangleShape idle1hurtb(sf::Vector2f(60, 100));
	idle1hurtb.setFillColor(sf::Color::Blue);
	idle1hurtb.setOrigin(player1start_x, player1start_y);
	idle1_hurt_v.push_back(idle1hurtb);

	//idle frame 2 hitboxes
	vector <sf::FloatRect> idle2_hit;
	idle2_hit.push_back(sf::FloatRect());
	//idle frame 2 hurtboxes
	vector <sf::FloatRect> idle2_hurt;
	idle2_hurt.push_back(sf::FloatRect(player1start_x, player1start_y, 60, 100));
	//idle frame 2 visible hitboxes
	vector <sf::RectangleShape> idle2_hit_v;
	idle2_hit_v.push_back(sf::RectangleShape());
	//idle frame 2 visible hurtboxes
	vector <sf::RectangleShape> idle2_hurt_v;
	sf::RectangleShape idle2hurtb(sf::Vector2f(60, 100));
	idle2hurtb.setFillColor(sf::Color::Blue);
	idle2hurtb.setOrigin(player1start_x, player1start_y);
	idle2_hurt_v.push_back(idle2hurtb);

	//idle frame 3 hitboxes
	vector <sf::FloatRect> idle3_hit;
	idle3_hit.push_back(sf::FloatRect());
	//idle frame 3 hurtboxes
	vector <sf::FloatRect> idle3_hurt;
	idle3_hurt.push_back(sf::FloatRect(player1start_x, player1start_y, 60, 100));
	//idle frame 3 visible hitboxes
	vector <sf::RectangleShape> idle3_hit_v;
	idle3_hit_v.push_back(sf::RectangleShape());
	//idle frame 3 visible hurtboxes
	vector <sf::RectangleShape> idle3_hurt_v;
	sf::RectangleShape idle3hurtb(sf::Vector2f(60, 100));
	idle3hurtb.setFillColor(sf::Color::Blue);
	idle3hurtb.setOrigin(player1start_x, player1start_y);
	idle3_hurt_v.push_back(idle3hurtb);

	//idle frame 4 hitboxes
	vector <sf::FloatRect> idle4_hit;
	idle4_hit.push_back(sf::FloatRect());
	//idle frame 4 hurtboxes
	vector <sf::FloatRect> idle4_hurt;
	idle4_hurt.push_back(sf::FloatRect(player1start_x, player1start_y, 60, 100));
	//idle frame 4 visible hitboxes
	vector <sf::RectangleShape> idle4_hit_v;
	idle4_hit_v.push_back(sf::RectangleShape());
	//idle frame 4 visible hurtboxes
	vector <sf::RectangleShape> idle4_hurt_v;
	sf::RectangleShape idle4hurtb(sf::Vector2f(60, 100));
	idle4hurtb.setFillColor(sf::Color::Blue);
	idle4hurtb.setOrigin(player1start_x, player1start_y);
	idle4_hurt_v.push_back(idle4hurtb);

	//idle frames list
	vector <Frame> bach_idle;
	Frame idle1 = Frame(idle1_hit, idle1_hurt, idle1_hit_v, idle1_hurt_v);
	Frame idle2 = Frame(idle2_hit, idle2_hurt, idle2_hit_v, idle2_hurt_v);
	Frame idle3 = Frame(idle3_hit, idle3_hurt, idle3_hit_v, idle3_hurt_v);
	Frame idle4 = Frame(idle4_hit, idle4_hurt, idle4_hit_v, idle4_hurt_v);
	bach_idle.push_back(idle1);
	bach_idle.push_back(idle2);
	bach_idle.push_back(idle3);
	bach_idle.push_back(idle4);
	//walk frames list
	vector <Frame> bach_walk;
	//jump frames list
	vector <Frame> bach_jump;
	//attack frames list
	vector <Frame> bach_attack;
	//hurt frames list
	vector <Frame> bach_hurt;
	//moves list

	//move to moves?

	vector <Move> bachMoves;
	bachMoves.push_back(Move(bach_idle));
	bachMoves.push_back(Move(bach_walk));
	bachMoves.push_back(Move(bach_jump));
	bachMoves.push_back(Move(bach_attack));
	bachMoves.push_back(Move(bach_hurt));
	
	Character bach = Character(bachMoves,"Ryu.png");

	//enum bachPossibleMoves { Idle, Walk, Jump, Attack, Hurt };
	//sf::Vector2i source(0, Idle);

	Player player1(bach, player1start_x, player1start_y);
	Player player2(bach, player2start_x, player2start_y);

	player1.pImage.setPosition(100, 500);
	player2.pImage.setPosition(800, 500);

	bool jumping = false;
	bool falling = false;
	bool walking = false;
	bool facing_right = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		if (player1.pImage.getPosition().x < player2.pImage.getPosition().x) facing_right = true;
		else facing_right = false;

		if (jumping) {
			if (player1.pImage.getPosition().y <= 400) {
				jumping = false;
				falling = true;
			}
			else {
				player1.pImage.move(0, -0.500000000f);
			}
		}
		if (falling) {
			if (player1.pImage.getPosition().y >= 500) {
				falling = false;
			}
			else {
				player1.pImage.move(0, 0.500000000f);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			//right
			if ((player1.pImage.getPosition().x + spriteWidth / 2 >= player2.pImage.getPosition().x - spriteWidth / 2 && facing_right) || player1.pImage.getPosition().x + spriteWidth / 2 >= window_width) {
			}
			else{
				player1.currentCharacter.currentMove = 1;
				player1.currentCharacter.currentMoveFrame = 0;
				player1.pImage.move(0.500000f, 0);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			//left 
			if ((player1.pImage.getPosition().x + spriteWidth / 2 <= player2.pImage.getPosition().x - spriteWidth / 2 && !facing_right) || player1.pImage.getPosition().x <= 0) {
			}
			else{
				player1.currentCharacter.currentMove = 1;
				player1.pImage.move(-0.5000000f, 0);
				player1.currentCharacter.currentMoveFrame = 0;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			//jump
			if(!jumping && !falling) jumping = true;
			player1.currentCharacter.currentMove = 2;
			player1.currentCharacter.currentMoveFrame = 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
			player1.currentCharacter.currentMove = 3;
			player1.currentCharacter.currentMoveFrame = 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			player1.currentCharacter.currentMove = 4;
			player1.currentCharacter.currentMoveFrame = 0;
		}
		//std::cout << clock.getElapsedTime().asSeconds() << std::endl;
		//find move based on input read, if0 state allows it and is different from currentMove:
		//set player1.currentMove, set player1.currentMoveFrame to 0
		//else player1.currentMoveFrame++
		frameCounter += frameSpeed * clock.restart().asSeconds();
		if (frameCounter >= switchFrame){
		frameCounter = 0;
		player1.currentCharacter.currentMoveFrame++;
		if (player1.currentCharacter.currentMoveFrame > (player1.currentCharacter.moveList.at(player1.currentCharacter.currentMove).frames.size()) - 1) {
			player1.currentCharacter.currentMove = 0;
			player1.currentCharacter.currentMoveFrame = 0;
}
		
		}
		//if player1.currentMoveFrame > player1.currentMove.frames.length:
		//set player1.currentMove to idle 
		//player1Image.setTextureRect(sf::IntRect(player1.currentMoveFrame * spriteWidth, player1.currentMove.spriteRow * spriteHeight, spriteWidth, SpriteHeight));
		player1.pImage.setTextureRect(sf::IntRect(player1.currentCharacter.currentMoveFrame * spriteWidth, player1.currentCharacter.currentMove * spriteHeight, spriteWidth, spriteHeight));
		player2.pImage.setTextureRect(sf::IntRect(player2.currentCharacter.currentMoveFrame * spriteWidth, player2.currentCharacter.currentMove * spriteHeight, spriteWidth, spriteHeight));
		cout << (player1.pImage.getPosition().x) << endl;

		//window.draw(shape);
		window.draw(player1.pImage);
		window.draw(player1.hitboxes_v);
		window.draw(player1.hurtboxes_v);

		window.draw(player2.pImage);

		window.display();
		window.clear(sf::Color(0,200,0,255));
	}

	return 0;
}