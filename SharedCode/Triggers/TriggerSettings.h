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
	
	float hue;
	float saturation;
	float elapsedTime;
	float radius;
	
	// rotation settings
	float rotationExtent;
	float rotationSpeed;
	bool rotateOnFire;
	
	TriggerRechargeSettings* rechargeSettings;

	// if true, then trigger's power is diminished on initialisation
	bool startEmpty;
	
	virtual void doTrigger(ofVec3f& pos);
	
	virtual void doTrigger(ofVec3f& pos, float power);
	
	virtual void doTrigger(ofVec3f& pos, float power, float direction);

	
	virtual void draw(float elapsedtime, ofVec3f pos,  float unitPower, bool active, float scale = 1, float angle = 0);

	virtual ofColor getColour(); 
	

};