#include <windows.h>
#include <mmsystem.h>
#include <iostream>

#include "input.h"

InputHandler::InputHandler() {
	int numDevs = midiInGetNumDevs();
	if (numDevs < 1) {
		cerr << "No MIDI Device Connected";
		return;
	}
	for (int i = 0; i < numDevs; i++) {
		HMIDIIN deviceHandle;
		midiInOpen(&deviceHandle, i, (DWORD_PTR)(void*)MidiInProc, 0, CALLBACK_FUNCTION);
		// might need to push a copy of handle since its filled by reference
		deviceHandles.push(deviceHandle);
	}
}

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
				//notes.sort();
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

//void startMidi
