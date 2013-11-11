
#pragma once

#include "ofMain.h"
#include "TriggerSettings.h"
#include "TriggerRechargeSettings.h"


class Trigger {
	
	public :
	
	//static TriggerRendererBase * defaultRenderer;
	
	Trigger();
	bool update(float deltaTime, ofRectangle& triggerArea);
	void draw(ofRectangle area, int motionTargetThreshold);
	
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
	
	// a vector of motion levels across the height of the trigger
	vector<float>vertMotionSamples;
	float sampleBrightness; 
	
	float lastTriggerTime;
	
	// scale is just used to keep track of whether we're growing or shrinking
	float scale;
	float lastScale;
		
	ofVec3f pos;
	//ofVec3f targetPos;
	//ofVec3f vel;
	
	bool fixedPosition;
	
	//vector <RocketSettings> rocketSettings;
	
	//ParticleSystemManager & particleSystemManager;
	
	bool showDebugData;

	float elapsedTime;
	float deltaTime;
	
	// for the debug data
	deque <float> motionValues;
	int motionValueCount;
	float lastUpdate;
	
	// angle
	float angle;
	int rotateDirection; 
	int triggerCount;
	
	ofImage flashImage;
	
	map<string, float> values; 
	
	
	//SETTINGS
	
	TriggerSettings* settings;
	TriggerSettings* lastSettings;
	TriggerRechargeSettings* rechargeSettings;
	
	
};