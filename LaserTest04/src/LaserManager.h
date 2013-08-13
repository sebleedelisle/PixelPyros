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
	
	int colourChangeDelay; 

	int endCount;
	int blankCount;
	
	QuadWarp warp; 
	
	ofMesh previewMesh;
	ofPoint pmin;
	ofPoint pmax;
	int previewPointIndex;
	
	int minPoints; 
	
	//bool laserDirty;
	bool showRegistration; 
	
	
	vector<ofxIlda::Point> ildaPoints;
	vector<ofPoint> ofPoints;
	
	float APP_WIDTH = ofGetWidth();
	float APP_HEIGHT = ofGetHeight();


};