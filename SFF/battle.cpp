int main(int argc, const char* argv[])
{
  gameEngine game;

  // initialize the engine
  game.Init( "Engine Test v1.0" );

  // load the intro
  game.ChangeState(introState::Instance());

  // main loop
  while (game.Running())
  {
    game.HandleEvents();
    game.Update();
    game.Draw();
  }

  // cleanup the engine
  game.Cleanup();
  return 0;
}