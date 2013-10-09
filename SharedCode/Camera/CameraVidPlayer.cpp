//
//  CameraVidPlayer.cpp
//  PixelPhones
//
//  Created by Seb Lee-Delisle on 01/05/2012.
//  Copyright (c) 2012 seb.ly. All rights reserved.
//

#include "CameraVidPlayer.h"

bool CameraVidPlayer::setup(string _name, string filename, int width, int height, int framerate) {
	
	CameraWrapper::setup(_name, width, height, framerate);
    
    
	//vidPlayer.initGrabber(width, height);
	//vidPlayer.setDesiredFrameRate(framerate); 
	
    if(!vidPlayer.loadMovie(filename)) {
	
		ofLog(OF_LOG_ERROR, "video file didn't load! ("+filename+")"); 
		return false;
    	
	}
    
    frameNum = 0; 
    vidPlayer.play();
	vidPlayer.setVolume(0);
	
	baseVideo = &vidPlayer; 

    return true; 
	
}
bool CameraVidPlayer::videoSettings(){
	//vidPlayer.videoSettings(); 
    vidPlayer.setPosition(0); 
	return true;
}
