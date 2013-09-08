


#pragma once


#include "constants.h"

#include "ofMain.h"
#include "ofxFensterManager.h"
#include "SceneManager.h"
#include "SettingsManager.h"
#include "ParticleSystemManager.h"
#include "CameraManagerWarped.h"
#include "SoundPlayer.h"
#include "MotionManager.h"
#include "TriggerManager.h"
#include "ofxAutoControlPanel.h"
//
//#include "SceneSpace.h"
//#include "SceneTron.h"
//#include "SceneLaunch.h"
#include "SceneIntro.h"
//#include "SceneRetro.h"
//#include "SceneRealistic.h"
#include "SceneCalibration.h"
#include "SceneSlideshow.h"

#include "PyrosRenderer.h"

#include "QuadWarp.h"

#include "glut/glut.h"

#include "ofxOsc.h"

#include "ofShader.h"

#include "TextWriter.h"

class ofApp : public ofxFenster{
	
public:
	
	ofApp(): particleSystemManager(soundPlayer), sceneManager(particleSystemManager, triggerManager) {
		
	};
	
	void setup();
	void update();
	void draw();
	void exit(); 
	void mousePressed( int x, int y, int button );
	void mouseMoved( int x, int y );
	void keyPressed( int key );
	void keyReleased( int key );
	
	void setupControlPanel();
	void eventsIn(guiCallbackData & data);

	void setupScenes();
	void initSounds(); 
	
	
  	ParticleSystemManager particleSystemManager;
	SceneManager sceneManager;
	TriggerManager triggerManager;
	OscManager oscManager;
    SettingsManager settingsManager;
	CameraManagerWarped cameraManager;
	MotionManager motionManager;
	SoundPlayer soundPlayer;
	
	ofFbo fbo; 
	bool useFbo; 
	
	ofxAutoControlPanel gui; 
	
	float lastUpdateTime;
	
	QuadWarp fboWarper1;
	QuadWarp fboWarper2;
	
	//bool shiftPressed;
	
	ofRectangle triggerArea;
	float triggerAreaCentreY;
	float triggerAreaWidth;
	float triggerAreaHeight;
	float triggerSpacing;
	bool triggerShowDebug;
	bool showDiffImage;
	bool triggersDisabled;
	bool drawCameraIntoFBO;
	bool shiftPressed;
	
	PyrosRenderer renderer;
	
	
	
	float testValue; 
    
private:
    
    // reverse top and bottom for osc slider
    ofShader shader;
    TextWriter textWriter;
    
    bool paused;
};
