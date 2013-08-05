//
//  Arrangement.cpp
//  ParticlePlay5
//
//  Created by Seb Lee-Delisle on 20/08/2012.
//
//

#include "Arrangement.h"

Arrangement :: Arrangement(ParticleSystemManager & psm, ofRectangle triggerarea, bool fixedposition) :

	// SHOULD MAYBE STOP TRIGGER AREA BEING SET HERE
	particleSystemManager(psm) {
	active = false;
	stopping = false;
	//setTriggerArea(triggerarea);
	//triggerPattern = NULL;
	triggerCount = 0;
		
	fixedPosition = fixedposition;
	
}


void Arrangement :: start() {
	stopping = false; 
	//cout << "start arrangement" << endl;
	for(int i=0; i<triggerCount; i++) {
		
		//if(ofRandom(100)<2) triggers[i]->doTrigger();
		//cout << "start trigger " << i <<endl;
		
		triggers[i]->start();
		
	}
	
	active = true;
	
}


void Arrangement :: stop() {
	
	for(int i=0; i<triggerCount; i++) {
		
		//if(ofRandom(100)<2) triggers[i]->doTrigger();
		
		triggers[i]->stop();
		
		
		
	}
	stopping = true;
	
}

bool Arrangement :: update(float deltaTime) {
	
	if(!active) return false;
	int activeTriggers = 0;
	
	for(int i=0; i<triggerCount; i++) {
		
		if( triggers[i]->update(deltaTime)) activeTriggers++;
		
	}
	if (activeTriggers==0)  {
		active = false;
	}
	
	return active;
	
	
}

void Arrangement:: draw() {
	
	if(!active) return;
	
	for(int i=0; i<triggerCount; i++) {
		
		triggers[i]->draw();
		
	}
	
	
	
}



void Arrangement :: updateMotion(MotionManager& motionManager, cv::Mat homography){
	
	if(!active) return;
	
	for(int i = 0; i<triggerCount; i++) {
		
		TriggerBase * trigger = triggers[i];
		
		if(!trigger->active) continue;
		
		float motion = motionManager.getMotionAtPosition(trigger->pos, trigger->radius*2, homography);
		trigger->registerMotion(motion/255);
		
		//cout << motion << endl;
		
		
	}
	
}

void Arrangement :: setPattern(TriggerPattern tp, ofRectangle& triggerarea, float minspacing, bool showDebug, bool triggersDisabled) {
	
	triggerPattern = tp;
	updateLayout(triggerarea, minspacing, showDebug, triggersDisabled);
	
	
	
	
}

void Arrangement::updateDebug(bool debug){
	for(int i=0; i<triggerCount; i++)
	{
		TriggerBase *trigger = triggers[i] ;
		
		trigger->showDebugData = debug ;
		//cout << "trigger debug : " << trigger->showDebugData << endl;
	}
}

void Arrangement::setTriggersDisabled(bool disabled){
	for(int i=0; i<triggerCount; i++)
	{
		TriggerBase *trigger = triggers[i] ;
		
		trigger->disabled = disabled ;
		//cout << "trigger debug : " << trigger->showDebugData << endl;
	}
}

void Arrangement :: updateLayout(ofRectangle& triggerarea, float minspacing, bool showDebug, bool triggersDisabled) {
	
	triggerArea = triggerarea;
	minimumSpacing = minspacing;
	
	float xPos = 0;//triggerArea.x;
	
	int triggerIndex = 0;
	triggerCount = 0;
	float lastSpacing = 0;
	
	if(triggerPattern.triggers.size()==0) return;
	
	if(fixedPosition) {
		
		//vector<TriggerBase*>& triggers = triggerPattern.triggers;
		
		for (int i = 0; i<triggerPattern.triggers.size(); i++) {
			
			TriggerBase* trigger = triggerPattern.triggers[i];
			
			float yvar = triggerPattern.verticalVariations[triggerIndex];
			float ypos = triggerPattern.verticalPositions[triggerIndex] + ofRandom(-yvar, yvar);
			ypos *= triggerArea.height/2;
			
			if(!trigger->fixedPosition) trigger->pos.x = xPos + triggerArea.x;
			trigger->pos.y = ypos + triggerArea.getCenter().y;
			
			xPos += 50;//triggerPattern.horizSpacings[i];
			
			//cout << trigger->pos.x << " " << trigger->pos.y << endl;
			if(triggers.size()<=i)
				triggers.push_back(trigger);
			
			if(active) trigger->start();
			
			trigger->disabled = triggersDisabled;
			trigger->showDebugData = showDebug; 
			
			triggerCount++; 
		}
		
		
		
		
		
	} else {
		//cout << "updateLayout " << triggerArea.x << " " << triggerArea.width << endl;
			
		
		while (xPos < (triggerArea.width/2)-minimumSpacing/2) {
			//cout << xPos << endl;
			
			TriggerBase* triggerLeft;
			TriggerBase* triggerRight;
			//bool makeNew = false;
			if(triggersLeft.size()>triggerCount) {
				triggerLeft = triggersLeft[triggerCount];
				triggerRight = triggersRight[triggerCount];
				//cout << "REUSING TRIGGERS" << endl;
			} else {
				triggerLeft = triggerPattern.triggers[triggerIndex]->clone();
				triggerRight = triggerPattern.triggers[triggerIndex]->clone();
			
				triggersLeft.push_back(triggerLeft);
				triggersRight.push_back(triggerRight);
				triggers.push_back(triggerLeft);
				triggers.push_back(triggerRight);
				//cout << "MAKING NEW TRIGGERS" << endl;

			}
			
			
			float yvar = triggerPattern.verticalVariations[triggerIndex];
			float ypos = triggerPattern.verticalPositions[triggerIndex] + ofRandom(-yvar, yvar);
			ypos *= triggerArea.height/2; 
			
			triggerLeft->pos.y = ypos + triggerArea.getCenter().y;
			triggerLeft->pos.x = xPos;
			triggerRight->pos = triggerLeft->pos; 
			
			lastSpacing = (minimumSpacing * triggerPattern.horizSpacings[triggerIndex]);
			
			xPos+=lastSpacing;
			
			triggerIndex++;
			if(triggerIndex>=triggerPattern.triggers.size()) triggerIndex = 0;
			triggerCount++;
			
			
		}

		
		// times by two to get both sets
		triggerCount *=2;
		// and subtract one to get rid of double in middle
		//triggerCount--;
		
		float spacing = (triggerArea.width/2) / (xPos- (lastSpacing*0.5)) ;
		//cout << "spacing " << spacing << endl;
		//cout << triggerCount << endl;
		
		
		for(int i = 0; i<triggers.size(); i+=2) {
			
			//cout << i <<  " trigger ";
			
			triggers[i]->pos.x *=spacing;
			triggers[i+1]->pos.x = (triggerArea.x + triggerArea.width) - triggers[i]->pos.x;
			triggers[i]->pos.x+=triggerArea.x;
		
			// disable spares!
			if(i>=triggerCount)
				triggers[i]->stop();
			else {
				if(active) 
					triggers[i]->start();
				triggers[i]->disabled = triggersDisabled;
				triggers[i]->showDebugData = showDebug;
			}
			
			if(i+1>=triggerCount)
				triggers[i+1]->stop();
			else {
				if(active) 
					triggers[i+1]->start();
				triggers[i+1]->disabled = triggersDisabled;
				triggers[i+1]->showDebugData = showDebug;
			}
			
		}
		
	}
	
	
	
	
}
//
//void Arrangement:: setTriggerArea(ofRectangle rect) {
//	triggerArea = rect;
//	for(int i=0; i<triggers.size(); i++) {
//		
//		triggers[i]->pos.y = triggerArea.y+(triggerArea.width/2);
//	}
//	
//}
//
//template <typename T>
//T* Arrangement :: addTrigger(T* trigger) {
//	
//	T* newtrigger = trigger->clone();
//	triggers.push_back(newtrigger);
//	return newtrigger;
//	
//}
//

