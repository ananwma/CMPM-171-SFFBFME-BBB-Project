#include "stdafx.h"
#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <Winuser.h>
#include <assert.h>

#include "input.h"

using namespace std;

void InputHandler::parseMidiData(HMIDIIN hMidiIn, DWORD dwParam1, DWORD dwParam2, DWORD dwInstance) {
	// Get last 3 bytes of the DWORD containing midi data. Byte 1 is never used, byte 2 is the note,
	// byte 3 is the velocity, and byte 4 is the status.
	int byte2 = (dwParam1 >> 16) & 0xFF;
	int byte3 = (dwParam1 >> 8) & 0xFF;
	int byte4 = dwParam1 & 0xFF;
	midiOutShortMsg(midout, dwParam1);
	if (byte4 == NOTE_ON) {
		if (byte2 != 0) {
			//notes.push_back(byte3);
			//send as int
			sendKeysDown(byte3, (int)hMidiIn);
		}
		else {
			sendKeysUp(byte3, (int)hMidiIn);
			//if (!notes.empty())
				//notes.pop_back();
		}
	} 
	else if (byte4 == NOTE_OFF) {
		sendKeysUp(byte3, (int)hMidiIn);
		//if (!notes.empty()) 
			//notes.pop_back();
	}

	/*if (!notes.empty()) {
		for (auto i : notes) {
			cout << i;
		}
		cout << endl;*/
	//	onNoteDown(notes);
	//}
}

void InputHandler::MidiInProc(HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwInstance, DWORD dwParam1, DWORD dwParam2) {
	
	// Get instance 
	InputHandler *pThis = reinterpret_cast<InputHandler *>(dwInstance);

	//list<int> notes;
	if (wMsg == MIM_DATA) {
		// Call non-static member function
		pThis->parseMidiData(hMidiIn, dwParam1, dwParam2, dwInstance);
	}
	else if (wMsg != MM_MIM_OPEN && wMsg != MM_MIM_CLOSE) {
		cerr << "Unexpected MIDI message received: " << wMsg << endl;
		exit(EXIT_FAILURE);
	}
}

// Make return value useful later
int InputHandler::prepareDevices() {
	for (int i = 0; i < midiInGetNumDevs(); i++) {
		HMIDIIN device;
		midiInOpen(&device, i, (DWORD_PTR)MidiInProc, reinterpret_cast<DWORD_PTR>(this), CALLBACK_FUNCTION);
		midiInStart(device);
		device_map[(int)device] = i;
	}

	for (int i = 0; i < midiOutGetNumDevs(); i++) {
		MIDIOUTCAPS caps;
		midiOutGetDevCaps(i, &caps, sizeof caps);
		if (caps.wMid == MM_YAMAHA)
			midiOutOpen(&midout, i, 0, 0, 0);
	}
	// Possibly move into constructor?
	return 0;
}

/* To build the midi message, leftshift volume 16 to make byte 2, and than
   OR with 0x07B0, the values for bytes 3 and 4 which designated a volume
   control message */
void InputHandler::setVolume(unsigned int vol) {
	assert(vol < 128 && "Volume value must be between 0 and 127");
	DWORD_PTR msg = vol << 16 | 0x07B0;
	midiOutShortMsg(midout, msg);
}