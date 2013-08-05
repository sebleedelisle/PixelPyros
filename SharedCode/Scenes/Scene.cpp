//
//  Scene.cpp
//  SceneCalibration
//
//  Created by Seb Lee-Delisle on 02/08/2012.
//  Copyright (c) 2012 seb.ly. All rights reserved.
//

#include "Scene.h"


Scene::Scene(string scenename, ParticleSystemManager & psm, ofRectangle triggerarea) : particleSystemManager(psm) {
    init(triggerarea);
	
	name = scenename; 
	
	triggerDebug = false;
	triggersDisabled = false;
}


void Scene::init(ofRectangle triggerarea) {
	active = false; 
	stopping = false;
	triggerArea = triggerarea;
	//setTriggerArea(triggerarea);
	currentArrangementIndex = -1;
	activeArrangements = 0;
}

void Scene :: start() {
	stopping = false; 
	if ((arrangements.size()==0)|| (changeArrangement(0))) active = true;
}

void Scene :: stop() { 
	
	for(int i=0; i<arrangements.size(); i++) {

		arrangements[i]->stop();
		
	}
	stopping = true; 
	
}

bool Scene :: update(float deltaTime) {

	for(int i = 0; i<arrangementTriggers.size(); i++) {
		
		
		if(*arrangementTriggers[i] && currentArrangementIndex!=i) {
			
			if(active) {
				cout << "CHANGING ARRANGEMENT " << i << endl;
				changeArrangement(i);
				
			} 
			
			
		} 		
		*arrangementTriggers[i] = false;
	}
	
	if(!active) return false;
	
	
	
	activeArrangements = 0;
	
	for(int i=0; i<arrangements.size(); i++) {
		if( arrangements[i]->update(deltaTime)) activeArrangements++;
		
		//THIS LINE MAKES IT AUTO CONTINUE - maybe a scene flag? 
		//else if ((!stopping) && (i==currentArrangementIndex)) next();
		
	}
	
	
	if((stopping) && (activeArrangements==0) ) {
		active = false;
	}

	return active; 
	
	
}


bool Scene:: draw() {

	if(!active) return false; 
	for(int i=0; i<arrangements.size(); i++) {
		
		arrangements[i]->draw();
		
	}
	
	return true; 

}
void Scene :: updateMotion(MotionManager& motionManager, cv::Mat homography){
	
	for(int i = 0; i<arrangements.size(); i++) {
		
		Arrangement * arrangement = arrangements[i];

		arrangement->updateMotion(motionManager, homography);
		
//		float motion = motionManager.getMotionAtPosition(trigger->pos, trigger->radius*2, homography); 
//		trigger->registerMotion(motion/255);
		
		//cout << motion << endl; 
		
		
	}
	
}

void Scene :: updateTriggerSettings(ofRectangle triggerarea, float spacing ){

	if(spacing<=0) spacing = 0.1;
	for(int i = 0; i<arrangements.size() ; i++) {
		arrangements[i]->updateLayout(triggerarea, spacing, triggerDebug, triggersDisabled);
	}

}

void  Scene :: setShowTriggerDebug(bool showDebug) {
	triggerDebug = showDebug;
	
	for(int i = 0; i<arrangements.size() ; i++) {
		arrangements[i]->updateDebug(triggerDebug);
	}
	
}

void  Scene :: setTriggersDisabled(bool disabled) {
	triggersDisabled =disabled; 
	for(int i = 0; i<arrangements.size() ; i++) {
		arrangements[i]->setTriggersDisabled(disabled);
	}
	
}



Arrangement& Scene ::addArrangement(TriggerPattern& pattern, bool fixedPosition) {
	arrangements.push_back(new Arrangement(particleSystemManager, triggerArea, fixedPosition));
	//arrangements.back()->setTriggerArea(triggerArea);
	arrangements.back()->setPattern(pattern, triggerArea, 50, triggerDebug, triggersDisabled);
	arrangementTriggers.push_back(new bool(false));
	
}


bool Scene :: changeArrangement(int num) {
	
	//if(currentArrangementIndex == num) return false;
	
	if((num>=arrangements.size())|| (stopping))  return false;

	for(int i = 0; i< arrangements.size(); i++) { 
		if(i!=num) {
			arrangements[i]->stop();
			*arrangementTriggers[i] = false;
		} else *arrangementTriggers[i] = true;
	}
	
	arrangements[num]->start();
	currentArrangementIndex = num; 
	return true;
	
	
}



bool Scene :: next() {
	if(arrangements.size()==0) return false;
	
	int nextArrangement = currentArrangementIndex+1;
	if(nextArrangement>=arrangements.size())
		nextArrangement = 0;
	
	changeArrangement(nextArrangement);
	
	
}

bool Scene :: previous() {

	if(arrangements.size()==0) return false;
	
	int prevArrangement = currentArrangementIndex-1;
	if(prevArrangement<0)
		prevArrangement = arrangements.size();
	
	changeArrangement(prevArrangement);


}