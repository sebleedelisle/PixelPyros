//
//  Warper.h
//  HomographyExample
//
//  Created by Seb Lee-Delisle on 07/08/2012.
//  Copyright (c) 2012 seb.ly. All rights reserved.
//

#pragma once 

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxXmlSettings.h"
#include "matrix_funcs.h"

using namespace ofxCv;
using namespace cv;

class Warper { 

	public : 
	
	Warper();
	
	bool init(float srcwidth, float srcheight, float dstwidth, float dstheight, string label="defaultWarp");
	
	bool update(ofPixels& sourcePixels);
	
	
	void updateWarpedImage(ofPixelsRef sourcePixels);
	
	//void setSourceImage(ofImage& img) ;
	
	void draw();
	
	void mousePressed(ofMouseEventArgs &e);
	void mouseDragged(ofMouseEventArgs &e);
	void mouseReleased(ofMouseEventArgs &e);
	
	bool hitTestPoints(vector<ofVec2f>& points, ofVec2f& checkpoint);
	bool hitTestPoint(ofVec2f& points, ofVec2f& checkpoint);
	void drawPoints(vector<ofVec2f>& points, ofColor colour = ofColor::white);
	void drawPoint(ofVec2f& point, ofColor colour = ofColor::white);
	void apply();

	bool loadSettings();
	bool saveSettings(); 
	
	void showGui();
	void hideGui();
	bool toggleGui();
		
	//ofImage* srcImage; 
	ofImage warpedImage; 
	string  settingsFileLabel; 
	
	float srcWidth; 
	float srcHeight; 
	float dstWidth; 
	float dstHeight; 
	
	float dstPreviewScale; 
	
	vector <ofVec2f> srcVecs, dstVecs;
	ofVec2f dstCenterPoint;

	cv::Mat homography;
	cv::Mat inverseHomography;
	
	bool guiVisible; 
	bool changed; 
	bool movingPoint; 
	bool autoSave; 
	ofVec2f *curPoint;
	ofVec2f clickOffset;
	ofVec2f dragStartPoint;
	
	GLfloat _glWarpMatrix[16];
	double _warpMatrix[3][3];


	
	bool verbose;
	

};