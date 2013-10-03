//
//  TriggerManager.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 21/08/2013.
//
//

#include "TriggerManager.h"


TriggerManager * TriggerManager :: triggerManager = NULL;
TriggerManager * TriggerManager::instance() {
	if(triggerManager ==NULL) {
		triggerManager = new TriggerManager();
	}
	return triggerManager;
}



TriggerManager::TriggerManager () {
	
	triggersDisabled = false;
	triggerDebug = false;
    
    initParams();

}

void TriggerManager::initParams(){
    parameters.setName("Trigger Positioning");
    parameters.add( triggerAreaWidthParam.set("width", 0.5, 0, 1 ) );
    parameters.add( triggerAreaHeightParam.set("height", 0.5, 0, 0.5 ) );
    parameters.add( triggerAreaCenterYParam.set("centre y", 0.5, 0.5, 1 ) );
    parameters.add( triggerSpacingParam.set("spacing", 0, 0, 400 ) );
    
    triggerAreaWidthParam.addListener(this, &TriggerManager::triggerParamChanged);
    triggerAreaHeightParam.addListener(this, &TriggerManager::triggerParamChanged);
    triggerAreaCenterYParam.addListener(this, &TriggerManager::triggerParamChanged);
    triggerSpacingParam.addListener(this, &TriggerManager::triggerParamChanged);
    
}


bool TriggerManager :: update(float deltaTime) {
	
	//if(!active) return false;
	int activeTriggers = 0;
	
	for(int i=0; i<triggers.size(); i++) {
		
		if( triggers[i]->update(deltaTime)) activeTriggers++;
		
	}
	/*
	if (activeTriggers==0)  {
		active = false;
	}*/
	
	return true;
		
}

void TriggerManager :: updateMotion(MotionManager& motionManager, cv::Mat homography){
	
	for(int i=0; i<triggers.size(); i++) {
		
		Trigger* trigger = triggers[i];
		if(!trigger->active) continue;
		
		// Fixed motion size! 10 pixels radius
		float motion = motionManager.getMotionAtPosition(trigger->pos, 10, homography);
		trigger->registerMotion(motion/255);
	}
	
	
}




void TriggerManager :: draw() {
	
	//if(!active) return;
	
	for(int i=0; i<triggers.size(); i++) {
		
		triggers[i]->draw();
		
	}
	
	
	
}


void TriggerManager :: setPattern(TriggerPattern tp ) {
	
	triggerPattern = tp;
	
	// TODO this is where we transfer the settings from the pattern
	// onto all the triggers.
	/*
	for(int i = 0; i<triggers.size(); i++) {
		
		Trigger * trigger = triggers[i];
		if(tp.triggers.size()>0) {
			TriggerSettings settings = tp.triggers[i%(tp.triggers.size())];
			//trigger->hue = sourcetrigger.hue;
			//trigger->saturation = sourcetrigger.saturation;
			
			trigger->copySettings(settings);
			
			trigger->active = true;
			
			cout << i << " hue : " << trigger->hue << endl ;
		} else {
			trigger->active = false;
			
		}
		
	}*/
	
	
	
	updateLayout();
}


//void TriggerManager :: updateTriggerSettings(ofRectangle triggerarea, float spacing ){
//    
//    
//	
//	triggerArea = triggerarea;
//	minimumSpacing = spacing;
//	
//	updateLayout();
//	
//}

void TriggerManager:: setDisplaySize( float width, float height ){
    displayWidth = width;
    displayHeight = height;
}

void TriggerManager :: toggleDebug() {
		
	setShowTriggerDebug(!triggerDebug);
	
}
void TriggerManager::setShowTriggerDebug(bool debug){
	for(int i=0; i<triggers.size(); i++){

		triggers[i]->showDebugData = debug ;
	}
	triggerDebug = debug;
}

void TriggerManager::setTriggersDisabled(bool disabled){
	for(int i=0; i<triggers.size(); i++)
	{
		
		triggers[i]->disabled = disabled ;
	}
}

void TriggerManager :: updateLayout() {
	

	float xPos = 0;
	float midX = triggerArea.x+ triggerArea.width/2;
	
	int triggerIndex = 0;
	triggerCount = 0;

	
	// if it's a blank arrangement then disable all the triggers and quit
	
	if(triggerPattern.triggers.size()==0) {
		
		
		for(int i = 0; i<triggers.size(); i++) {
			triggers[i]->copySettings(NULL);
		}
		
		return;
		
	}
	
	// figure out the spacing between the triggers so that it fills the space
	//float spacing = triggerArea.width / floor(triggerArea.width / minimumSpacing);
	// then work out the number of triggers we can fit
	int numOfTriggers =  ceil(triggerArea.width / minimumSpacing);
	if(numOfTriggers%2==0) {
		numOfTriggers--;
	}
	float spacing = triggerArea.width/(numOfTriggers-1);
	
	while (triggerCount<numOfTriggers ) { //(triggerArea.width/2)-minimumSpacing/2) {
				
		Trigger * trigger;
		
		if(triggers.size()>triggerCount) {
			trigger = triggers.at(triggerCount);
			
		} else {
			trigger = new Trigger();
			triggers.push_back(trigger);
		}
		
		trigger->copySettings(triggerPattern.triggers[triggerIndex]);
		
		trigger->start();
		
		trigger->disabled = triggersDisabled;
		trigger->showDebugData = triggerDebug;
			
		trigger->pos.y = triggerArea.getCenter().y; //ypos +
		trigger->pos.x = xPos + midX;
			
		if(xPos>=0){
			xPos = -xPos-spacing;
		
			triggerIndex++;
			if(triggerIndex>=triggerPattern.triggers.size()) triggerIndex = 0;
		} else {
			xPos = -xPos;
		}

		triggerCount++;
		
		
	}
	
	
	for(int i = triggerCount; i<triggers.size(); i++) {
		triggers[i]->stop();
	}

	
	
}


void TriggerManager :: mouseMoved(int x, int y){

	for(int i = 0; i<triggers.size(); i++) {
		Trigger * trigger = triggers[i];
		float distance = trigger->pos.distance(ofVec3f(x,y));
		if(distance<100) {
			trigger->registerMotion(1.0f-(distance/100.0f));

		}

	}

}

void TriggerManager::triggerParamChanged(float &value){
    triggerArea.width = triggerAreaWidthParam*displayWidth;
    triggerArea.x = (displayWidth - triggerArea.width)/2;
    triggerArea.height = (displayHeight * triggerAreaHeightParam);
    triggerArea.y = (displayHeight * triggerAreaCenterYParam) - (triggerArea.height/2) ;

    minimumSpacing = triggerSpacingParam.get();
    
    updateLayout();
}

void TriggerManager::emptyTriggers() {
	for(int i = 0; i<triggers.size(); i++) {
		Trigger * trigger = triggers[i];
		trigger->unitPower = 0; 
	}
	
	
}
