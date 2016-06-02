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
	bool hit = 0;
	Frame();
	Frame(vector <sf::FloatRect>, vector <sf::FloatRect>, vector <sf::FloatRect>);
	Frame(vector <sf::FloatRect>, vector <sf::FloatRect>);

	void addBox(string type, sf::FloatRect box) {
		if (type == "clip") {
			clipboxes.push_back(box);
		}
		else if (type == "hurt") {
			hurtboxes.push_back(box);
		}
		else if (type == "hit") {
			hitboxes.push_back(box);
		}
	}

	~Frame() = default;
};

