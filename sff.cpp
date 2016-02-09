
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <list>

#include "input.h"


using namespace std;
using noteTable = map<vector<int>, int>;

/*unsigned long hashing_func(vector<int> key) {
	cout << "Hashing called";
	unsigned int hash = 0;
	for (unsigned int n : notes)
		sum_of_elems += (2 << n);
	return hash;
}*/
/*noteTable table(hashing_func) = {
	{ { 60,64,67 }, C_MAJOR }

};*/

struct chord {
	int notearray[4];
	
	void insert(int note) {
		for (int n : notearray) {

		}
	}
};

int simultaneous = 0;
list<int> notes;


int CALLBACK MidiInProc(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2) {
	if (wMsg == MIM_DATA) {
		// Get last 3 bytes of the DWORD containing midi data. Byte 1 is never used, byte 2 is the note,
		// byte 3 is the velocity, and byte 4 is the status.
		int byte2 = (dwParam1 >> 16) & 0xFF;
		int byte3 = (dwParam1 >> 8) & 0xFF;
		int byte4 = dwParam1 & 0xFF;
		if (byte4 == NOTE_ON) {
			simultaneous = 1;
			if (byte2 != 0 && simultaneous > 0) {
				notes.push_back(byte3);
			}
		}
		else if ((simultaneous > 0) && (byte4 == 248 || byte4 == 254)) {
			simultaneous--;
		}
		else if (simultaneous == 0) {
			int sum_of_elems = 1;
			if (!notes.empty()) {
				notes.sort();
				for (auto i = notes.begin(); i != notes.end(); ++i)
					cout << *i << ' ';
				cout << endl;
				for (int n : notes)
					sum_of_elems += (n*n);
				cout << "sum: " << sum_of_elems << endl;
				//cout << table.count(notes);
				notes.clear();
			}
		}
		//if (!notes.empty()) {
		//	for (auto i = notes.begin(); i != notes.end(); ++i)
		//		cout << *i << ' ';
		//	cout << endl;
		//}
	}
	else if (wMsg != MM_MIM_OPEN && wMsg != MM_MIM_CLOSE) {
		cerr << "Unexpected MIDI message recieved: " << wMsg << endl;
		exit(EXIT_FAILURE);
	}
	return 0;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	// Get a console for debugging with cout
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	MIDIINCAPS device_capabilities;
	cout << midiInGetNumDevs() << endl;
	for (int dev_num = 0; dev_num < midiInGetNumDevs(); dev_num++) {
		midiInGetDevCaps(dev_num, &device_capabilities, sizeof device_capabilities);
		cout << device_capabilities.wMid;
	}

	int numDevs = midiInGetNumDevs();

	HMIDIIN midi_device_handle;
	midiInOpen(&midi_device_handle, 0, (DWORD_PTR)(void*)MidiInProc, 0, CALLBACK_FUNCTION);
	midiInStart(midi_device_handle);





	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}