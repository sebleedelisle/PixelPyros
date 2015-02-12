
#pragma once

#include "ofMain.h"
#include "ofxNSWindowApp.h"
#include "ofxGui.h"
#include "ofApp.h"

class controlWindow : public ofxNSWindowApp {

protected:
    ofxPanel gui;
	ofxPanel laserGui;
    ofxToggle toggleDemo;
    ofxSlider<float> sliderDemo;
    ofxSlider<int> intSliderDemo;
    ofxColorSlider colorSliderDemo;
    ofxButton buttonDemo;
    ofxLabel labelDemo;
    ofApp* mainApp;
    
    ofParameter<int> numParticles;
	ofParameter<float> particleFlicker;
	ofParameter<float> speed;
    
	ofxColorSlider color;
    ofxToggle showParticles;
	ofxToggle showRectangle;

    LaserManager& laserManager;

public:
	controlWindow(ofApp*);
	
	void setup();
	void update();
	void draw();
    void exit();

	void keyPressed(int key);
	void keyReleased(int key);
	
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased();
	void mouseReleased(int x, int y, int button);
    
    void fullscreenButtonPressed();
	
	void mouseScrolled(float x, float y);

};

