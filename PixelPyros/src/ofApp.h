


#pragma once

#include "constants.h"

#include "ofMain.h"
#include "SceneManager.h"
#include "ParticleSystemManager.h"
#include "CameraManagerWarped.h"
#include "MotionManager.h"
#include "TriggerManager.h"

#include "LaserManager.h"
#include "ControlPanels.h"
#include "SoundPlayer.h"

#include "SceneSpace.h"
#include "SceneVectorizer.h"
#include "SceneIntro.h"
#include "SceneRetro.h"
#include "SceneRealistic.h"
#include "SceneCalibration.h"
#include "SceneSlideshow.h"
#include "SceneGame.h"
#include "SceneNadia.h"

#include "PyrosRenderer.h"

#include "QuadWarp.h"

#include "glut/glut.h"

#include "ofxOsc.h"

#include "ofShader.h"

#include "TextWriter.h"


#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_NSGL
#include "GLFW/glfw3native.h"

class ofApp :public ofBaseApp{
	
public:
	
	ofApp(): particleSystemManager(*ParticleSystemManager::instance()), triggerManager(*TriggerManager::instance()), soundPlayer(*SoundPlayer::instance()), laserManager(*LaserManager::instance()),
        parameterManager(*ParameterManager::instance()){
 		
 	};
	
	void setup();
	void update();
	void draw();
	void exit();
	void mousePressed( int x, int y, int button );
	void mouseMoved( int x, int y );
    void keyPressed( int key );
	void keyReleased( int key );
	
	void setupScenes();
	void initSounds();
	void calculateScreenSizes();
	void updateScreenSizes(); 
	void windowResized(int w, int h);

	
  	ParticleSystemManager& particleSystemManager;
	LaserManager& laserManager;
	SceneManager sceneManager;
	TriggerManager& triggerManager;

	CameraManagerWarped cameraManager;
	MotionManager motionManager;
	SoundPlayer& soundPlayer;
    ParameterManager& parameterManager;
    ControlPanels controlPanels;

	
	ofParameterGroup appParams; 
	ofParameter<float> timeSpeed;
	ofParameter<int> edgeBlendSize; 
	
	ofFbo fbo;
	bool useFbo;
	
	float lastUpdateTime;
	
	QuadWarp fboWarper1;
	QuadWarp fboWarper2;
	
	
	vector<ofRectangle> screens;
	
	
	//ofRectangle triggerArea;
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
	
	
    
private:
    
    // reverse top and bottom for osc slider
    ofShader shader;
    TextWriter textWriter;
    
    bool paused;
};

struct screenSortClass {
    bool operator()(ofRectangle a, ofRectangle b)
    {
        return a.x < b.x;
        }
} screenSort;
        