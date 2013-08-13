#pragma once

#include "ofMain.h"

#include "ofxTSP.h"

#define COUNT 11
#define WIDTH 600

//using namespace ofxTSP;

class testApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	
	void keyPressed  (int key);
	void solve();

	vector<ofVec2f> positions;

	ofxTSP::Problem problem;
	ofxTSP::BruteForce solver;
	ofxTSP::Route solvedRoute; //inherits vector<int>
};
