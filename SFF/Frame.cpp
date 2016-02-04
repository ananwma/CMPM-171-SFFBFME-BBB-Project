#include "Frame.h"




Frame::Frame() {

}
Frame::Frame(vector <sf::IntRect> hitboxes_n, vector <sf::IntRect> hurtboxes_n, vector <sf::RectangleShape> hitboxes_vn, vector <sf::RectangleShape> hurtboxes_vn)
{
	hitboxes = hitboxes_n;
	hitboxes_v = hitboxes_vn;
	hurtboxes = hurtboxes_n;
	hurtboxes_v = hurtboxes_vn;
}


Frame::~Frame()
{
}
