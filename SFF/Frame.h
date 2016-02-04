#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class Frame
{
public:
	vector<sf::IntRect> hitboxes;
	vector<sf::IntRect> hurtboxes;
	vector<sf::RectangleShape> hitboxes_v;
	vector<sf::RectangleShape> hurtboxes_v;
	int x_move;
	int y_move;
	//boolean endofmove_flag;
	Frame();
	Frame(vector <sf::IntRect> hitboxes_n, vector <sf::IntRect> hurtboxes_n, vector <sf::RectangleShape> hitboxes_vn, vector <sf::RectangleShape> hurtboxes_vn);
	~Frame();
};

