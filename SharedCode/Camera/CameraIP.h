//
//  CameraIP.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 08/10/2013.
//
//

#pragma once

#include "ofMain.h"
#include "CameraWrapper.h"
#include "IPVideoGrabber.h"

using namespace ofx::Video;



class CameraIP : public CameraWrapper {

	public :
	bool setup(string _name, int width, int height, int framerate, string url, string user, string pass);
	bool update();
	
	
	void connectCamera();
	bool videoSettings();
	
	IPVideoGrabber ipGrabber;
	string url, user, password; 




};