#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "LaserManager.h"
#include "Particle.h"

class ofApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	
	void exit();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
	
	LaserManager laserManager;
	deque <Particle> particles;

	

	void circleResolutionChanged(int & circleResolution);
	void ringButtonPressed();

	bool bHide;

	int particlesCreated ; 

	ofParameter<int> numParticles;
	ofxColorSlider color;
	ofParameter<float> particleFlicker;
	ofParameter<float> speed;
	float elapsedTime; 
	
	
	
	//ofxVec2Slider center;
	//ofxIntSlider circleResolution;
	ofxToggle showParticles;
	
	
	//ofxButton twoCircles;
	//ofxButton ringButton;
	//ofxLabel screenSize;

	ofxPanel gui;

	//ofSoundPlayer ring;
};

