//
//  TriggerableRocket.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 01/09/2013.
//
//

#pragma once

#include "TriggerableBase.h"
#include "ParticleSystemManager.h"


class TriggerableRocket : public TriggerableBase {


	public :
	
	TriggerableRocket(ParticleSystemManager &psm); 

	void doTrigger(ofVec3f& pos, float power, float direction);
	
	PhysicsObject *  makeNewRocket(ofVec3f& pos);

	ParticleSystemManager & particleSystemManager;
	
	RocketSettings rocketSettings;

};