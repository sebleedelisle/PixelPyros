//
//  TriggerSettings.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 05/09/2013.
//
//

#include "TriggerSettings.h"
#include "TriggerRechargeSettings.h"

TriggerRendererBase * TriggerSettings::defaultRenderer = new TriggerRendererBase();
TriggerSettings TriggerSettings::blank;

//: TriggerSettings::blank.setTriggerable(NULL);

//TriggerSettings::blank.setRenderer(NULL);


TriggerSettings::TriggerSettings() {
	
	// default settings :
	TriggerSettings::blank.setTriggerable(NULL);
	TriggerSettings::blank.setRenderer(NULL);
	
	//rechargeSettings = TriggerRechargeSettings::defaultSettings;
	
	

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
