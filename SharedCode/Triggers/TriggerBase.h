//
//  TriggerBase.h
//  ParticlePlay4
//
//  Created by Seb Lee-Delisle on 02/08/2012.
//  Copyright (c) 2012 seb.ly. All rights reserved.
//

#pragma once

#include "ParticleSystem.h"
#include "PhysicsObject.h"
#include "RocketSettings.h"
#include "ParticleSystemManager.h"

typedef enum {
	TRIGGER_TYPE_FIRE_ON_MOTION,
	TRIGGER_TYPE_FIRE_ON_CHARGE
	
} TriggerType;

class TriggerBase {
	
	public :
	
	TriggerBase(ParticleSystemManager & psm, float triggerRadius = 5) : particleSystemManager(psm){
		typeLabel = "TriggerBase";
		fixedPosition = false;
		radius = triggerRadius;
	};
	
	virtual TriggerBase* clone() const=0;
	
	virtual bool update(float deltaTime) =0;
	virtual void draw() = 0;
	
	virtual void start() = 0;
	virtual void stop() = 0;
	
	virtual void registerMotion(float unitValue) = 0;
	
	//virtual TriggerBase* clone() const = 0;
	virtual bool doTrigger() = 0;
	
	TriggerType type;
	
	bool active;
	bool stopping;
	bool disabled;
	
	// to create a trigger that is one shot, set restoreSpeed
	// to 0. 
	
	// motionLevel is the accumulated motion
	float motionLevel;
	
	//amount per second to take away from the accumulated motion
	float motionDecay;
	
	// a scalar that multiplies the motion level to add to the
	// unitPower
	float motionSensitivity;
	
	// set restoreSpeed to 0 to make it a single shot trigger
	float restoreSpeed;
	
	float unitPower;
	
	// triggerLevel is the amount of unitPower needed to make something happen
	float triggerLevel;
	
	// the amount of power taken away when it triggers
	float triggerPower;
	
	// minimum time between triggers
	float minTriggerInterval;
	
	float lastTriggerTime;
	
	// scale is just used to keep track of whether we're growing or shrinking
	float scale;
	//float targetScale;
	// radius is the graphical size and also the motion area size
	float radius;
	
	
	ofVec3f pos;
	bool fixedPosition; 
	
	//vector <RocketSettings> rocketSettings;
	
	ParticleSystemManager & particleSystemManager;
	
	bool showDebugData;
	
	
	
	float elapsedTime;
	
	
	string typeLabel;
	
};