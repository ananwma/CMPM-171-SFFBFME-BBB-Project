int main(int argc, const char* argv[])
{
  gameEngine game;

  // initialize the engine
  game.Init( "Engine Test v1.0" );

  // load the intro
  game.ChangeState(introState::Instance());
  //initialize players
  //sf::Texture pTexture;
  //sf::Sprite player1Image;
  //case statements based on character choice?
  //repeat for player2
  

  // main loop
  while (game.Running())
  {
    game.HandleEvents();
	//checkplayer1input
	//repeat for player2
    game.Update();
	//find move based on input read, if state allows it and is different from currentMove:
		//set player1.currentMove, set player1.currentMoveFrame to 0
		//else player1.currentMoveFrame++
		//if player1.currentMoveFrame > player1.currentMove.frames.length:
			//set player1.currentMove to idle 
    //player1Image.setTextureRect(sf::IntRect(player1.currentMoveFrame * spriteWidth, player1.currentMove.spriteRow * spriteHeight, spriteWidth, SpriteHeight));

	//repeat for player2
	//testCollision
    game.Draw();
  }

  // cleanup the engine
  game.Cleanup();
  return 0;
}
