#include <iostream>
#include <fstream>
#include <windows.h>
#include "Midi.h"
using namespace std;

	DWORD NoteA0 = 0x00401590; //21
	DWORD NoteA0sharp = 0x00401690; //22
	DWORD NoteB0 = 0x00401790; //23
	
	DWORD NoteC1 = 0x00401890; //24
	DWORD NoteC1sharp = 0x00401990; //25
	DWORD NoteD1 = 0x00401A90; //26
	DWORD NoteD1sharp = 0x00401B90; //27
	DWORD NoteE1 = 0x00401C90; //28
	DWORD NoteF1 = 0x00401D90; //29
	DWORD NoteF1sharp = 0x00401E90; //30
	DWORD NoteG1 = 0x00401F90; //31
	DWORD NoteG1sharp = 0x00402090; //32
	DWORD NoteA1 = 0x00402190; //33
	DWORD NoteA1sharp = 0x00402290; //34
	DWORD NoteB1 = 0x00402390; //35

	DWORD NoteC2 = 0x00402490; //36
	DWORD NoteC2sharp = 0x00402590; //37
	DWORD NoteD2 = 0x00402690; //38
	DWORD NoteD2sharp = 0x00402790; //39
	DWORD NoteE2 = 0x00402890; //40
	DWORD NoteF2 = 0x00402990; //41
	DWORD NoteF2sharp = 0x00402A90; //42
	DWORD NoteG2 = 0x00402B90; //43
	DWORD NoteG2sharp = 0x00402C90; //44
	DWORD NoteA2 = 0x00402D90; //45
	DWORD NoteA2sharp = 0x00402E90; //46
	DWORD NoteB2 = 0x00402F90; //47

	DWORD NoteC3 = 0x00403090; //48
	DWORD NoteC3sharp = 0x00403190; //49
	DWORD NoteD3 = 0x00403290; //50
	DWORD NoteD3sharp = 0x00403390; //51
	DWORD NoteE3 = 0x00403490; //52
	DWORD NoteF3 = 0x00403590; //53
	DWORD NoteF3sharp = 0x00403690; //54
	DWORD NoteG3 = 0x00403790; //55
	DWORD NoteG3sharp = 0x00403890; //56
	DWORD NoteA3 = 0x00403990; //57
	DWORD NoteA3sharp = 0x00403A90; //58
	DWORD NoteB3 = 0x00403B90; //59

	//middle C
	DWORD NoteC4 = 0x00403C90; //60
	DWORD NoteC4sharp = 0x00403D90; //61
	DWORD NoteD4 = 0x00403E90; //62
	DWORD NoteD4sharp = 0x00403F90; //63
	DWORD NoteE4 = 0x00404090; //64
	DWORD NoteF4 = 0x00404190; //65
	DWORD NoteF4sharp = 0x00404290; //66
	DWORD NoteG4 = 0x00404390; //67
	DWORD NoteG4sharp = 0x00404490; //68
	DWORD NoteA4 = 0x00404590; //69
	DWORD NoteA4sharp = 0x00404690; //70
	DWORD NoteB4 = 0x00404790; //71

	DWORD NoteC5 = 0x00404890; //72
	DWORD NoteC5sharp = 0x00404990; //73
	DWORD NoteD5 = 0x00404A90; //74
	DWORD NoteD5sharp = 0x00404B90; //75
	DWORD NoteE5 = 0x00404C90; //76
	DWORD NoteF5 = 0x00404D90; //77
	DWORD NoteF5sharp = 0x00404E90; //78
	DWORD NoteG5 = 0x00404F90; //79
	DWORD NoteG5sharp = 0x00405090; //80
	DWORD NoteA5 = 0x00405190; //81
	DWORD NoteA5sharp = 0x00405290; //82
	DWORD NoteB5 = 0x00405390; //83

	DWORD NoteC6 = 0x00405490; //84
	DWORD NoteC6sharp = 0x00405590; //85
	DWORD NoteD6 = 0x00405690; //86
	DWORD NoteD6sharp = 0x00405790; //87
	DWORD NoteE6 = 0x00405890; //88
	DWORD NoteF6 = 0x00405990; //89
	DWORD NoteF6sharp = 0x00405A90; //90
	DWORD NoteG6 = 0x00405B90; //91
	DWORD NoteG6sharp = 0x00405C90; //92
	DWORD NoteA6 = 0x00405D90; //93
	DWORD NoteA6sharp = 0x00405E90; //94
	DWORD NoteB6 = 0x00405F90; //95

	DWORD NoteC7 = 0x00406090; //96
	DWORD NoteC7sharp = 0x00406190; //97
	DWORD NoteD7 = 0x00406290; //98
	DWORD NoteD7sharp = 0x00406390; //99
	DWORD NoteE7 = 0x00406490; //100
	DWORD NoteF7 = 0x00406590; //101
	DWORD NoteF7sharp = 0x00406690; //102
	DWORD NoteG7 = 0x00406790; //103
	DWORD NoteG7sharp = 0x00406890; //104
	DWORD NoteA7 = 0x00406990; //105
	DWORD NoteA7sharp = 0x00406A90; //106
	DWORD NoteB7 = 0x00406B90;//107

	DWORD NoteC8 = 0x00406C90; //108


	HMIDIOUT handle;
	unsigned int DEFAULT_DEVICE = 0;


int Midi::init()
{
        // Default MIDI Device
	loadSongs();

	if(!midiOutOpen(&handle, DEFAULT_DEVICE, 0,0, CALLBACK_NULL))
	{
	//midiOutShortMsg(handle, NoteC1);
	//Sleep(250);

	//midiOutShortMsg(handle, NoteE1);
	//Sleep(250);

	//midiOutShortMsg(handle, NoteG1);
	//Sleep(1500);

	}
	else 
	cout << "Error Opening Default MIDI Device" << endl;

return 0;
}

float countdown = 0;

void Midi::playRail(float speed,int currentRail)
{
	if(countdown <= 0)
	{
		playNextNote(speed);
		countdown = 50;
	}
	countdown-=speed*100;
}
int currentSong = 0;
int songIndex[50];
int SongMax[50];
string Songs[50][100];
void Midi::playNextNote(float speed)
{
	cout<<speed<<endl;
	if(strcmp(Songs[currentSong][songIndex[currentSong]].c_str(),"A")==0)
	{
		if(speed < .01)
		{
			midiOutShortMsg(handle, NoteA1);
		}
		else if(speed < .02)
		{
			midiOutShortMsg(handle, NoteA2);
		}
		else if(speed < .03)
		{
			midiOutShortMsg(handle, NoteA3);
		}
		else if(speed < .04)
		{
			midiOutShortMsg(handle, NoteA4);
		}
		else if(speed < .05)
		{
			midiOutShortMsg(handle, NoteA5);
		}
		else if(speed < .06)
		{
			midiOutShortMsg(handle, NoteA6);
		}
		else if(speed >= .06)
		{
			midiOutShortMsg(handle, NoteA7);
		}
	}
	else if(strcmp(Songs[currentSong][songIndex[currentSong]].c_str(),"B")==0)
	{
		if(speed < .01)
		{
			midiOutShortMsg(handle, NoteB1);
		}
		else if(speed < .02)
		{
			midiOutShortMsg(handle, NoteB2);
		}
		else if(speed < .03)
		{
			midiOutShortMsg(handle, NoteB3);
		}
		else if(speed < .04)
		{
			midiOutShortMsg(handle, NoteB4);
		}
		else if(speed < .05)
		{
			midiOutShortMsg(handle, NoteB5);
		}
		else if(speed < .06)
		{
			midiOutShortMsg(handle, NoteB6);
		}
		else if(speed >= .06)
		{
			midiOutShortMsg(handle, NoteB7);
		}
	}
	else if(strcmp(Songs[currentSong][songIndex[currentSong]].c_str(),"C")==0)
	{
		if(speed < .01)
		{
			midiOutShortMsg(handle, NoteC1);
		}
		else if(speed < .02)
		{
			midiOutShortMsg(handle, NoteC2);
		}
		else if(speed < .03)
		{
			midiOutShortMsg(handle, NoteC3);
		}
		else if(speed < .04)
		{
			midiOutShortMsg(handle, NoteC4);
		}
		else if(speed < .05)
		{
			midiOutShortMsg(handle, NoteC5);
		}
		else if(speed < .06)
		{
			midiOutShortMsg(handle, NoteC6);
		}
		else if(speed >= .06)
		{
			midiOutShortMsg(handle, NoteC7);
		}
	}
	else if(strcmp(Songs[currentSong][songIndex[currentSong]].c_str(),"D")==0)
	{
		if(speed < .01)
		{
			midiOutShortMsg(handle, NoteD1);
		}
		else if(speed < .02)
		{
			midiOutShortMsg(handle, NoteD2);
		}
		else if(speed < .03)
		{
			midiOutShortMsg(handle, NoteD3);
		}
		else if(speed < .04)
		{
			midiOutShortMsg(handle, NoteD4);
		}
		else if(speed < .05)
		{
			midiOutShortMsg(handle, NoteD5);
		}
		else if(speed < .06)
		{
			midiOutShortMsg(handle, NoteD6);
		}
		else if(speed >= .06)
		{
			midiOutShortMsg(handle, NoteD7);
		}
	}
	else if(strcmp(Songs[currentSong][songIndex[currentSong]].c_str(),"E")==0)
	{
		if(speed < .01)
		{
			midiOutShortMsg(handle, NoteE1);
		}
		else if(speed < .02)
		{
			midiOutShortMsg(handle, NoteE2);
		}
		else if(speed < .03)
		{
			midiOutShortMsg(handle, NoteE3);
		}
		else if(speed < .04)
		{
			midiOutShortMsg(handle, NoteE4);
		}
		else if(speed < .05)
		{
			midiOutShortMsg(handle, NoteE5);
		}
		else if(speed < .06)
		{
			midiOutShortMsg(handle, NoteE6);
		}
		else if(speed >= .06)
		{
			midiOutShortMsg(handle, NoteE7);
		}
	}
	else if(strcmp(Songs[currentSong][songIndex[currentSong]].c_str(),"F")==0)
	{
		if(speed < .01)
		{
			midiOutShortMsg(handle, NoteF1);
		}
		else if(speed < .02)
		{
			midiOutShortMsg(handle, NoteF2);
		}
		else if(speed < .03)
		{
			midiOutShortMsg(handle, NoteF3);
		}
		else if(speed < .04)
		{
			midiOutShortMsg(handle, NoteF4);
		}
		else if(speed < .05)
		{
			midiOutShortMsg(handle, NoteF5);
		}
		else if(speed < .06)
		{
			midiOutShortMsg(handle, NoteF6);
		}
		else if(speed >= .06)
		{
			midiOutShortMsg(handle, NoteF7);
		}
	}
	else if(strcmp(Songs[currentSong][songIndex[currentSong]].c_str(),"G")==0)
	{
		if(speed < .01)
		{
			midiOutShortMsg(handle, NoteG1);
		}
		else if(speed < .02)
		{
			midiOutShortMsg(handle, NoteG2);
		}
		else if(speed < .03)
		{
			midiOutShortMsg(handle, NoteG3);
		}
		else if(speed < .04)
		{
			midiOutShortMsg(handle, NoteG4);
		}
		else if(speed < .05)
		{
			midiOutShortMsg(handle, NoteG5);
		}
		else if(speed < .06)
		{
			midiOutShortMsg(handle, NoteG6);
		}
		else if(speed >= .06)
		{
			midiOutShortMsg(handle, NoteG7);
		}
	}
	songIndex[currentSong] = songIndex[currentSong]+1;
	if(songIndex[currentSong] > SongMax[currentSong])
	{
		songIndex[currentSong] = 0;
	}
}
void Midi::loadSongs()
{
	ifstream song0;
	song0.open("Data/Rail0Song.txt");
	int count = 0;
	while(song0.eof()==false)
	{
		char temp[100];
		song0.getline(temp,100);
		Songs[currentSong][count++] = string(temp);
		SongMax[currentSong] = 42;
	}
	song0.close();

}