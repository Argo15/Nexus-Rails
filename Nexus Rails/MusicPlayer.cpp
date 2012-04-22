#include <iostream>
#include <fstream>
#include <windows.h>
#include "MusicPlayer.h"
#include "audiere.h"
using namespace audiere;
using namespace std;

AudioDevicePtr* device;
OutputStreamPtr* sound;
int MusicPlayer::init()
{	
	cout<<"here"<<endl;
	string fileName="Data/awoefuldog.wav";
   device = new AudioDevicePtr(OpenDevice());
   sound = new OutputStreamPtr(OpenSound(*device,fileName.c_str(), false));
   (*sound)->play(); (*sound)->setRepeat(true); (*sound)->setVolume(1.0f);
   return 0;
}