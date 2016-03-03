#include <vector>
#include <map>
#include <windows.h>
#include <mmsystem.h>
#include <mmreg.h>

// Some midi data signals
#define NOTE_ON 144
#define NOTE_OFF 128


#define C_NATURAL 0x1
#define C_SHARP 0x2
#define D_NATURAL 0x4
#define D_SHARP 0x8
#define E_NATURAL 0x10
#define F_NATURAL 0x20
#define F_SHARP 0x40
#define G_NATURAL 0x80
#define G_SHARP 0x100
#define A_NATURAL 0x200
#define A_SHARP 0x400
#define B_NATURAL 0x800

#define C_MAJOR 0x91
#define C_MAJOR_6 0x1090
#define C_MAJOR_64 0x11080
#define C_MAJOR_7 0x891
#define C_MINOR 0x89
#define C_MINOR_6 0x1088
#define C_MINOR_64 0x9080
#define C_MINOR_7 0x489
#define CS_MAJOR 0x
#define CS_MAJOR_6 0x
#define CS_MAJOR_64 0x
#define CS_MAJOR_7 0x
#define CS_MINOR 0x
#define CS_MINOR_6 0x
#define CS_MINOR_64 0x
#define CS_MINOR_7 0x
#define D_MAJOR 0x
#define D_MAJOR_6 0x
#define D_MAJOR_64 0x
#define D_MAJOR_7 0x
#define D_MINOR 0x224
#define D_MINOR_6 0x
#define D_MINOR_64 0x
#define D_MINOR_7 0x
#define DS_MAJOR 0x
#define DS_MAJOR_6 0x
#define DS_MAJOR_64 0x
#define DS_MAJOR_7 0x
#define DS_MINOR 0x
#define DS_MINOR_6 0x
#define DS_MINOR_64 0x
#define DS_MINOR_7 0x
#define E_MAJOR 0x
#define E_MAJOR_6 0x
#define E_MAJOR_64 0x
#define E_MAJOR_7 0x
#define E_MINOR 0x890
#define E_MINOR_6 0x
#define E_MINOR_64 0x
#define E_MINOR_7 0x
#define F_MAJOR 0x1220
#define F_MAJOR_6 0x
#define F_MAJOR_64 0x
#define F_MAJOR_7 0x
#define F_MINOR 0x
#define F_MINOR_6 0x
#define F_MINOR_64 0x
#define F_MINOR_7 0x
#define FS_MAJOR 0x
#define FS_MAJOR_6 0x
#define FS_MAJOR_64 0x
#define FS_MAJOR_7 0x
#define FS_MINOR 0x
#define FS_MINOR_6 0x
#define FS_MINOR_64 0x
#define FS_MINOR_7 0x
#define G_MAJOR 0x4880
#define G_MAJOR_6 0x84800
#define G_MAJOR_64 0x884
#define G_MAJOR_7 0x24880
#define G_MINOR 0x
#define G_MINOR_6 0x
#define G_MINOR_64 0x
#define G_MINOR_7 0x
#define GS_MAJOR 0x
#define GS_MAJOR_6 0x
#define GS_MAJOR_64 0x
#define GS_MAJOR_7 0x
#define GS_MINOR 0x
#define GS_MINOR_6 0x
#define GS_MINOR_64 0x
#define GS_MINOR_7 0x
#define A_MAJOR 0x
#define A_MAJOR_6 0x
#define A_MAJOR_64 0x
#define A_MAJOR_7 0x
#define A_MINOR 0x11200
#define A_MINOR_6 0x
#define A_MINOR_64 0x
#define A_MINOR_7 0x
#define AS_MAJOR 0x
#define AS_MAJOR_6 0x
#define AS_MAJOR_64 0x
#define AS_MAJOR_7 0x
#define AS_MINOR 0x
#define AS_MINOR_6 0x
#define AS_MINOR_64 0x
#define AS_MINOR_7 0x
#define B_MAJOR 0x
#define B_MAJOR_6 0x
#define B_MAJOR_64 0x
#define B_MAJOR_7 0x 
#define B_MINOR 0x
#define B_MINOR_6 0x
#define B_MINOR_64 0x
#define B_MAJOR_DIM 0x24800
#define B_MINOR_7 0x 

#pragma once
[event_source(native)]
class InputHandler
{
public: 
	// Constructors etc.
	InputHandler() = default;
	InputHandler(const InputHandler&) = delete;
	InputHandler(InputHandler&&) = delete;
	InputHandler& operator= (const InputHandler&) = default;
	InputHandler& operator= (InputHandler&&) = default;
	~InputHandler() = default;

	// Opens device
	int prepareDevices();

	// Methods for midi out operations
	void setVolume(unsigned int);
	void playNote(unsigned int);

	// Event functions, has no implementation
	__event void sendKeysDown(int, int);
	__event void sendKeysUp(int, int);
private:
	// Map of handles to device ID's
	std::map<int, int> device_map;
	//std::vector<int> notes;
	void parseMidiData(HMIDIIN hMidiIn, DWORD dwParam1, DWORD dwParam2, DWORD dwInstance);
	HMIDIOUT midout;
	static void CALLBACK MidiInProc(HMIDIIN, UINT, DWORD_PTR, DWORD, DWORD);
};