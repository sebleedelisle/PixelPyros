
#pragma once

#include "ParticleSystem.h"
#include "PhysicsObject.h"
#include "RocketSettings.h"
#include "ParticleSystemManager.h"

#include "TriggerBase.h"

class TriggerSimple : public TriggerBase {
	
	public :
	
	TriggerSimple(ParticleSystemManager & psm, float triggerRadius = 5);
	virtual bool update(float deltaTime);
	virtual void draw();
	
	virtual void start();
	virtual void stop();
	
	virtual void registerMotion(float unitValue);
	
	virtual bool doTrigger();
	
	
	virtual TriggerSimple* clone() const{
		//cout << "clone TriggerRocket"<< endl;
		return new TriggerSimple( *this );
	}
	
	//ofColor colour;
	float hue;
	float saturation; 
	// for the debug data
	deque <float> motionValues;
	int motionValueCount;
	float lastUpdate;

	// for the spinny orb
	float rot1, rot2, rot3;
	float vel1, vel2, vel3;

	
	
};