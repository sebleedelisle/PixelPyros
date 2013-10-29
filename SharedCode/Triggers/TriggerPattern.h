//
//  Pattern.h
//  ParticlePlay5
//
//  Created by Seb Lee-Delisle on 20/08/2012.
//
//

#pragma once

#include "Trigger.h"
#include "TriggerSettings.h"
#include "TriggerSettingsRocket.h"
#include "TriggerSettingsRocketOrb.h"

typedef enum {
	TRIGGER_ARRANGE_MIRROR,
	TRIGGER_ARRANGE_DISTRIBUTE
} TriggerArrangeMode;

class TriggerPattern  {

	public :
	
	TriggerPattern(string patternname = "none"){
		arrangeMode = TRIGGER_ARRANGE_MIRROR;
		name = patternname; 
	};
	
	TriggerPattern(TriggerSettings* trigger){
		addTriggerSettings(trigger);
		arrangeMode = TRIGGER_ARRANGE_MIRROR;
	};
	
	TriggerPattern(vector<TriggerSettings*> triggers){
		for(int i = 0; i<triggers.size(); i++) {
			addTriggerSettings(triggers[i]);
		}
		arrangeMode = TRIGGER_ARRANGE_MIRROR;
	};
	
	//template <typename T>
	void addTriggerSettings(TriggerSettings* trigger){
		triggers.push_back(trigger);
	}
	/*
	void addTriggerSettings(){
		//triggers.push_back(trigger);
	}*/
	
	TriggerSettingsRocket* addRocketTrigger(RocketSettings* rocketSettings) {
		
		TriggerSettingsRocket* ts = new TriggerSettingsRocketOrb();
		// TODO - THIS IS BAD - should store these pointers somewhere and clear
		// them later.
		
		//TriggerableRocket* tr = new TriggerableRocket();
		ts->addRocketSettings(rocketSettings);
		
		addTriggerSettings(ts);
		
		return ts;
	}

	vector <TriggerSettings*> triggers;
	
	TriggerArrangeMode arrangeMode;
	
	string name; 
	
	// TODO ADDITIONAL STUFF THAT TRIGGER PATTERN NEEDS
	// Mirrored - on by default - what else? specific positions? 
	// auto-rotate - triggers should rotate to give everyone a try
	
	// probably don't need this in future, just helps me test.
	//TriggerableBase defaultTriggerable;

};
