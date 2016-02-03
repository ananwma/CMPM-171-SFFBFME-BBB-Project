#pragma once
#include <memory>
#include <list>

#include "input.h";

class GameStateManager;
class GameState;

using state_ptr = std::shared_ptr<GameState>;


[event_receiver(native)]
class GameState {
public:
	//virtual ~GameState();
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void recieveKeysDown(std::list<int> &notes) = 0;

	//Need seperate function because you cannot unhook events within the functions which receive events
	virtual void unhookEvent() = 0;
};
