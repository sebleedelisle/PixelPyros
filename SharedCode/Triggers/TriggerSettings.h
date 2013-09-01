//
//  TriggerSettings.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 28/08/2013.
//
//

#pragma once

#include "TriggerRendererBase.h"
#include "TriggerableBase.h"

class TriggerSettings {

	public:
	
	TriggerSettings() {
		
		// default settings :
		
		motionTriggerLevel = 0.5;
		triggerPower = 1;
		minTriggerInterval = 0.3;
		
		motionDecay = 20;
		motionSensitivity = 1;
		restoreSpeed = 1;
		
		hue = 0;
		saturation = 0;
		renderer = NULL;
		triggerable = NULL;
		
	}

	void setTriggerable(TriggerableBase * newtriggerable) {
		triggerable = newtriggerable;
	}
	void setRenderer(TriggerRendererBase * newrenderer) {
		renderer = newrenderer;
	}
	
	
	
	// motionTriggerLevel is the amount of motion needed to make something happen
	float motionTriggerLevel;
	
	// the amount of power taken away when it triggers
	float triggerPower;
	
	
	// minimum time between triggers
	float minTriggerInterval;

	//amount per second to take away from the accumulated motion
	float motionDecay;

	
	// a scalar that multiplies the motion level to add to the
	// unitPower
	float motionSensitivity;
	
	// set restoreSpeed to 0 to make it a single shot trigger
	float restoreSpeed;
	
	//ofColor colour;
	float hue;
	float saturation;
	
	TriggerRendererBase * renderer; 
	TriggerableBase * triggerable;
	
	// TODO ADDITIONAL STUFF FOR TRIGGER SETTINGS
	// rotating triggers
	// one shot / rechargeable
	
	
};

