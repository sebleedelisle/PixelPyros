//
//  Scene.h
//  SceneCalibration
//
//  Created by Seb Lee-Delisle on 02/08/2012.
//  Copyright (c) 2012 seb.ly. All rights reserved.
//

#pragma once 


#include "constants.h"
#include "TriggerPattern.h"
#include "TriggerManager.h"
#include "SequenceCommand.h"


class Scene { 


	public : 
	
	Scene(string scenename);
	
	void loadMusicFile(string musicfile);
	
	virtual void start();
	virtual void stop();
	
	virtual bool update(float deltaTime); 
	virtual bool draw();
   
	virtual bool changeTriggerPattern(int num);
	
	void addTriggerPattern(TriggerPattern& pattern);
	void addTriggerPattern(TriggerPattern& pattern, string label);
	
	TriggerPattern getCurrentTriggerPattern();
	
	TriggerManager* triggerManager; 
	
	string name; 
 
	bool next();
	bool previous();
	
	bool active;
	//bool stopping;
	
	vector <TriggerPattern> triggerPatterns;
	int currentTriggerPatternIndex;
	
	bool playing;
	bool recording; 
	bool togglePlayPause();
	bool toggleRecord();
	void goToTime(float time);
	
	SequenceCommand addCommand(float time, SequenceCommandType type, int arg);
	vector <SequenceCommand> commands;
	void processCommand(SequenceCommand command);

	float lastUpdate;
	float lengthSeconds;
	float positionSeconds;
	
	ofSoundPlayer music;
	string musicFile;
	
	
	
	//int activeTriggerPatterns;
	
	
//	ofRectangle triggerArea; 
//	bool triggerDebug;
//	bool triggersDisabled;
	
	// AN ARRAY OF TRIGGERS TO CHANGE ARRANGEMENT
	// FROM THE GUI / OSC
	//vector <bool *> triggerPatternChangeTriggers;
    

};