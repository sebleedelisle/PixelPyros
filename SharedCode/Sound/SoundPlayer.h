//
//  SoundPlayer.h
//  ParticlePlay5
//
//  Created by Seb Lee-Delisle on 19/08/2012.
//
//

#pragma once
#include "ofMain.h"
#include "Sound.h"

class SoundPlayer {
	
	public :
	
	static SoundPlayer* soundPlayer;
	static SoundPlayer* instance();
	
	SoundPlayer();
	
	bool addSound(string filename, string reference, float vol = 1, float speed = 1, float speedVar = 0, string fileType = "aif", float retriggerMin = 0.02);
	
	bool playSound(string soundname, float volume, float pan);
	
	map <string, Sound> sounds;
	string defaultPath;
	
	float globalVolume; 
	
	
};

