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
#include "LaserShape.h"
#include "LaserCircle.h"
#include "LaserSpiral.h"
#include "LaserPolyline.h"
#include "LaserLine.h"
#include "ofxGui.h"
#include "ofMain.h"
#include "constants.h"
#include "RectangleUI.h"
#include "ofxNetwork.h"

class LaserManager {

	public:
	
	static LaserManager * instance();
	static LaserManager * laserManager;

	
	LaserManager();
	
	void setup(int width, int height);
    void update();
	void draw();
	
	void renderPreview();
	void renderLaserPath(ofRectangle previewRectangle, bool overrideSettings);
	
	//void updatePreviewScreenRect(ofRectangle pscreenrect);

	bool my_compare( ofPoint a, ofPoint b){
		return a.y < b.y;
	}
	
	void addLaserDot(const ofPoint& ofpoint, ofFloatColor colour, float intensity =1);
	
	void addLaserCircle(const ofPoint& ofpoint, ofFloatColor colour, float radius, float intensity =1);
	
	void addLaserSpiral(const ofPoint& position, ofFloatColor col, float rad1,float rad2, float fadeoutpoint = 1,  float intens = 1);
	
	void addLaserPolyline(const ofPolyline& line, float intens = 1);

	//void addLaserLine(const ofPoint&start, const ofPoint&end, ofFloatColor colour);
	void addLaserLineEased(const ofPoint&start, const ofPoint&end, ofFloatColor colour);
	//void addLaserRect(const ofPoint&topLeft, const ofPoint&dimensions, ofFloatColor colour);
	void addLaserRectEased(const ofPoint&topLeft, const ofPoint&dimensions, ofFloatColor colour);
	//void closeLaserLoop();
	void moveLaser(const ofPoint & target);
	//void moveLaserToPointAndVel(const ofPoint& targetPos, const ofPoint& targetVel);
	
	void drawShapes();
	
	void drawLaserLine(LaserLine& line);
	void drawLaserPolyline(LaserPolyline& laserPolyline);
	void drawLaserCircle(LaserCircle& circle);
	void drawLaserDot(LaserDot& dot);
	void drawLaserSpiral(LaserSpiral& spiral);
	
	void resetIldaPoints();
	void addIldaPoint(ofPoint p, ofFloatColor c, float pointIntensity = 1);
	
	ofxIlda::Point ofPointToIldaPoint(const ofPoint& ofpoint, ofFloatColor colour);
	ofPoint ildaPointToOfPoint(const ofxIlda::Point& ildapoint);
	
	vector<float> getPointsAlongDistance(float distance, float acceleration, float maxspeed);
	
	
	
	void connectButtonPressed();
	
	void connectToEtherdream();
	void disconnectFromEtherdream();
	bool toggleRegistration();
	
	
	void addDelayTest() ;
	
	void sendPointsTCP(vector<ofxIlda::Point>& points); 
	string ildaPointToString(ofxIlda::Point& p);
	
	vector <LaserShape*> shapes;
	
	ofxEtherdream etherdream;
	
	ofFloatColor white;
	ofFloatColor black;
	
	ofSoundPlayer beep; 
	
	ofPoint currentPosition;
	
	ofxButton connectButton;
	ofParameter<string> etherdreamStatus;
	ofParameter<int> pps; 
	ofParameter<bool> showWarpPoints;
	ofParameter<bool> flipX;
	ofParameter<bool> flipY;
	ofParameter<bool> showRegistration;
	ofParameter<bool> showMaskRectangle;
	ofParameter<bool> showSyncTest;
	ofParameter<bool> showLaserPath;
	ofParameter<bool> renderLaserPreview;
	
	// overall brightness applied to any laser colour
	ofParameter<float> intensity;
	// allows you to shift the colour changes back or
	// forward to compensate for crap lasers
	ofParameter<int> colourChangeDelay;
	
	// how many blank points before and after drawing a dot
	ofParameter<int> shapePreBlank;
	ofParameter<int> shapePostBlank;
	// the number of points for a dot
	ofParameter<int> dotMaxPoints;
	
	// show the movement between shapes as a dotted red line
	ofParameter<bool> showMovePoints;
	
	// the speed for movement and acceleration
	ofParameter<float> moveSpeed;
	ofParameter<int> movePointsPadding;
	
	ofParameter<float> speedLine;
	ofParameter<float> accelerationLine;
	
	ofParameter<float> overlapCircle; 
	
	ofParameter<float> speedCircle;
	ofParameter<float> accelerationCircle;
	
	ofParameter<float> speedEasedLine;
	ofParameter<int> paddingEasedLine;
	
	ofParameter<float>spiralSpacing; 
	
	ofxTCPServer TCP;
	bool useTCP; 

	ofParameterGroup p1, p2, p3;
	ofParameterGroup parameters;
    ofParameterGroup calibrationParameters;

    QuadWarp warp;
	
	bool shouldBeConnected;
	string lastState; 
	
	RectangleUI maskRectangle; 
	
	//ofMesh previewMesh;
	ofMesh pathMesh;
	ofPoint pmin;
	ofPoint pmax;
	
	int minPoints;
	int restartCount; 
	
	//bool laserDirty;
	
	
	vector<ofxIlda::Point> ildaPoints;
	//vector<ofPoint> ofPoints;
	
	float appWidth;
	float appHeight;
	
	ofImage pointPreviewImage;


};