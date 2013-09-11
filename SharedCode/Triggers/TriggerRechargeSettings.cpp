//
//  TriggerRechargeSettings.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 05/09/2013.
//
//

#include "TriggerRechargeSettings.h"


//TriggerRechargeSettings* TriggerRechargeSettings::defaultSettings = new TriggerRechargeSettings();

TriggerRechargeSettings* TriggerRechargeSettings::medium = new TriggerRechargeSettings(1);
TriggerRechargeSettings* TriggerRechargeSettings::fast = new TriggerRechargeSettings(2);
TriggerRechargeSettings* TriggerRechargeSettings::slow = new TriggerRechargeSettings(0.5);

TriggerRechargeSettings::TriggerRechargeSettings() {

	initDefaults();

}

TriggerRechargeSettings::TriggerRechargeSettings(float restorespeed) {

	initDefaults(); 
	restoreSpeed = restorespeed;

}
												 
void TriggerRechargeSettings :: initDefaults() {
	motionTriggerLevel = 0.5;
	triggerPower = 1;
	minTriggerInterval = 0.3;
	
	motionDecay = 20;
	motionSensitivity = 1;
	restoreSpeed = 1;

}