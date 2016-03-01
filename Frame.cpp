#include "stdafx.h"
#include "Frame.h"




Frame::Frame() {

}
Frame::Frame(vector <sf::FloatRect> hitboxes_n, vector <sf::FloatRect> hurtboxes_n, vector <sf::FloatRect> clipboxes_n)
{
	hitboxes = hitboxes_n;
	hurtboxes = hurtboxes_n;
	clipboxes = clipboxes_n;
	hit = false;
}

//Temporary additional ctor without clipboxes
Frame::Frame(vector <sf::FloatRect> hitboxes_n, vector <sf::FloatRect> hurtboxes_n)
{
	hitboxes = hitboxes_n;
	hurtboxes = hurtboxes_n;
	hit = false;
}
