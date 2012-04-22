#ifndef MIDI_H
#define MIDI_H
using namespace std;

class Midi
{
public:
	int init();
	void playRail(float,int);
	void playNextNote(float);
	void die();
private:
	void loadSongs();
};

#endif