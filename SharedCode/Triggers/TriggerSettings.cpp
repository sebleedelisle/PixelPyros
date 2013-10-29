//
//  TriggerSettings.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 05/09/2013.
//
//

#include "TriggerSettings.h"
#include "TriggerRechargeSettings.h"

TriggerRechargeSettings* TriggerSettings::defaultRechargeSettings = new TriggerRechargeSettings();

TriggerSettings* TriggerSettings::blank = new TriggerSettings() ;



TriggerSettings::TriggerSettings() {
	if(TriggerSettings::blank!=NULL) {
		TriggerSettings::blank->radius = 4;
		
	
	}
		// default settings : TODO - where should this be?
	
	rechargeSettings = TriggerSettings::defaultRechargeSettings;
	
	hue = 0;
	saturation = 0;
	radius = 7;
	
	rotationExtent = 0;
	rotationSpeed = 0;
	
	rotateOscillationOffset = 0;
	rotateMirrorOffset = 5;
	
	enabled = false;
	
	rotateOnFire = false;
	startEmpty = false;
	numTriggers = 1; 
	
}

/*

void TriggerSettings::doTrigger(ofVec3f& pos) {
	doTrigger(pos, 1,0);
}

void TriggerSettings::doTrigger(ofVec3f& pos, float power) {
	doTrigger(pos, power, 0);
}
*/
void TriggerSettings::doTrigger(ofVec3f& pos, float power, float direction, map<string, float>& values) {
	//ofLog(OF_LOG_WARNING, "triggered");
}

ofColor TriggerSettings::getColour() {
	return ofColor::black;
	
}


void TriggerSettings::update(float deltaTime, map<string, float> &triggerValues){
	values = &triggerValues;
}

void TriggerSettings::draw(float elapsedtime, ofVec3f pos, float unitPower, bool active, float scale, float angle ) {
	
	
	// BASE CLASS HAS NO RENDERER
	return;
	/*
	
	
	ofPushStyle();
	ofNoFill();
	
	ofSetColor(colour);
	if(!active) ofSetColor(ofColor::gray);
	
	ofCircle(pos, radius);
	ofPopStyle();
	*/
}


