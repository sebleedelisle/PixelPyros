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

	void doTrigger(ofVec3f& pos, float power, float direction);

	void draw(float elapsedtime, ofVec3f pos, float radius, ofColor colour, float unitPower, bool active);
	
	ofPath path;
	
	
	PhysicsObject *  makeNewRocket(ofVec3f& pos);

	ParticleSystemManager & particleSystemManager;
	
	RocketSettings* rocketSettings;

};