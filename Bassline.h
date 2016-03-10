#pragma once
#include <vector>
#include "Game.h"

#define BASSLINE_CHANNEL 1
#define C1 36
#define D1 38
#define E1 40
#define F1 41
#define G1 43
#define A1 45
#define B1 47
#define C2 48
#define D2 50
#define E2 52
#define F2 53
#define G2 55
#define A2 57
#define B2 59

enum Key {
	KEY_CM,
	KEY_CSM,
	KEY_DM,
	KEY_DSM,
	KEY_EM,
	KEY_FM,
	KEY_FSM,
	KEY_GM,
	KEY_GSM,
	KEY_AM,
	KEY_ASM,
	KEY_BM,
	KEY_Cm,
	KEY_CSm,
	KEY_Dm,
	KEY_DSm,
	KEY_Em,
	KEY_Fm,
	KEY_FSm,
	KEY_Gm,
	KEY_GSm,
	KEY_Am,
	KEY_ASm,
	KEY_Bm,
};

class Bassline {
public:
	// CTORs and DTOR
	Bassline(const Game&, std::vector<int>, Key, int);
	~Bassline() = default;
	Bassline(const Bassline&) = delete;
	Bassline(Bassline&&) = delete;
	Bassline& operator= (const Bassline&) = delete;
	Bassline& operator= (Bassline&&) = delete;

	void playNextNote();
	void transpose(int);
	void modulateTo(Key);
	void setInstrument(int);
	void setVolume(int);
	void setBassline(vector<int>);
	void appendNotes(vector<int>);
	int getCurrentNote();
private:
	std::vector<int> bassline;
	size_t size;
	size_t index = 0;
	int volume;
	Key key;

	const Game& game;
};