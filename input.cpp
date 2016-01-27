#include "stdafx.h"
#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <Winuser.h>

#include "input.h"

using namespace std;

int InputHandler::nextFreePort = 0;

InputHandler::InputHandler() {
	/*int numDevs = midiInGetNumDevs();
	if (numDevs < 1) {
		cerr << "No MIDI Device Connected";
		return;
	}
	for (int i = 0; i < numDevs; i++) {
		HMIDIIN deviceHandle;
		midiInOpen(&deviceHandle, i, (DWORD_PTR)(void*)MidiInProc, 0, CALLBACK_FUNCTION);
		// might need to push a copy of handle since its filled by reference
		deviceHandles.push_back(deviceHandle);
	}
	cout << "test";
	for (auto n : deviceHandles)
		n.midiInStart();*/
}

void InputHandler::parseMidiData(DWORD dwParam1, DWORD dwParam2, DWORD dwInstance) {
	// Get last 3 bytes of the DWORD containing midi data. Byte 1 is never used, byte 2 is the note,
	// byte 3 is the velocity, and byte 4 is the status.
	int byte2 = (dwParam1 >> 16) & 0xFF;
	int byte3 = (dwParam1 >> 8) & 0xFF;
	int byte4 = dwParam1 & 0xFF;
	if (byte4 == NOTE_ON) {
		if (byte2 != 0) {
			notes.push_back(byte3);
			onNoteDown(notes);
		}
		else
			notes.pop_back();
	} 
	else if (byte4 == NOTE_OFF) {
		notes.pop_back();
	}

	if (!notes.empty()) {
	//	onNoteDown(notes);
	}
}


// Make return value chord/note in future
// Make return raw data and process in seperate functions

void InputHandler::MidiInProc(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2) {
	
	// Get context
	InputHandler *pThis = reinterpret_cast<InputHandler *>(dwInstance);

	list<int> notes;
	if (wMsg == MIM_DATA) {
		// Call non-static member function
		pThis->parseMidiData(dwParam1, dwParam2, dwInstance);
	}
	else if (wMsg != MM_MIM_OPEN && wMsg != MM_MIM_CLOSE) {
		cerr << "Unexpected MIDI message recieved: " << wMsg << endl;
		exit(EXIT_FAILURE);
	}
}

// Make return value useful later
int InputHandler::prepareDevice() {
	// Possibly move into constructor?
	midiInOpen(&deviceHandle, nextFreePort, (DWORD_PTR)MidiInProc, reinterpret_cast<DWORD_PTR>(this), CALLBACK_FUNCTION);
	nextFreePort++;
	midiInStart(deviceHandle);
	//simultaneous = 0;
	return 0;
}


