#pragma once

#include "ofMain.h"
#include "ofxCv.h"

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed( int key );
	
	ofVec2f undistortPoint(ofVec2f point);
	
	ofVideoGrabber cam;
	ofImage undistorted;
	ofxCv::Calibration calibration;
	
	bool doUndistortion = true;
	
};
