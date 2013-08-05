//
//  Trigger.cpp
//  ParticlePlay4
//
//  Created by Seb Lee-Delisle on 02/08/2012.
//  Copyright (c) 2012 seb.ly. All rights reserved.
//

#include "TriggerRocket.h"


TriggerRocket :: TriggerRocket (ParticleSystemManager& psm, float triggerRadius) : TriggerSimple(psm, triggerRadius){
	
	typeLabel = "TriggerRocket"; 
	
	currentRocketIndex = 0;
	useAllPower = false;
	
	
}
void TriggerRocket::draw() {
	
	if(!active) return;
    
    TriggerSimple::draw() ;
}

bool TriggerRocket::doTrigger() { 
	
	if(!TriggerSimple :: doTrigger()) return false;
	if(rocketSettings.size()==0) return false;
	
	PhysicsObject *rocket = makeNewRocket(); 
	
	return true; 
}

PhysicsObject * TriggerRocket:: makeNewRocket() {
	
	RocketSettings & rs = rocketSettings[currentRocketIndex];
	currentRocketIndex++;
	if(currentRocketIndex==rocketSettings.size()) currentRocketIndex = 0;

	PhysicsObject *rocket = particleSystemManager.addRocket(rs, pos);
	
	// can use this to adjust height of fireworks
	//rocket->velScalar.set(1,1,1);
	
	return rocket; 
	
	
}

void TriggerRocket:: addRocketSettings(RocketSettings rocket) {
	
	rocketSettings.push_back(rocket);
	
	
}
