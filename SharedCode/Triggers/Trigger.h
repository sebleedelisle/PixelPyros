
#pragma once

#include "ofMain.h"
#include "TriggerSettings.h"
#include "TriggerRechargeSettings.h"


class Trigger {
	
	public :
	
	//static TriggerRendererBase * defaultRenderer;
	
	Trigger();
	bool update(float deltaTime);
	void draw();
	
	void start();
	void stop();
	
	void registerMotion(float unitValue);
	
	bool doTrigger();
	
	void copySettings(TriggerSettings* settings) ;
	
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
	
	
	
	//SETTINGS
	
	TriggerSettings* settings;
	TriggerRechargeSettings* rechargeSettings;
	
	
};