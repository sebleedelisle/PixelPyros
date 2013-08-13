#pragma once

#include "ofMain.h"
#include "ofxEtherdream.h"
#include <math.h>
#include "Quint.h"
#include "Cubic.h"
#include "CubicBezier.h"

#include <algorithm> 
class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    
    bool my_compare( ofPoint a, ofPoint b){
		return a.y < b.y;
	}
	
	void addLaserDot(const ofPoint& ofpoint, ofFloatColor& colour);
	void addLaserLine(const ofPoint&start, const ofPoint&end, ofFloatColor& colour);

	void closeLaserLoop();
	void moveLaserQuintic(const ofPoint & start, const ofPoint & end);
	void moveLaserToPointAndVel(const ofPoint& targetPos, const ofPoint& targetVel);
	
	void resetIldaPoints(); 
	void addIldaPoint(const ofPoint& p, ofFloatColor& c);

	ofxIlda::Point ofPointToIldaPoint(const ofPoint& ofpoint, ofFloatColor& colour);
	ofPoint ildatPointToOfPoint(const ofxIlda::Point& ildapoint); 
	
	
	ofxEtherdream etherdream;
	
	ofFloatColor white;
	ofFloatColor black;
	
	
	ofPoint startPosition;
	ofPoint startVel; 
	ofPoint currentPosition;
	ofPoint currentVel; 
	
	int endCount;
	int blankCount;
	
	ofMesh previewMesh; 
	ofPoint pmin;
	ofPoint pmax;
	int previewPointIndex;
	
	bool laserDirty; 


	vector<ofxIlda::Point> ildaPoints;
	vector<ofPoint> ofPoints; 

};
