#include "Bassline.h"
#include "input.h"

Bassline::Bassline(const Game &_game, std::vector<int> _bassline, Key _key, int _volume) : game(_game), bassline(_bassline), key(_key), volume(_volume) {
	size = bassline.size();
}

void Bassline::playNextNote() {
	// Silence previous note
	game.inputHandler->playNote(bassline.at((index + size) % size), 0, BASSLINE_CHANNEL);
	// Play current note
	game.inputHandler->playNote(bassline.at(index), volume, BASSLINE_CHANNEL);
	// Increase index and wrap around if at end
	++index %= size;
}

void Bassline::transpose(int halfsteps) {
	for (int &i : bassline)
		i += halfsteps;
}

// Minor keys dont work yet
void Bassline::modulateTo(Key newKey) {
	int halfsteps = newKey - key;
	key = newKey;
	for (int &i : bassline)
		i += halfsteps;
}

void Bassline::setInstrument(int instrument) {
	game.inputHandler->setInstrument(instrument, BASSLINE_CHANNEL);
}

void Bassline::setVolume(int volume) {
	this->volume = volume;
}

void Bassline::setBassline(vector<int> newBassline) {
	bassline = newBassline;
	size = newBassline.size();
	index = 0;
}

void Bassline::appendNotes(vector<int> append) {
	vector<int> tmp;
	tmp.reserve(bassline.size() + append.size()); 
	tmp.insert(tmp.end(), bassline.begin(), bassline.end());
	tmp.insert(tmp.end(), append.begin(), append.end());
	bassline = std::move(tmp);
	size = bassline.size();
}

int Bassline::getCurrentNote() {
	return bassline.at((index-1) % size);
}

