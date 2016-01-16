class gameState
{
public:
  virtual void Init() = 0;
  virtual void Cleanup() = 0;

  virtual void Pause() = 0;
  virtual void Resume() = 0;

  virtual void HandleEvents(gameEngine* game) = 0;
  virtual void Update(gameEngine* game) = 0;
  virtual void Draw(gameEngine* game) = 0;

  void ChangeState(gameEngine* game, gameState* state) {
    game->ChangeState(state);
  }

  protected: gameState() { }
};
