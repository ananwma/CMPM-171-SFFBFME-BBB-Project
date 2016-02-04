#include "Character.h"
#include "Player.h"



Player::Player(Character currentCharacter_n, int start_x, int start_y)
{
	currentCharacter = currentCharacter_n;
	if (!pTexture.loadFromFile(currentCharacter.spritesheet))
		std::cout << "Error could not load player image" << std::endl;
	pImage.setTexture(pTexture);
	health = 100;
	meter = 0;
	roundWins = 0;
	canCancel = false;
	//currentMoveFrame = 0;
	x = start_x;
	y = start_y;

}


Player::~Player()
{
}
