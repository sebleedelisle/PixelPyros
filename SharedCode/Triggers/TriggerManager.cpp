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
	triggerDebugMode = false;
    
	rectanglePreviewBrightness = 1;
	
    initParams();

}

void TriggerManager::initParams(){
    parameters.setName("Triggers");
    parameters.add( triggerAreaWidthParam.set("width", 0.9125, 0, 1 ) );
    parameters.add( triggerAreaTopParam.set("top", 0.8, 0.7, 1 ) );
	parameters.add( triggerAreaBottomParam.set("bottom", 0.9, 0.7, 1 ) );
	parameters.add( triggerNumParam.set("number of triggers", 28, 1, 40 ) );
	
	parameters.add( triggerSampleSizeParam.set("trigger sample size", 10,2,60) );
				   
    parameters.add( triggerOscillationParam.set("vertical oscillation", 5.9, 0, 10 ) );
    parameters.add( triggerDebugMode.set("Debug Mode",false) );
    
	parameters.add( triggerMode.set("mode",0,0,2));
	parameters.add( triggerModeString.set("trigger mode"));
	
	parameters.add( numVertSamples.set("vertical sample num", 10, 6,20));
	parameters.add( motionMultiplier.set("motion multiplier", 0.1, 0.00001, 1));
	parameters.add( motionSamplesResetSpeed.set("motion reset speed", 0.99, 0.8,0.999999));
	parameters.add( motionTargetThreshold.set("target threshold", 50, 1, 200));
	parameters.add( moveTowardMotionSpeed.set("move speed", 0.05, 0.001, 0.2));
	parameters.add( moveHomeSpeed.set("move home speed", 20, 1,100)); 
	parameters.add( multiSampleSize.set("samples sample size", 5,2,60) );
								  
    triggerAreaWidthParam.addListener(this, &TriggerManager::triggerParamChanged);
    triggerAreaTopParam.addListener(this, &TriggerManager::triggerParamChanged);
    triggerAreaBottomParam.addListener(this, &TriggerManager::triggerParamChanged);
    triggerNumParam.addListener(this, &TriggerManager::triggerParamIntChanged);
    triggerOscillationParam.addListener(this, &TriggerManager::triggerParamChanged);
	triggerMode.addListener(this, &TriggerManager::triggerModeChanged);
    triggerDebugMode.addListener(this, &TriggerManager::setShowTriggerDebug);
    
    //Needed to load defaults
    updateTriggerValues();
}


bool TriggerManager :: update(float deltaTime) {
	
		
	//if(!active) return false;
	int activeTriggers = 0;
	
	for(int i=0; i<triggers.size(); i++) {
		
		if( triggers[i]->update(deltaTime, triggerArea)) activeTriggers++;
		
	}
	/*
	if (activeTriggers==0)  {
		active = false;
	}*/
	
	triggerModeString = (triggerMode==0)? "MANUAL" : "AUTO";
	
	

	
	if(triggerMode==TRIGGER_MODE_AUTO) {
		for(int i=0; i<triggers.size(); i++) {
			
			Trigger& trigger = *triggers[i];
			if(!trigger.active) continue;
			
			
			if(trigger.vertMotionSamples.size()!=numVertSamples) {
				trigger.vertMotionSamples.resize(numVertSamples);
			}
			
			// fade out the samples
			for(int i = 0; i<numVertSamples; i++) {
				float& sample = trigger.vertMotionSamples[i];
				sample*=motionSamplesResetSpeed;
			}

			int topposition = -1;
			for(int j = numVertSamples-1; j>=0; j--) {
				if(trigger.vertMotionSamples[j] > motionTargetThreshold) {
					topposition = j;
				}
			}
			
			if(topposition == -1) {
				trigger.pos.y -= deltaTime * moveHomeSpeed;
				if(trigger.pos.y < triggerArea.getTop()) trigger.pos.y = triggerArea.getTop();
				
			} else {
				float targety = ofMap(topposition, 0, numVertSamples, triggerArea.getTop(), triggerArea.getBottom());
				trigger.pos.y += (targety-trigger.pos.y) * moveTowardMotionSpeed;
			}
			
			
		}
	}

	
	return true;
		
}

void TriggerManager :: updateMotion(MotionManager& motionManager, cv::Mat homography){
	
	for(int i=0; i<triggers.size(); i++) {
		
		Trigger* trigger = triggers[i];
		if(!trigger->active) continue;
		
		// Fixed motion size! 10 pixels radius
		float motion = motionManager.getMotionAtPosition(trigger->pos, triggerSampleSizeParam, homography);
		trigger->registerMotion(motion/255);
	}
		
	for(int i=0; i<triggers.size(); i++) {
		
		Trigger& trigger = *triggers[i];
		if(!trigger.active) continue;
	
		if(trigger.vertMotionSamples.size()>numVertSamples) {
			trigger.vertMotionSamples.resize(numVertSamples); 
		}
		
		for(int j = 0; j<numVertSamples; j++) {
			
			float ypos = ofMap(j, 0, numVertSamples, triggerArea.getTop(), triggerArea.getBottom());
			
			if(trigger.vertMotionSamples.size()<=j) {
				trigger.vertMotionSamples.push_back(0);
			}
			
			
			trigger.vertMotionSamples[j] += motionManager.getMotionAtPosition(ofVec2f(trigger.pos.x, ypos), multiSampleSize, homography)*motionMultiplier;
			if(trigger.vertMotionSamples[j]>255) trigger.vertMotionSamples[j] = 255;
		}
	}
}


void TriggerManager :: draw() {
	
	//if(!active) return;
	
	for(int i=0; i<triggers.size(); i++) {
		triggers[i]->draw(triggerArea, motionTargetThreshold);
	}
	
	
	if(rectanglePreviewBrightness>0) {
		ofPushStyle();
		ofNoFill();
		ofSetColor(255 * rectanglePreviewBrightness);
		ofSetLineWidth(1);
		ofRect(triggerArea);
	
		ofPopStyle();
		rectanglePreviewBrightness-=0.05; 
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
    triggerDebugMode = !triggerDebugMode;
    bool debug = triggerDebugMode;
	setShowTriggerDebug(debug);
	
}
void TriggerManager::setShowTriggerDebug(bool & debug){
	for(int i=0; i<triggers.size(); i++){
		triggers[i]->showDebugData = debug ;
	}
}

void TriggerManager::setTriggersDisabled(bool disabled){
	for(int i=0; i<triggers.size(); i++)
	{
		
		triggers[i]->disabled = disabled ;
	}
}

void TriggerManager :: updateLayout() {
	
	triggerPatternOffset++; 
	
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
	
	int numOfTriggers = triggerNumParam;
	float spacing = minimumSpacing;
	float xPos = 0;
	if(numOfTriggers%2==0) {
		xPos-= minimumSpacing/2;
	}
	/*
	if(triggerPattern.arrangeMode == TRIGGER_ARRANGE_MIRROR) {
		numOfTriggers =  ceil(triggerArea.width / minimumSpacing);
		if(numOfTriggers%2==0) {
			numOfTriggers--;
		}
		spacing = triggerArea.width/(numOfTriggers-1);
		
	} else if(triggerPattern.arrangeMode == TRIGGER_ARRANGE_DISTRIBUTE) {
		numOfTriggers = triggerPattern.triggers.size();
		spacing = triggerArea.width/(numOfTriggers-1);
		xPos = triggerArea.getLeft(); 
	}*/
	
	while (triggerCount<numOfTriggers ) {
		
		Trigger * trigger;
		
		if(triggers.size()>triggerCount) {
			trigger = triggers.at(triggerCount);
			
		} else {
			trigger = new Trigger();
			triggers.push_back(trigger);
			if(triggerMode == TRIGGER_MODE_AUTO) trigger->pos.y = triggerArea.getTop();
		}
		
		trigger->copySettings(triggerPattern.triggers[triggerIndex]);
		
		trigger->disabled = trigger->disabled || triggersDisabled;
		
		
		trigger->start();
		
		trigger->showDebugData = triggerDebugMode;
			
		if(triggerPattern.arrangeMode == TRIGGER_ARRANGE_MIRROR) {
			trigger->pos.x = xPos + midX;
			if(xPos>=0){
				xPos = -xPos-spacing;
				
				triggerIndex++;
				if(triggerIndex>=triggerPattern.triggers.size()) triggerIndex = 0;
			} else {
				xPos = -xPos;
			}
		} else {
			trigger->pos.x = xPos;
			triggerIndex++;
			xPos+=spacing;
		}
		
		if(triggerMode == TRIGGER_MODE_MANUAL) {
			trigger->pos.y = triggerArea.getCenter().y + cos((trigger->pos.x - midX)/(triggerArea.getWidth())* triggerOscillationParam * PI ) * (triggerArea.getHeight()/2);
		}
			


		triggerCount++;
		
		
	}
	
	
	for(int i = triggerCount; i<triggers.size(); i++) {
		triggers[i]->stop();
	}

	
	
}


void TriggerManager :: mouseMoved(int x, int y, ofRectangle previewRect){

	for(int i = 0; i<triggers.size(); i++) {
		Trigger * trigger = triggers[i];
		float distance = trigger->pos.distance(ofVec3f(x,y));
		if(distance<100) {
			trigger->registerMotion(1.0f-(distance/100.0f));

		}

	}
	
	x = ofMap(x, 0, APP_WIDTH, previewRect.getLeft(), previewRect.getRight());
	y = ofMap(y, 0, APP_HEIGHT, previewRect.getTop(), previewRect.getBottom());
	
	for(int i = 0; i<triggers.size(); i++) {
		Trigger * trigger = triggers[i];
		float distance = trigger->pos.distance(ofVec3f(x,y));
		if(distance<50) {
			trigger->registerMotion(1.0f-(distance/50.0f));
			
		}
		
	}
	

}

void TriggerManager::triggerParamChanged(float &value){
	updateTriggerValues();
	
	rectanglePreviewBrightness = 1;
}

void TriggerManager::triggerParamIntChanged(int &value){
	
   updateTriggerValues();
	
	rectanglePreviewBrightness = 1;
	
	
	
	
}

void TriggerManager::triggerModeChanged(int &value){
	
	// hack because the int slider is stupid :)
	if(triggerMode >1) triggerMode = 1;
	
	
	updateTriggerValues();
	
	rectanglePreviewBrightness = 1;

}




void TriggerManager::updateTriggerValues(){
    triggerArea.width = triggerAreaWidthParam*displayWidth;
    triggerArea.x = (displayWidth - triggerArea.width)/2;
	
	if(triggerAreaTopParam>triggerAreaBottomParam) triggerAreaTopParam = triggerAreaBottomParam;
	
    triggerArea.y = (displayHeight * triggerAreaTopParam)  ;
	triggerArea.height = displayHeight * (triggerAreaBottomParam - triggerAreaTopParam)  ;
	
    minimumSpacing = triggerArea.width/((float)triggerNumParam-1);
    
    updateLayout();
}

void TriggerManager::emptyTriggers() {
	for(int i = 0; i<triggers.size(); i++) {
		Trigger * trigger = triggers[i];
		trigger->unitPower = 0; 
	}
	
	
}
