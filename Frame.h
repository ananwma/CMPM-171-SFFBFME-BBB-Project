#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class Frame
{
public:
	vector<sf::FloatRect> hitboxes;
	vector<sf::FloatRect> hurtboxes;
	int x_move;
	int y_move;
	//boolean endofmove_flag;
	Frame();
	Frame(vector <sf::FloatRect> hitboxes_n, vector <sf::FloatRect> hurtboxes_n);
	~Frame();
};

