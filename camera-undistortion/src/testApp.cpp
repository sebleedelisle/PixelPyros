#include "testApp.h"

using namespace ofxCv;
using namespace cv;

void testApp::setup() {
	ofSetVerticalSync(true);
	cam.initGrabber(640, 480);
	calibration.setFillFrame(true); // true by default
	calibration.load("mbp-2011-isight.yml");
	imitate(undistorted, cam);
}

void testApp::update() {
	cam.update();
	if(cam.isFrameNew()) {
		calibration.undistort(toCv(cam), toCv(undistorted));
		undistorted.update();
	}
}

void testApp::draw() {
	ofSetColor(255);
	cam.draw(0, 0);
	if(doUndistortion) undistorted.draw(640, 0);
	else cam.draw(640, 0);
	
	ofNoFill();
	
	ofVec2f mousePos((float)ofGetMouseX(), (float)ofGetMouseY());
	ofCircle(mousePos , 10);
	ofVec2f distortedPos = calibration.undistort(mousePos);
	
	ofCircle(distortedPos * ofVec2f(640,480) + ofVec2f(320,240), 8);
	
	
	for(int x = 0; x<=10; x++) {
		for(int y = 0; y<=10; y++) {
			
			ofVec2f p1(x*64,y*48);
			ofVec2f p2 = p1;
			p2.x+=64;
			ofVec2f p3 = p1;
			p3.y+=48;
			
			if(x<10) ofLine(p1, p2);
			if(y<10) ofLine(p1, p3);
			
			ofPushMatrix();
			ofTranslate(640,0);
			
//			p1 = p1 / ofVec2f(640,640) - ofVec2f(0.5,0.5);
//			p2 = p2 / ofVec2f(640,640) - ofVec2f(0.5,0.5);
//			p3 = p3 / ofVec2f(640,640) - ofVec2f(0.5,0.5);
//			
			if(x<10)ofLine(undistortPoint(p1 ), undistortPoint((p2)));
			if(y<10)ofLine(undistortPoint(p1), undistortPoint((p3)));
			
			ofPopMatrix();
			
			
		}
	}
	
}

ofVec2f testApp::undistortPoint(ofVec2f point) {
	
	//point = point / ofVec2f(640,640) - ofVec2f(0.5,0.5);

	ofVec2f undistortedPoint = calibration.undistort(point);
	undistortedPoint *= ofVec2f(640,640);
	undistortedPoint += ofVec2f(320,240);
	return undistortedPoint;
	
}


void testApp::keyPressed(int key) {
	doUndistortion = !doUndistortion;
}
