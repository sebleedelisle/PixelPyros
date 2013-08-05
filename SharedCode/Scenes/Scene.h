//
//  Scene.h
//  SceneCalibration
//
//  Created by Seb Lee-Delisle on 02/08/2012.
//  Copyright (c) 2012 seb.ly. All rights reserved.
//

#pragma once 


#include "constants.h"
#include "Arrangement.h"
#include "ParticleSystemManager.h"
#include "MotionManager.h"
#include "ofxCV.h"


class Scene { 


	public : 
	
	Scene(string scenename, ParticleSystemManager& psm, ofRectangle triggerarea);
	
	virtual void start();
	virtual void stop();
	
	virtual bool update(float deltaTime); 
	virtual bool draw();
	
	virtual void updateMotion(MotionManager& motionManager, cv::Mat homography);
   
	virtual bool changeArrangement(int num);
	
	Arrangement& addArrangement(TriggerPattern& pattern, bool fixedPosition = false);
	
	void updateTriggerSettings(ofRectangle triggerarea, float spacing);
	void setShowTriggerDebug(bool);
	void  setTriggersDisabled(bool disabled);

	string name; 
 
	bool next();
	bool previous();
	
	bool active; 
	bool stopping;
	
	vector <Arrangement*> arrangements;
	int currentArrangementIndex;
	int activeArrangements; 
	
	ParticleSystemManager& particleSystemManager; 
	
	ofRectangle triggerArea; 
	bool triggerDebug;
	bool triggersDisabled;
	
	vector <bool *> arrangementTriggers; 
    
private:
        
    void init(ofRectangle triggerarea);
};