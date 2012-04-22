#ifndef MIDI_H
#define MIDI_H
using namespace std;

class Midi
{
public:
	int init();
	void playRail(float,int);
	void playNextNote(float);
private:
	void loadSongs();
};

#endif