#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class Frame
{
public:
	vector<sf::FloatRect> hitboxes;
	vector<sf::FloatRect> hurtboxes;
	vector<sf::RectangleShape> hitboxes_v;
	vector<sf::RectangleShape> hurtboxes_v;
	int x_move;
	int y_move;
	//boolean endofmove_flag;
	Frame();
	Frame(vector <sf::FloatRect> hitboxes_n, vector <sf::FloatRect> hurtboxes_n, vector <sf::RectangleShape> hitboxes_vn, vector <sf::RectangleShape> hurtboxes_vn);
	~Frame();
};

