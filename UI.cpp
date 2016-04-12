#include "stdafx.h"
#include "UI.h"

void UI::setPos(float x, float y) {
	xpos = x;
	ypos = y;
}

void UI::addDrawable(sf::Drawable& d) {
	drawVector.push_back(d);
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
