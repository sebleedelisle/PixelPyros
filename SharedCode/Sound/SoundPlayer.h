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
	
	SoundPlayer(){
		globalVolume = 1; 
	};
	
	bool addSound(string filename, string reference, float vol = 1, float speed = 1, float speedVar = 0, string fileType = "aif", float retriggerMin = 0.02){
		
		sounds[reference] = Sound();// = (Sound);
		Sound& newsound = sounds[reference];
		newsound.masterVolume = vol;
		newsound.speed = speed;
		newsound.speedVariation = speedVar;
		newsound.minRetriggerTime = retriggerMin;
		
		
		if(!newsound.addSound(defaultPath, filename, vol,fileType)) {
			sounds.erase(reference); 
			
		};
		
	};
	
	bool playSound(string soundname, float volume = 1, float pan = 0){
		
		if(sounds.find(soundname) == sounds.end()) return false;
		sounds[soundname].play(volume * globalVolume, pan);
	}

	
	map <string, Sound> sounds;
	string defaultPath;
	
	float globalVolume; 
	
	
};
