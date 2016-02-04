#include "Character.h"



Character::Character() {

}

Character::Character(vector <Move> moveList_n, string spritesheet_url)
{
	moveList = moveList_n;
	spritesheet = spritesheet_url;
	currentMove = 0;
	currentMoveFrame = 0;
}



Character::~Character()
{
}
