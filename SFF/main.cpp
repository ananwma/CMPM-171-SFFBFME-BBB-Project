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
	
	vector <Frame> bach_idle;
	//bach_idle.push_back(Frame(sf::IntRect(),sf::IntRect(player1start_x,player1start_y, 10, 10),sf::RectangleShape, sf::RectangleShape))
	vector <Frame> bach_walk;
	vector <Frame> bach_jump;
	vector <Frame> bach_attack;
	vector <Frame> bach_hurt;
	vector <Move> bachMoves;
	bachMoves.push_back(Move(bach_idle));
	bachMoves.push_back(Move(bach_walk));
	bachMoves.push_back(Move(bach_jump));
	bachMoves.push_back(Move(bach_attack));
	bachMoves.push_back(Move(bach_hurt));
	Character bach = Character(bachMoves,"Ryu.png");
	enum bachPossibleMoves { Idle, Walk, Jump, Attack, Hurt };
	sf::Vector2i source(0, Idle);
	
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
			source.y = Walk;
			player1.pImage.move(0.1000000, 0);
		}


		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			source.y = Walk;
			player1.pImage.move(-0.10000000, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			source.y = Jump;
			player1.pImage.move(0, 0.100000000);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
			source.y = Attack;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			source.y = Hurt;
		}
		std::cout << clock.getElapsedTime().asSeconds() << std::endl;
		//find move based on input read, if state allows it and is different from currentMove:
		//set player1.currentMove, set player1.currentMoveFrame to 0
		//else player1.currentMoveFrame++
		frameCounter += frameSpeed * clock.restart().asSeconds();
		if (frameCounter >= switchFrame){
		frameCounter = 0;
	source.x++;
		if (source.x * 68 >= player1.pTexture.getSize().x) {
			source.x = 0;
}
		
		}
		//if player1.currentMoveFrame > player1.currentMove.frames.length:
		//set player1.currentMove to idle 
		//player1Image.setTextureRect(sf::IntRect(player1.currentMoveFrame * spriteWidth, player1.currentMove.spriteRow * spriteHeight, spriteWidth, SpriteHeight));
		player1.pImage.setTextureRect(sf::IntRect(source.x * 68, source.y * 105, 68, 105));

		
		//window.draw(shape);
		window.draw(player1.pImage);
		window.display();
		window.clear(sf::Color(0,200,0,255));
	}

	return 0;
}
