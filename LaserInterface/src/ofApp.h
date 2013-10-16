#pragma once

#include "ofMain.h"
#include "ofxEtherdream.h"
#include "ofxNetwork.h"

class ofApp : public ofBaseApp{
	public:
	
	void setup();
	void update();
	void draw();
	void exit(); 
	
	void keyPressed(int key);

	bool connectToServer();
	ofxIlda::Point getPointFromString(string str); 
	
	ofxEtherdream etherdream;
	ofxTCPClient tcpClient;
	
	int lastConnectionAttemptTimeMils;
	int timeSinceLastConnectionAttemptMils;
	
	vector<ofxIlda::Point> points;
	vector<ofxIlda::Point> nextpoints;
	
	
};