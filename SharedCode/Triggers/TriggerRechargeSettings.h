//
//  TriggerRechargeSettings.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 05/09/2013.
//
//

#pragma once

class TriggerRechargeSettings {

	public:
	
	static TriggerRechargeSettings* defaultSettings;
	
	TriggerRechargeSettings();
	
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





};