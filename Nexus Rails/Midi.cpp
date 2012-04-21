// MIDI DEMO / EXPERIMENTAL PROGRAM
// OS - Windows 98
// Compiler - Microsoft Visual C++
//   Special Settings Project->Settings->Object/Library Modules = WINMM.LIB
// This Program uses "low level" MIDI functions to make sound
// Doug Watson
// 5/27/03

#include <iostream>
#include <windows.h>
using namespace std;

int init()
{
	HMIDIOUT handle;
	unsigned int DEFAULT_DEVICE = 0;         // Default MIDI Device
	DWORD NoteC = 0x00403c90;
	DWORD NoteE = 0x00404090;
	DWORD NoteG = 0x00404390;

	if(!midiOutOpen(&handle, DEFAULT_DEVICE, 0,0, CALLBACK_NULL))
	{
	midiOutShortMsg(handle, NoteC);
	Sleep(250);

	midiOutShortMsg(handle, NoteE);
	Sleep(250);

	midiOutShortMsg(handle, NoteG);
	Sleep(1500);

	}
	else 
	cout << "Error Opening Default MIDI Device" << endl;

return 0;
}