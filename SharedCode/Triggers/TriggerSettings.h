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
#include "TriggerRechargeSettings.h"


class TriggerSettings {

	public:
	
	static TriggerRendererBase * defaultRenderer;
	static TriggerSettings blank;
	static TriggerRechargeSettings* defaultRechargeSettings;
	
	TriggerSettings();
	void setTriggerable(TriggerableBase * newtriggerable);
	void setRenderer(TriggerRendererBase * newrenderer);
	
		
	//ofColor colour;
	float hue;
	float saturation;
	
	TriggerRechargeSettings* rechargeSettings;
	
	TriggerRendererBase * renderer; 
	TriggerableBase * triggerable;
	
	// TODO ADDITIONAL STUFF FOR TRIGGER SETTINGS
	// rotating triggers
	// one shot / rechargeable
	
	
};



