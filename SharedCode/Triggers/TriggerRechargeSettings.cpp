//
//  TriggerRechargeSettings.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 05/09/2013.
//
//

#include "TriggerRechargeSettings.h"


TriggerRechargeSettings* TriggerRechargeSettings::defaultSettings = new TriggerRechargeSettings();


TriggerRechargeSettings::TriggerRechargeSettings() {

	motionTriggerLevel = 0.5;
	triggerPower = 1;
	minTriggerInterval = 0.3;
	
	motionDecay = 20;
	motionSensitivity = 1;
	restoreSpeed = 1;

}