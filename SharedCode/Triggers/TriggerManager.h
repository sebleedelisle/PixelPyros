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
	
	float minimumSpacing;
	int triggerCount;

    ofParameter<float> triggerAreaWidthParam;
    ofParameter<float> triggerAreaHeightParam;
    ofParameter<float> triggerAreaCenterYParam;
    ofParameter<float> triggerSpacingParam;
	ofParameter<float> triggerOscillationParam;
    ofParameter<bool> triggerDebugMode;
    ofParameterGroup parameters;
};