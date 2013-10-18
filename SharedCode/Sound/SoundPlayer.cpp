//
//  SoundPlayer.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 09/09/2013.
//
//

#include "SoundPlayer.h"

SoundPlayer* SoundPlayer :: soundPlayer = NULL;
SoundPlayer* SoundPlayer::instance() {
	
	if (soundPlayer == NULL) {
		soundPlayer = new SoundPlayer();
	}
	return soundPlayer;
	
}

SoundPlayer::SoundPlayer(){
	globalVolume.set("sfx volume", 0.7,0,1);
	
	screenRect.set(0,0,ofGetWidth(), ofGetHeight()); 
}

void SoundPlayer::setScreenRect(ofRectangle rect) {
	screenRect.set(rect);
	
}

bool SoundPlayer:: addSound(string filename, string reference, float vol, float speed, float speedVar, string fileType, float retriggerMin){
	
	sounds[reference] = Sound();// = (Sound);
	Sound& newsound = sounds[reference];
	newsound.masterVolume = vol;
	newsound.speed = speed;
	newsound.speedVariation = speedVar;
	newsound.minRetriggerTime = retriggerMin;
	
	
	if(!newsound.addSound(defaultPath, filename, vol,fileType)) {
		sounds.erase(reference);
		
	};
	return true; 
}

bool SoundPlayer::playSound(string soundname, float volume = 1, float pan = 0){
	
	if(sounds.find(soundname) == sounds.end()) return false;
	sounds[soundname].play(volume * globalVolume, pan);
	return true; 
}

bool SoundPlayer::playSoundPanned(string soundname, float volume, ofVec3f pos){
	
	return playSound(soundname, volume, ofMap(pos.x, screenRect.getLeft(), screenRect.getRight(), -1,1));

}
