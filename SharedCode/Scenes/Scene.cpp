//
//  Scene.cpp
//  SceneCalibration
//
//  Created by Seb Lee-Delisle on 02/08/2012.
//  Copyright (c) 2012 seb.ly. All rights reserved.
//

#include "Scene.h"


Scene::Scene(string scenename, ParticleSystemManager & psm) : particleSystemManager(psm) {
	active = false;
	stopping = false;

	currentTriggerPatternIndex = 0;
	activeTriggerPatterns = 0;
	
	name = scenename;
}


void Scene :: start() {
	stopping = false; 
	if ((triggerPatterns.size()==0)|| (changeTriggerPattern(0))) active = true;
}

void Scene :: stop() { 
	
	// TODO : tell triggerManager to stop the triggers
	
	for(int i=0; i<triggerPatterns.size(); i++) {

		//triggerPatterns[i]->stop();
		
	}
	stopping = true; 
	
}

bool Scene :: update(float deltaTime) {

	
	// check to see if a changeTriggerPattern message has come in from
	// the external UI and if so, change to that arrangement
	for(int i = 0; i<triggerPatternChangeTriggers.size(); i++) {
		if(*triggerPatternChangeTriggers[i] && currentTriggerPatternIndex!=i) {
			if(active) {
				cout << "CHANGING ARRANGEMENT " << i << endl;
				changeTriggerPattern(i);
			} 
		} 		
		*triggerPatternChangeTriggers[i] = false;
	}
	
	if(!active) return false;
	
	activeTriggerPatterns = 0;
	
	for(int i=0; i<triggerPatterns.size(); i++) {
		//if( triggerPatterns[i]->update(deltaTime)) activeTriggerPatterns++;
		
		//THIS LINE MAKES IT AUTO CONTINUE - maybe a scene flag? 
		//else if ((!stopping) && (i==currentTriggerPatternIndex)) next();
		
	}
	
	
	if((stopping) && (activeTriggerPatterns==0) ) {
		active = false;
	}

	return active; 
	
	
}


bool Scene:: draw() {

	if(!active) return false; 
	for(int i=0; i<triggerPatterns.size(); i++) {
		
		//triggerPatterns[i]->draw();
		
	}
	
	return true; 

}
void Scene :: updateMotion(MotionManager& motionManager, cv::Mat homography){
	
	for(int i = 0; i<triggerPatterns.size(); i++) {
		
		//Arrangement * arrangement = triggerPatterns[i];

		//arrangement->updateMotion(motionManager, homography);
	}
	
}


TriggerPattern Scene :: getCurrentTriggerPattern() {

	return triggerPatterns[currentTriggerPatternIndex];
	
}

void Scene ::addTriggerPattern(TriggerPattern& pattern) {
	triggerPatterns.push_back(pattern);
	triggerPatternChangeTriggers.push_back(new bool(false));
}

bool Scene :: changeTriggerPattern(int num) {
	
	//if(currentTriggerPatternIndex == num) return false;
	
	if((num>=triggerPatterns.size())|| (stopping))  return false;
	
	//TODO this needs to tell the triggerManager to change stuff
	
	
	/*
	for(int i = 0; i< triggerPatterns.size(); i++) { 
		if(i!=num) {
			triggerPatterns[i]->stop();
			*arrangementChangeTriggers[i] = false;
		} else *arrangementChangeTriggers[i] = true;
	}
	
	triggerPatterns[num]->start();*/
	
	
	
	currentTriggerPatternIndex = num; 
	return true;
	
	
}



bool Scene :: next() {
	if(triggerPatterns.size()==0) return false;
	
	int nextArrangement = currentTriggerPatternIndex+1;
	if(nextArrangement>=triggerPatterns.size())
		nextArrangement = 0;
	
	changeTriggerPattern(nextArrangement);
	
	
}

bool Scene :: previous() {

	if(triggerPatterns.size()==0) return false;
	
	int prevArrangement = currentTriggerPatternIndex-1;
	if(prevArrangement<0)
		prevArrangement = triggerPatterns.size()-1;
	
	changeTriggerPattern(prevArrangement);


}