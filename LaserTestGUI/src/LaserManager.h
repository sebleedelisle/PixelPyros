//
//  LaserManager.h
//  LaserTest02
//
//  Created by Seb Lee-Delisle on 08/08/2013.
//
//

#pragma once

#include "ofxEtherdream.h"
#include <math.h>
#include "Quint.h"
#include "Quad.h"
#include "Cubic.h"
#include "CubicBezier.h"
#include "QuadWarp.h"
#include "ofxCv.h"
#include "LaserDot.h"
#include "ofxGui.h"


class LaserManager {

	public:
	
	LaserManager();
	
	void update(); 
	
	bool my_compare( ofPoint a, ofPoint b){
		return a.y < b.y;
	}
	
	void addLaserDot(const ofPoint& ofpoint, ofFloatColor colour, float intensity =1);
	void addLaserLine(const ofPoint&start, const ofPoint&end, ofFloatColor colour);
	void addLaserLineEased(const ofPoint&start, const ofPoint&end, ofFloatColor colour);
	void addLaserRect(const ofPoint&topLeft, const ofPoint&dimensions, ofFloatColor colour);
	void closeLaserLoop();
	void moveLaser(const ofPoint & target, bool alreadyWarped = false);
	void moveLaserToPointAndVel(const ofPoint& targetPos, const ofPoint& targetVel);
	
	void drawDots();
	
	void resetIldaPoints();
	void addIldaPoint(const ofPoint& p, ofFloatColor c);
	
	ofxIlda::Point ofPointToIldaPoint(const ofPoint& ofpoint, ofFloatColor colour);
	ofPoint ildaPointToOfPoint(const ofxIlda::Point& ildapoint);
	
	
	void connectToEtherdream();
	void disconnectFromEtherdream();
	bool toggleRegistration(); 
	
	
	void addDelayTest() ;

	
	vector <LaserDot> dots; 
	
	ofxEtherdream etherdream;
	
	ofFloatColor white;
	ofFloatColor black;
	
	ofPoint startPosition;
	ofPoint startVel;
	ofPoint currentPosition;
	ofPoint currentVel;
	
	float maxSpeed;
	float acceleration;
	
		int endCount;
	int blankCount;
	
	// overall brightness applied to any laser colour
	ofParameter<float> intensity;
	// allows you to shift the colour changes back or
	// forward to compensate for crap lasers
	ofParameter<int> colourChangeDelay;
	
	// how many blank points before and after drawing a dot
	ofParameter<int> dotPreBlank;
	ofParameter<int> dotPostBlank;
	// the number of points for a dot
	ofParameter<int> dotMaxPoints;
	
	// show the movement between shapes as a dotted red line
	ofParameter<bool> showMovePoints;
	// the speed for movement and 
	ofParameter<float> moveSpeed;
	ofParameter<float> movePointsPadding;
	ofParameter<bool> connectButton;
	ofParameter<string> etherdreamStatus; 
	
	ofParameterGroup p1, p2, p3;
	ofParameterGroup parameters;
	
	bool isConnected; 

	
	QuadWarp warp; 
	
	ofMesh previewMesh;
	ofPoint pmin;
	ofPoint pmax;
	
	int minPoints; 
	
	//bool laserDirty;
	bool showRegistration; 
	
	
	vector<ofxIlda::Point> ildaPoints;
	vector<ofPoint> ofPoints;
	
	float APP_WIDTH = ofGetWidth();
	float APP_HEIGHT = ofGetHeight();


};