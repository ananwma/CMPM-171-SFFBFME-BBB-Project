#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <string>
#include <vector>

#include "Player.h"

using namespace std;




int main()
{
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Super Fugue Fighter");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	float frameCounter = 0, switchFrame = 100, frameSpeed = 500;
	sf::Clock clock;

	//create Bach and his moves, from frames up
	int player1start_x = 300;
	int player1start_y = 1000;
	int spriteWidth = 68;
	int spriteHeight = 105;
	
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			player1.currentCharacter.currentMove = 1;
			player1.currentCharacter.currentMoveFrame = 0;
			player1.pImage.move(0.1000000, 0);
		}


		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			player1.currentCharacter.currentMove = 1;
			player1.pImage.move(-0.10000000, 0);
			player1.currentCharacter.currentMoveFrame = 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			player1.currentCharacter.currentMove = 2;
			player1.currentCharacter.currentMoveFrame = 0;
			player1.pImage.move(0, 0.100000000);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
			player1.currentCharacter.currentMove = 3;
			player1.currentCharacter.currentMoveFrame = 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			player1.currentCharacter.currentMove = 4;
			player1.currentCharacter.currentMoveFrame = 0;
		}
		std::cout << clock.getElapsedTime().asSeconds() << std::endl;
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

		
		//window.draw(shape);
		window.draw(player1.pImage);
		window.draw(player1.hitboxes_v);
		window.draw(player1.hurtboxes_v);
		window.display();
		window.clear(sf::Color(0,200,0,255));
	}

	return 0;
}