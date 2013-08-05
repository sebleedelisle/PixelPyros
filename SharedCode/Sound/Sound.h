//
//  Sound.h
//  ParticlePlay5
//
//  Created by Seb Lee-Delisle on 19/08/2012.
//
//


#include "ofMain.h"

class Sound {
	
	public :
	
	Sound() {
		
		masterVolume = 1;
		currentSoundIndex = 0;
		lastPlayedTime = 0;
		minRetriggerTime = 0.02;
		speedVariation = 0.2;
		speed = 0.8;
		
	}
	
	
	bool addSound(string path, string filename, float vol = 1, string type ="aif") {
		cout <<  "adding sound " << path+filename << endl;
		
		ofDirectory dir(path);
		if(!dir.exists()) {
			ofLog(OF_LOG_ERROR, "Sound::addSound - directory "+path+" not found");
			return false;
		}
		
		ofFile file;
		
		if(file.doesFileExist(path+filename+"."+type)){
		
			sounds.push_back(ofSoundPlayer());
			ofSoundPlayer& newsound = sounds.back();
			newsound.loadSound(path+filename+"."+type);
			newsound.setMultiPlay(true);
		} else {
			int filenum = 1;
			
			
			while(file.doesFileExist(path+filename+"."+ofToString(filenum)+"."+type)){
				
				addSound(path, filename+"."+ofToString(filenum), vol, type);
				filenum++;
				
			}
			
			
		}
		
		int numsounds = sounds.size();
		
		// if we only have one sound then make a few for proper
		// polyphony.
//		if(numsounds==1){
//			
//			for(int i = 0; i<12; i++) {
//				sounds.push_back(sounds[0]);
//			}
//		}
		
		return true; 
		
	}
	
	bool play(float vol = 1, float pan = 0) {
		
		if(ofGetElapsedTimef()-lastPlayedTime < minRetriggerTime) return false;
		
		
		if(currentSoundIndex>=sounds.size()) currentSoundIndex = 0;
		ofSoundPlayer& sound = sounds[currentSoundIndex];
		
		sound.setVolume(vol*masterVolume);
		sound.setPan(pan);
		sound.setSpeed(ofRandom(speed-speedVariation, speed+speedVariation));
		sound.play();
		
		lastPlayedTime = ofGetElapsedTimef();
		//cout << "playing sound "<< currentSoundIndex << endl;
		currentSoundIndex++;
		return true;
		
	}
	
	
	
	
	
	
	
	//string soundName;
	
	float masterVolume ;
	vector <ofSoundPlayer> sounds;
	int currentSoundIndex;
	float lastPlayedTime;
	float minRetriggerTime;
	float speedVariation;
	float speed; 
	
	
};
