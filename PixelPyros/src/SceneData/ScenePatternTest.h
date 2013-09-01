//
//  ScenePatternTest.h
//  ParticlePlay5
//
//  Created by Seb Lee-Delisle on 20/08/2012.
//
//

#pragma once

#include "Scene.h"
#include "Trigger.h"
#include "RocketBasic.h"
#include "Arrangement.h"

#include "TriggerPattern.h"



class ScenePatternTest : public Scene {

	
	public :

	ScenePatternTest(string scenename, ParticleSystemManager& psm, ofRectangle triggerarea) : Scene(scenename, psm, triggerarea){
	
		RocketBasic rocketSettings(100,10, 120);
		
		Trigger trigger(particleSystemManager);
		
		trigger.addRocketSettings(rocketSettings);
		// makes one shot type
		trigger.type = TRIGGER_TYPE_FIRE_ON_MOTION;
		trigger.motionTriggerLevel = 1;
		trigger.restoreSpeed = 0.0;
		trigger.triggerPower = 0.99;
		
		trigger.motionSensitivity = 2;
		
		Trigger trigger2(particleSystemManager);
		trigger.type = TRIGGER_TYPE_FIRE_ON_MOTION;
		trigger2.restoreSpeed = 0.0;
		//trigger.motionTriggerLevel = 1;
		
		trigger2.addRocketSettings(RocketFountain()); 
		
		TriggerPattern pattern;
		trigger.radius = 10;
		pattern.addTrigger(trigger,0.5);
		trigger2.radius = 5;
		pattern.addTrigger(trigger2,0.5);
		pattern.addTrigger(trigger2,0.5);
		pattern.addTrigger(trigger2,0.5);
	
		addTriggerPattern(pattern);
		
		TriggerPattern pattern2;
		trigger.radius = 10;
		pattern2.addTrigger(trigger,0.5);
		trigger2.radius = 5;
		pattern2.addTrigger(trigger2,0.5);
		addTriggerPattern(pattern2);
	
	}

};