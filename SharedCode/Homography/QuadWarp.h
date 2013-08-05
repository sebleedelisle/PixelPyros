


#pragma once

#include "ofMain.h"
#include "glut/glut.h"
#include "ofxXMLSettings.h"

class QuadWarp {
	
	public :
	
	QuadWarp (string saveLabel = "default");
	
	void draw(bool lockAxis = false);
	
	void mousePressed(ofMouseEventArgs &e);
	void mouseDragged(ofMouseEventArgs &e);
	void mouseReleased(ofMouseEventArgs &e);
	
	bool hitTestPoints(vector<ofVec2f>& points, ofVec2f& point);
	void drawPoints(vector<ofVec2f>& points, ofColor colour = ofColor::white);

	
	void setDstPoint(int index, ofVec3f point, bool setAsDefault = true);
	
	// applies the distortion matrix to the current draw state
	void apply(ofRectangle sourceRect);
	
	
	bool loadSettings();
	void saveSettings();

	
	bool visible;
	float lastMousePress; 
	
	vector <ofVec3f> dstPoints;
	vector <ofVec3f> defaultDstPoints;
	
	ofColor pointColour;
	
	GLfloat _glWarpMatrix[16];
	double _warpMatrix[3][3];
	
	
	//ofVec3f *curPoint;
	int curPointIndex; 
	
	ofVec3f clickOffset;
	ofVec3f dragStartPoint;
	
	
	ofRectangle bounds;
	string label;
	float pointRadius;
	
	
};