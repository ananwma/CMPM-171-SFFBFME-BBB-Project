

#include <list>
#include <vector>
#include <windows.h>
#include <mmsystem.h>

// Some midi data signals
#define NOTE_ON 144
#define NOTE_OFF 128

#define A_NATURAL 0
#define A_SHARP 1
#define B_NATURAL 2
#define C_NATURAL 3
#define C_SHARP 4
#define D_NATURAL 5
#define D_SHARP 6
#define E_NATURAL 7
#define F_NATURAL 8
#define F_SHARP 9
#define G_NATURAL 10
#define G_SHARP 11

#define A_MAJOR 12
#define A_MAJOR_6 13
#define A_MAJOR_64 14
#define A_MAJOR_7 15
#define A_MINOR 16
#define A_MINOR_6 17
#define A_MINOR_64 18
#define A_MINOR_7 19
#define AS_MAJOR 20
#define AS_MAJOR_6 21
#define AS_MAJOR_64 22
#define AS_MAJOR_7 23
#define AS_MINOR 24
#define AS_MINOR_6 25
#define AS_MINOR_64 26
#define AS_MINOR_7 27
#define B_MAJOR 28
#define B_MAJOR_6 29
#define B_MAJOR_64 30
#define B_MAJOR_7 31
#define B_MINOR 32
#define B_MINOR_6 33
#define B_MINOR_64 34
#define B_MINOR_7 35
#define C_MAJOR 36
#define C_MAJOR_6 37
#define C_MAJOR_64 38
#define C_MAJOR_7 39
#define C_MINOR 40
#define C_MINOR_6 41
#define C_MINOR_64 42
#define C_MINOR_7 43
#define CS_MAJOR 44
#define CS_MAJOR_6 45
#define CS_MAJOR_64 46
#define CS_MAJOR_7 47
#define CS_MINOR 48
#define CS_MINOR_6 49
#define CS_MINOR_64 50
#define CS_MINOR_7 51
#define D_MAJOR 52
#define D_MAJOR_6 53
#define D_MAJOR_64 54
#define D_MAJOR_7 55
#define D_MINOR 56
#define D_MINOR_6 57
#define D_MINOR_64 58
#define D_MINOR_7 59
#define DS_MAJOR 60
#define DS_MAJOR_6 61
#define DS_MAJOR_64 62
#define DS_MAJOR_7 63
#define DS_MINOR 64
#define DS_MINOR_6 65
#define DS_MINOR_64 66
#define DS_MINOR_7 67
#define E_MAJOR 68
#define E_MAJOR_6 69
#define E_MAJOR_64 70
#define E_MAJOR_7 71
#define E_MINOR 72
#define E_MINOR_6 73
#define E_MINOR_64 74
#define E_MINOR_7 75
#define F_MAJOR 76
#define F_MAJOR_6 77
#define F_MAJOR_64 78
#define F_MAJOR_7 79
#define F_MINOR 80
#define F_MINOR_6 81
#define F_MINOR_64 82
#define F_MINOR_7 83
#define FS_MAJOR 84
#define FS_MAJOR_6 85
#define FS_MAJOR_64 86
#define FS_MAJOR_7 87
#define FS_MINOR 88
#define FS_MINOR_6 89
#define FS_MINOR_64 90
#define FS_MINOR_7 91
#define G_MAJOR 92
#define G_MAJOR_6 93
#define G_MAJOR_64 94
#define G_MAJOR_7 95
#define G_MINOR 96
#define G_MINOR_6 97
#define G_MINOR_64 98
#define G_MINOR_7 99
#define GS_MAJOR 100
#define GS_MAJOR_6 101
#define GS_MAJOR_64 102
#define GS_MAJOR_7 103
#define GS_MINOR 104
#define GS_MINOR_6 105
#define GS_MINOR_64 106
#define GS_MINOR_7 107
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

	// Event functions, has no implementation
	__event void sendKeysDown(int, int);
	__event void sendKeysUp(int, int);
private:
	std::vector<HMIDIIN> devices;
	std::list<int> notes;
	void parseMidiData(HMIDIIN hMidiIn, DWORD dwParam1, DWORD dwParam2, DWORD dwInstance);
	static void CALLBACK MidiInProc(HMIDIIN, UINT, DWORD_PTR, DWORD, DWORD);
};