//
//  CameraIP.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 08/10/2013.
//
//

#include "CameraIP.h"

bool CameraIP::setup(string _name, int width, int height, int framerate, string _url, string _user, string _pass) {
	
	CameraWrapper::setup(_name, width, height, framerate);
	
	//if(!ipGrabber.initGrabber(width, height)) return false;
	url = _url;
	user = _user;
	password = _pass; 
	
	connectCamera(); 
	
	//grabber->setURI("http://148.61.142.228/axis-cgi/mjpg/video.cgi?resolution=320x240");
	
	
	
	name = _name;
    frameNum = 0;
	
	baseVideo = &ipGrabber;
	ipGrabber.update();
	
	return true;
	
}
bool CameraIP::update(){
	
	
	if(!ipGrabber.isConnected()) {
		
		connectCamera();
		
	}
	return CameraWrapper::update();
	
};  // returns true if frame is new


void CameraIP::connectCamera() {
	
	ipGrabber.setUsername(user);
	ipGrabber.setPassword(password);
	
	ipGrabber.setCameraName(name);
	ipGrabber.setURI(url);

	ipGrabber.connect(); // connect immediately
	
	// if desired, set up a video resize listener
	//ofAddListener(grabber->videoResized, this, &ofApp::videoResized);

	
}


bool CameraIP::videoSettings(){
	return false;
}


