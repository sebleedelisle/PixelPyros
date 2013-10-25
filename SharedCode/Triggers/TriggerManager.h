//
//  TriggerManager.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 21/08/2013.
//
//

#pragma once
#include "Trigger.h"
#include "TriggerPattern.h"
#include "ofxCv.h"
#include "MotionManager.h"
#include "constants.h"

class TriggerManager {
	
	public :
	
	static TriggerManager * instance();
	static TriggerManager * triggerManager;
	static const int TRIGGER_MODE_MANUAL = 0;
	static const int TRIGGER_MODE_AUTO = 1;

	
	TriggerManager();
	void initParams();
    
	bool update(float deltaTime);
	void draw();
	
	//void updateTriggerSettings(ofRectangle triggerarea, float spacing);
	void setShowTriggerDebug(bool & debug);
	void setTriggersDisabled(bool disabled);
    void setDisplaySize( float width, float height );
	void toggleDebug(); 
	
	void updateMotion(MotionManager& motionManager, cv::Mat homography);
	
	void updateLayout();
	void setPattern(TriggerPattern tp);
	
	void mouseMoved(int x, int y, ofRectangle previewRect);
	void triggerParamChanged(float & value);
	void triggerParamIntChanged(int &value);
	void triggerModeChanged(int &value);
    void updateTriggerValues();
	
	void emptyTriggers();
    
	TriggerPattern triggerPattern;
	
	ofRectangle triggerArea;
	//bool active;
	//bool triggerDebug;
	bool triggersDisabled;
    float displayWidth;
    float displayHeight;
	
	vector <Trigger*> triggers;
	//vector <TriggerBase*> triggersLeft;
	//vector <TriggerBase*> triggersRight;
	
	int triggerPatternOffset;
	
	float minimumSpacing;
	int triggerCount; // keeps track of the number of triggers - needed? 

		
	float rectanglePreviewBrightness; 
	
	ofParameter<int> triggerMode;
	ofParameter<string> triggerModeString; 
    ofParameter<float> triggerAreaWidthParam;
    ofParameter<float> triggerAreaBottomParam;
    ofParameter<float> triggerAreaTopParam;
    ofParameter<int> triggerNumParam;
	ofParameter<float> triggerSampleSizeParam; 
	ofParameter<float> triggerOscillationParam;
    ofParameter<bool> triggerDebugMode;
	
	
	// the number of vertical motion samples
	ofParameter<int> numVertSamples; // 10
	// the speed that the triggers move towards motion
	ofParameter<float> moveTowardMotionSpeed; // 0.05
	// the speed that the trigger reset back to the top (pixels per second)
	ofParameter<float> moveHomeSpeed; // 20
	// the minimum motion to move towards  - 0 > 255
	ofParameter<int> motionTargetThreshold; // 50
	// the speed that the motion samples reset
	ofParameter<float> motionSamplesResetSpeed;  // 0.99; 
	// a scalar to adjust the amount of motion to add to the samples
	ofParameter<float> motionMultiplier; // 0.1
	ofParameter<float> multiSampleSize; 
	
	
    ofParameterGroup parameters;
};