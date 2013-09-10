//
//  TriggerSettings.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 28/08/2013.
//
//

#pragma once

#include "TriggerRechargeSettings.h"
#include "ofMain.h"

class TriggerSettings {

	public:
	
	static TriggerSettings* blank;
	static TriggerRechargeSettings* defaultRechargeSettings;
	
	TriggerSettings();
	
	//ofColor colour;
	float hue;
	float saturation;
	float elapsedTime;
	
	
	TriggerRechargeSettings* rechargeSettings;
	
	virtual void doTrigger(ofVec3f& pos);
	
	virtual void doTrigger(ofVec3f& pos, float power);
	
	virtual void doTrigger(ofVec3f& pos, float power, float direction);

	
	virtual void draw(float elapsedtime, ofVec3f pos, float radius, ofColor colour, float unitPower, bool active);



};