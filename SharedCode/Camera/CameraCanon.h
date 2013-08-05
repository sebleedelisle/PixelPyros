//
//  CameraFirewire.h
//  PixelPhones
//
//  Created by Seb Lee-Delisle on 26/04/2012.
//  Copyright (c) 2012 seb.ly. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "CameraWrapper.h"

#include "ofxAutoControlPanel.h"

#include "Canon.h"

class CameraCanon : public CameraWrapper{
	
	
    public :
	bool setup(string _name, int width = 640, int height = 480, int framerate =30);
	bool update();
	
	bool videoSettings();
	
	void setGain(int value);
	int getGain();
	void setShutter(int value);
	int getShutter();
	
	int getGamma();
	void setGamma(int value);
	int getBrightness();
	void setBrightness(int value);
	
	void initControlPanel(ofxAutoControlPanel& gui, float w);
	
    //ofxLibdc::Grabber camera;
	
	roxlu::Canon canon;

	
	
	
	
};