#pragma once
#include <vector>
#include "Game.h"

#define BASSLINE_CHANNEL 1

class Bassline {
public:

	// CTORs and DTOR
	Bassline(const Game&, std::vector<int>, int);
	~Bassline() = default;
	Bassline(const Bassline&) = delete;
	Bassline(Bassline&&) = delete;
	Bassline& operator= (const Bassline&) = delete;
	Bassline& operator= (Bassline&&) = delete;

	void playNextNote();
	void transpose(int);
	void setInstrument(int);
	void setVolume(int);
	void setBassline(vector<int>);
	void appendNotes(vector<int>);
private:
	std::vector<int> bassline;
	size_t size;
	size_t index = 0;
	int volume;

	const Game& game;
};