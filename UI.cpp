#include "stdafx.h"
#include "UI.h"


UI::UI(float _xpos, float _ypos, sf::Sprite _sprite) : 
	xpos(_xpos),
	ypos(_ypos),
	sprite(_sprite)
{
}

void UI::setPos(float x, float y) {
	xpos = x;
	ypos = y;
}

void UI::setSprite(sf::Sprite s) {
	sprite = s;
}

void UI::setData(int d) {
	data = d;
}

sf::Vector2f UI::getPos() {
	return sf::Vector2f(xpos, ypos);
}

int UI::getData() {
	return data;
}
