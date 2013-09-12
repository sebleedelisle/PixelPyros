/*
 *  CameraManager.h
 *  PixelPhones
 *
 *  Created by Seb Lee-Delisle on 15/03/2012.
 *  Copyright 2012 seb.ly. All rights reserved.
 *
 */

#pragma once

#include "ofxLibdc.h"
#include "CameraWrapper.h"
#include "CameraVidGrabber.h"
#include "CameraFirewire.h"
#include "CameraVidPlayer.h"
//#include "CameraCanon.h"

#include "ofxAutoControlPanel.h"

#define CAPTURE_FPS 30

class CameraManager : public ofBaseDraws{ 
	public : 
	
	CameraManager(); 
	void init(); 
	bool update(); 
	void draw(float x, float y); 
	void draw(float x, float y, float w, float h); 
	ofPixelsRef getPixelsRef();
	
	void setAnchorPercent(float xPct, float yPct){};
	void setAnchorPoint(float x, float y){};
	void resetAnchor(){};
	
	
	float getWidth(); 
	float getHeight(); 
	
	void videoSettings(); 
	
	void close(); 
	
	void next(); 
	bool changeCamera(string camname);
	virtual bool changeCamera(CameraWrapper* cam);
	
	void initControlPanel(ofxAutoControlPanel& gui); 
	void guiEventsIn(guiCallbackData & data);
    
    void beginCapture();
    void endCapture();
	
	guiTypeToggle* toggleShowUSBControls;
	guiTypeDrawable* cameraPreview;
	
	CameraVidPlayer * addVidPlayer(string filename, int width = 1024, int height = 768);
	CameraWrapper* camera; 
	vector <CameraWrapper*> cameras; 	
	
	CameraVidGrabber*	cameraVidGrabber; 
	CameraFirewire*		cameraFirewire; 
	CameraVidPlayer*	cameraVidPlayer;
	//CameraCanon*		cameraCanon;
	
	int gain; 
	int gamma;
	int shutter; 
	int brightness;
	
    bool capturing;
    //float captureInterval;
    unsigned long framesCaptured;
    string captureBase;
    string captureTimestamp;
    
private:
    
    float captureDelta;
    
    void captureFrame();
    string getCaptureFilename();
};
