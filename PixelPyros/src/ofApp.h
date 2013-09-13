


#pragma once


#include "constants.h"

#include "ofMain.h"
#include "SceneManager.h"
#include "SettingsManager.h"
#include "ParticleSystemManager.h"
#include "CameraManagerWarped.h"
#include "MotionManager.h"
#include "TriggerManager.h"
#include "ofxAutoControlPanel.h"

#include "LaserManager.h"
#include "ControlPanels.h"
#include "SoundPlayer.h"
#include "Sequencer.h"

//
//#include "SceneSpace.h"
#include "SceneVectorizer.h"
//#include "SceneLaunch.h"
#include "SceneIntro.h"
#include "SceneRetro.h"
//#include "SceneRealistic.h"
#include "SceneCalibration.h"
#include "SceneSlideshow.h"
#include "SceneNadia.h"

#include "PyrosRenderer.h"

#include "QuadWarp.h"

#include "glut/glut.h"

#include "ofxOsc.h"

#include "ofShader.h"

#include "TextWriter.h"

class ofApp :public ofBaseApp{
	
public:
	
	ofApp(): particleSystemManager(*ParticleSystemManager::instance()), triggerManager(*TriggerManager::instance()), soundPlayer(*SoundPlayer::instance()), laserManager(*LaserManager::instance()),
        parameterManager(*ParameterManager::instance()), sequencer(&sceneManager){
 		
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
	
//    void mousePressed(ofMouseEventArgs &e);
//	void mouseDragged(ofMouseEventArgs &e);
//	void mouseReleased(ofMouseEventArgs &e);
//	void mouseMoved(ofMouseEventArgs &e);
	
  	ParticleSystemManager& particleSystemManager;
	LaserManager& laserManager;
	SceneManager sceneManager;
	TriggerManager& triggerManager;
	OscManager oscManager;
    SettingsManager settingsManager;
	CameraManagerWarped cameraManager;
	MotionManager motionManager;
	SoundPlayer& soundPlayer;
    ParameterManager& parameterManager;
    ControlPanels controlPanels;
	Sequencer sequencer; 
	
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
    bool altPressed;
	
	PyrosRenderer renderer;
	
	
	
	float testValue;
    
private:
    
    // reverse top and bottom for osc slider
    ofShader shader;
    TextWriter textWriter;
    
    bool paused;
};
