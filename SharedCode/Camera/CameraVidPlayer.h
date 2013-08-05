//
//  CameraVidPlayer.h
//  PixelPhones
//
//  Created by Seb Lee-Delisle on 01/05/2012.
//  Copyright (c) 2012 seb.ly. All rights reserved.
//
#pragma once

#include "ofMain.h"
#include "CameraWrapper.h"

class CameraVidPlayer : public CameraWrapper { 
    
	public :
	bool setup(string _name, string filename, int width = 640, int height = 480, int framerate =30);
	
	
	bool videoSettings(); 
   
	ofVideoPlayer vidPlayer; 

    
    
	
	
};