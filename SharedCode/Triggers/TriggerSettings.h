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
	
	// if set, this offsets the sin position dependent on xposition
	float rotateOscillationOffset;
	
	// if set, rotates angle around dependent on triggerPosition
	float rotateMirrorOffset;
	
	TriggerRechargeSettings* rechargeSettings;

	// if true, then trigger's power is diminished on initialisation
	bool startEmpty;
	
	// false by default, needs overriding. 
	bool enabled;
	
	//virtual void doTrigger(ofVec3f& pos);
	
	//virtual void doTrigger(ofVec3f& pos, float power);
	
	virtual void doTrigger(ofVec3f& pos, float power, float direction, map<string, float>& values);
	
	// MUST BE CALLED RIGHT BEFORE DRAW
	virtual void update(float deltaTime, map<string, float>& triggerValues);
	
	virtual void draw(float elapsedtime, ofVec3f pos,  float unitPower, bool active, float scale = 1, float angle = 0);
	
	
	virtual ofColor getColour();
	
	map<string, float>* values; 
	

};