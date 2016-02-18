#include "stdafx.h"
#include "Frame.h"




Frame::Frame() {

}
Frame::Frame(vector <sf::FloatRect> hitboxes_n, vector <sf::FloatRect> hurtboxes_n)
{
	hitboxes = hitboxes_n;
	hurtboxes = hurtboxes_n;
}


Frame::~Frame()
{
}
