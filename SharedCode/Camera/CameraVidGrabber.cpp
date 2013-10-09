/*
 *  CameraVidGrabber.cpp
 *  PixelPhones
 *
 *  Created by Seb Lee-Delisle on 16/03/2012.
 *  Copyright 2012 seb.ly. All rights reserved.
 *
 */

#include "CameraVidGrabber.h"

bool CameraVidGrabber::setup(string _name, int width, int height, int framerate) {
	
	CameraWrapper::setup(_name, width, height, framerate);	
	
	if(!vidGrabber.initGrabber(width, height)) return false;
	vidGrabber.setDesiredFrameRate(framerate); 
	name = _name; 
    frameNum = 0; 
	
	baseVideo = &vidGrabber;
	
	return true;
   
}


bool CameraVidGrabber::videoSettings(){
	vidGrabber.videoSettings();
	return true;
	
}


