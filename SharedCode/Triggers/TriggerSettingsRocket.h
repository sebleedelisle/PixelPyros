//
//  TriggerableRocket.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 01/09/2013.
//
//

#pragma once

#include "TriggerSettings.h"
#include "ParticleSystemManager.h"


class TriggerSettingsRocket : public TriggerSettings {


	public :
	
	TriggerSettingsRocket(); 

	virtual void doTrigger(ofVec3f& pos, float power, float direction);

	virtual void draw(float elapsedtime, ofVec3f pos, ofColor colour, float unitPower, bool active);
	
	
	ofPath path;

	virtual PhysicsObject *  makeNewRocket(ofVec3f& pos);

	ParticleSystemManager & particleSystemManager;
	
	RocketSettings* rocketSettings;

};