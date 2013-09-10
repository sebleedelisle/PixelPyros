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

TriggerRendererBase * TriggerSettings::defaultRenderer = new TriggerRendererBase();
TriggerSettings* TriggerSettings::blank = new TriggerSettings();
//TriggerSettings::blank->setTriggerable(NULL);
//TriggerSettings::blank->setRenderer(NULL);


TriggerSettings::TriggerSettings() {
	
	
	// default settings : TODO - where should this be? 
	
	rechargeSettings = TriggerSettings::defaultRechargeSettings;
	
	hue = 0;
	saturation = 0;
	renderer = TriggerSettings::defaultRenderer;
	triggerable = NULL;
	
}

void TriggerSettings::setTriggerable(TriggerableBase * newtriggerable) {
	triggerable = newtriggerable;
}
void TriggerSettings::setRenderer(TriggerRendererBase * newrenderer) {
	renderer = newrenderer;
}

