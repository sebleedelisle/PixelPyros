
#pragma once

#include "ofMain.h"
#include "TriggerSettings.h"
#include "TriggerRendererBase.h"

class Trigger {
	
	public :
	
	Trigger();
	bool update(float deltaTime);
	void draw();
	
	void start();
	void stop();
	
	void registerMotion(float unitValue);
	
	bool doTrigger();
	
	void copySettings(const TriggerSettings& settings) ;
	
	
	/*
	virtual Trigger* clone() const{
		//cout << "clone TriggerRocket"<< endl;
		return new Trigger( *this );
	}*/
	
	float unitPower;
	
	bool active;
	bool stopping;
	bool disabled;
	
	// to create a trigger that is one shot, set restoreSpeed
	// to 0.
	
	// motionLevel is the accumulated motion
	float motionLevel;
	
	float lastTriggerTime;
	
	// scale is just used to keep track of whether we're growing or shrinking
	float scale;
	//float targetScale;
	// radius is the graphical size and also the motion area size
	float radius;
	
	
	ofVec3f pos;
	bool fixedPosition;
	
	//vector <RocketSettings> rocketSettings;
	
	//ParticleSystemManager & particleSystemManager;
	
	bool showDebugData;

	float elapsedTime;

	
	// for the debug data
	deque <float> motionValues;
	int motionValueCount;
	float lastUpdate;
	
	TriggerRendererBase * renderer;
	TriggerableBase * triggerable;
	
	TriggerRendererBase defaultRenderer;
	TriggerableBase defaultTriggerable;
	
	TriggerSettings defaultSettings; 
	
	/*
	// for the spinny orb
	float rot1, rot2, rot3;
	float vel1, vel2, vel3;
	*/
	
	
	
	//SETTINGS
	
	//amount per second to take away from the accumulated motion
	float motionDecay;
	
	// a scalar that multiplies the motion level to add to the
	// unitPower
	float motionSensitivity;
	
	// set restoreSpeed to 0 to make it a single shot trigger
	float restoreSpeed;
	
	
	// motionTriggerLevel is the amount of motion needed to make something happen
	float motionTriggerLevel;
	
	// the amount of power taken away when it triggers
	float triggerPower;
	
	// minimum time between triggers
	float minTriggerInterval;
		
	//ofColor colour;
	float hue;
	float saturation;
	

	
	
};