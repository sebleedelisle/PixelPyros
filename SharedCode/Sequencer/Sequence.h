//
//  Sequence.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 13/09/2013.
//
//
#pragma once
#include "ofMain.h"
#include "SceneManager.h"

#include "SequenceCommand.h"

class Sequence {
	
	public:

	Sequence(string sequencename);
	
	void setup(string scenename, string musicfile); 
	
	void start();
	void stop();
	void update(SceneManager& sm); 
	
	bool togglePause();
	void goToTime(float time);
	void setSpeed(float speed);
	void processCommand(SequenceCommand command, SceneManager& sm);
	
	SequenceCommand addCommand(int time, SequenceCommandType type, int arg);
	
	
	vector <SequenceCommand> commands;
	
	string name;
	string sceneName;
	string musicFile;
	float lastUpdate; 
	
	ofSoundPlayer music;
	
		
	bool playing; 
	
};