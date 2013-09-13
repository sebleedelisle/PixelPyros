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
	radius = 10;
	
	
}

void TriggerSettings::doTrigger(ofVec3f& pos) {
	doTrigger(pos, 1,0);
}

void TriggerSettings::doTrigger(ofVec3f& pos, float power) {
	doTrigger(pos, power, 0);
}

void TriggerSettings::doTrigger(ofVec3f& pos, float power, float direction) {
	//ofLog(OF_LOG_WARNING, "triggered");
}


void TriggerSettings::draw(float elapsedtime, ofVec3f pos, ofColor colour, float unitPower, bool active ) {
	
	ofPushStyle();
	ofNoFill();
	
	ofSetColor(colour);
	if(!active) ofSetColor(ofColor::gray);
	
	ofCircle(pos, radius);
	ofPopStyle();
	
}


