/*
 *  CameraFirewire.cpp
 *  PixelPhones
 *
 *  Created by Seb Lee-Delisle on 16/03/2012.
 *  Copyright 2012 seb.ly. All rights reserved.
 *
 */

#include "CameraCanon.h"

bool CameraCanon::setup(string _name, int width, int height, int framerate)  {
	
	CameraWrapper::setup(_name, width, height, framerate);
    
	// setup() will pick the first camera. Or if there are multiple cameras you
	// can use the number, or the GUID of the camera.
    //if(!camera.setup()) return false;
	
    //camera.setBayerMode(DC1394_COLOR_FILTER_GBRG);
	//    camera.set1394b(true);
	
    name = _name;
	//baseVideo = &camera;
	
	canon.start();
	if(canon.isCameraConnected()) return true;
	else return false;
}


bool CameraCanon :: update(){
	
	//baseVideo->update();
	bool newFrame = canon.updateLiveView(); // baseVideo->isFrameNew();
	
	if(newFrame) {
		
		
		cv::Mat camMat = ofxCv::toCv(canon.getLivePixels());
		
		if(flipX||flipY) {
			int code;
			if(flipX && flipY)
				code = -1;
			else if(flipX)
				code = 1;
			else
				code = 0;
			
			cv::flip(camMat, camMat, code);
			
		}
		
		if(greyScale) {
			cv::Mat greyMat = ofxCv::toCv(greyImage);
			ofxCv::convertColor(camMat, greyMat, CV_RGB2GRAY);
			greyImage.update();
		} else {
			
			cv::Mat colMat = ofxCv::toCv(colImage);
			//ofxCv::convertColor(camMat, colMat, CV_RGB2GRAY);
			//ofxCv::convertColor(camMat, colMat,CV_RGB2GRAY);
			
			ofxCv::copy(camMat, colMat);
			colImage.update();
			
			
		}
	}
	
	return newFrame;
	
};  // returns true if frame is new


bool CameraCanon::videoSettings(){
	//camera.videoSettings();
	
}


void CameraCanon :: initControlPanel(ofxAutoControlPanel &gui, float w) {
	
	gui.addLabel("Canon camera");
	
	unsigned int min, max;
	
	
//	gui.addSlider("Shutter", "FW_SHUTTER", getShutter(), 1, 500, true)->setDimensions(400, 10); // actual top limit is 4000
//	
//	gui.addSlider("Brightness", "FW_BRIGHTNESS", getBrightness(), 0, 255, true)->setDimensions(400, 10); ;
//	
//	gui.addSlider("Gain", "FW_GAIN", getGain(), 180, 1023, true)->setDimensions(400, 10); ;
//	
//	gui.addSlider("Gamma", "FW_GAMMA", getGamma(), 10, 22, true)->setDimensions(400, 10); ;
	
	
}


int CameraCanon::getGain() {
	return 0;//camera.getGainRaw();
}

void CameraCanon::setGain(int v) {
	//camera.setGainRaw(v);
	
	//cout << "gain " << camera.getGainRaw() << "\n";
}

int CameraCanon::getGamma() {
	return 0;//camera.getGammaRaw();
}

void CameraCanon::setGamma(int v) {
	//camera.setGammaRaw(v);
	
	//cout << "gamma " << camera.getGammaRaw() << "\n";
}

int CameraCanon::getBrightness() {
	return 0;//camera.getBrightnessRaw();
}

void CameraCanon::setBrightness(int v) {
	//camera.setBrightnessRaw(v);
	
	//cout << "brightness " << camera.getGammaRaw() << "\n";
}

int CameraCanon::getShutter() {
	return 0;//camera.getShutterRaw();
}

void CameraCanon::setShutter(int v) {
	//camera.setShutterRaw(v) ;
	//cout << "shutter " << camera.getShutterRaw()<< "\n";
}
