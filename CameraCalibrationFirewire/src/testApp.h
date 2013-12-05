#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxLibdc.h"

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	
	//ofVideoGrabber cam;
	ofxLibdc::Grabber cam;
	ofImage undistorted;
	ofPixels previous;
	ofPixels diff;
	float diffMean;
	
	float lastTime;
	bool active;
	
	ofxCv::Calibration calibration;
};
