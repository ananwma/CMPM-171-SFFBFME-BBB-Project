#pragma once
#include "Frame.h"


using namespace std;

class Move
{
public:
	Move() = default;
	Move(vector <Frame>);
	vector <Frame> frames;
	string hitrange;
	vector <Move> cancels_into;
	int spriteRow; //for image source
	string state;
	~Move();
};

