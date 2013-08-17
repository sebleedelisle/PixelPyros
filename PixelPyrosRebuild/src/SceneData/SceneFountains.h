//
//  SceneFountains.h
//  ArchitectureCamera
//
//  Created by Seb Lee-Delisle on 14/08/2012.
//  Copyright (c) 2012 seb.ly. All rights reserved.
//
#pragma once

#include "Scene.h"
#include "RocketFountain.h"
#include "TriggerRocket.h"



class SceneFountains : public Scene {
	
	public :
	
	SceneFountains(string scenename, ParticleSystemManager& psm, ofRectangle triggerarea) : Scene(scenename, psm, triggerarea){
		
		TriggerRocket trigger(psm);
		
		
		RocketFountain rocket(0,0,0);
		trigger.addRocketSettings(rocket);
		
		trigger.minTriggerInterval = 0.1;
		trigger.restoreSpeed = 1;
		trigger.motionSensitivity = 0;
		
		trigger.triggerPower = 0.5;
		
		TriggerPattern pattern;
		pattern.addTrigger(trigger);
		addArrangement(pattern); 
		
		//addTriggers(trigger, 30, 20,ofGetHeight()*0.85, ofGetWidth()-160);
		
	}
	
	
};