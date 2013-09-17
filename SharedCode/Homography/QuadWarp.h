


#pragma once

#include "ofMain.h"
#include "glut/glut.h"
#include "ofxXMLSettings.h"
#include "ofxCv.h"

using namespace ofxCv;
using namespace cv;
using namespace std;

class QuadWarp {
	
	public :
	
	QuadWarp (string saveLabel = "default");
	
	void draw();
	void draw(bool lockAxis);
	
	void mousePressed(ofMouseEventArgs &e);
	void mouseDragged(ofMouseEventArgs &e);
	void mouseReleased(ofMouseEventArgs &e);
	float dragSpeed = 0.1;
	
	bool hitTestPoints(vector<ofVec2f>& points, ofVec2f& point);
	void drawPoints(vector<ofVec2f>& points, ofColor colour = ofColor::white);

	
	void setDstPoint(int index, ofVec3f point);
	void setSrcPoint(int index, ofVec3f point);
	
	ofVec3f getWarpedPoint(ofVec3f point);
	ofVec3f getUnWarpedPoint(ofVec3f point);
	void updateHomography();
	
	// applies the distortion matrix to the current draw state
	void apply(ofRectangle sourceRect);
	
	
	bool loadSettings();
	void saveSettings();

	
	bool visible;
	float lastMousePress; 
	
	vector <ofVec3f> srcPoints;
	vector <ofVec3f> dstPoints;
	//vector <ofVec3f> defaultDstPoints;
	
	cv::Mat homography;
	cv::Mat inverseHomography;
	
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

std::ostream& operator<<(std::ostream& stream, const QuadWarp& warp);
std::istream& operator>>(std::istream& stream, QuadWarp& warp);
