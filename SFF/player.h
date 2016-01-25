class Player{
    void executeMove();
    void checkDead();
    boolean isMoveValid(); 
    
    
    Character character;
    int health;
    int meter;
    int roundWins;
    String state;
    Move currentMove;
	int currentMoveFrame;
    int inputBuffer;
    boolean canCancel;
    // currentSprite;
    int currentFrame;
}
