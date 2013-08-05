/*
 *  CameraVidGrabber.h
 *  PixelPhones
 *
 *  Created by Seb Lee-Delisle on 16/03/2012.
 *  Copyright 2012 seb.ly. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "CameraWrapper.h"

class CameraVidGrabber : public CameraWrapper { 

	public :
	bool setup(string _name, int width = 640, int height = 480, int framerate =30);
	
	bool videoSettings(); 
	
	ofVideoGrabber vidGrabber; 
    
	
};