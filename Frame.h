#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class Frame
{
public:
	vector<sf::FloatRect> hitboxes;
	vector<sf::FloatRect> hurtboxes;
	vector<sf::FloatRect> clipboxes;
	int x_move;
	int y_move;
	bool hit;
	//boolean endofmove_flag;
	Frame();
	// No copy constructor
	//Frame(const Frame&) = delete;
	Frame(vector <sf::FloatRect> , vector <sf::FloatRect>, vector <sf::FloatRect>);
	Frame(vector <sf::FloatRect>, vector <sf::FloatRect>);
	~Frame() = default;
};

