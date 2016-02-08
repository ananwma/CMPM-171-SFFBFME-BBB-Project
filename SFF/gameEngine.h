class gameEngine
{
public:
  void Init();
  void Cleanup();

  void ChangeState(gameState* state);
  void PushState(gameState* state);
  void PopState();

  void HandleEvents();
  void Update();
  void Draw();

  bool Running() { return m_running; }
  void Quit() { m_running = false; }

private:
  // the stack of states
  vector<gameState*> states;

  bool m_running;
};
