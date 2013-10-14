//
//  TriggerSettingsRocketOrb.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 11/10/2013.
//
//

#pragma once

#include "TriggerSettingsRocket.h" 

class TriggerSettingsRocketOrb : public TriggerSettingsRocket {



	virtual void update(float deltaTime, map<string, float>&triggerValues);
	virtual void draw(float elapsedtime, ofVec3f pos, float unitPower, bool active, float scale, float angle);

	float deltaTime; 






};