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
#include "ParticleSystemManager.h"
#include "MotionManager.h"
#include "ofxCV.h"


class Scene { 


	public : 
	
	Scene(string scenename);
	
	virtual void start();
	virtual void stop();
	
	virtual bool update(float deltaTime); 
	virtual bool draw();
	
	virtual void updateMotion(MotionManager& motionManager, cv::Mat homography);
   
	virtual bool changeTriggerPattern(int num);
	
	void addTriggerPattern(TriggerPattern& pattern);
	
	TriggerPattern getCurrentTriggerPattern();
	
//	void updateTriggerSettings(ofRectangle triggerarea, float spacing);
//	void setShowTriggerDebug(bool);
//	void setTriggersDisabled(bool disabled);

	string name; 
 
	bool next();
	bool previous();
	
	bool active; 
	bool stopping;
	
	vector <TriggerPattern> triggerPatterns;
	int currentTriggerPatternIndex;
	int activeTriggerPatterns; 
	
	ParticleSystemManager& particleSystemManager; 
	
//	ofRectangle triggerArea; 
//	bool triggerDebug;
//	bool triggersDisabled;
	
	// AN ARRAY OF TRIGGERS TO CHANGE ARRANGEMENT
	// FROM THE GUI / OSC
	vector <bool *> triggerPatternChangeTriggers;
    

};