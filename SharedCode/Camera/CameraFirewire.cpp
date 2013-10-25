/*
 *  CameraFirewire.cpp
 *  PixelPhones
 *
 *  Created by Seb Lee-Delisle on 16/03/2012.
 *  Copyright 2012 seb.ly. All rights reserved.
 *
 */

#include "CameraFirewire.h"

bool CameraFirewire::setup(string _name, int width, int height, int framerate)  {
	
	CameraWrapper::setup(_name, width, height, framerate);
    
	// setup() will pick the first camera. Or if there are multiple cameras you
	// can use the number, or the GUID of the camera.
    if(!camera.setup()) return false;
	
    camera.setBayerMode(DC1394_COLOR_FILTER_GBRG);
	//    camera.set1394b(true);
	
   
    name = _name; 
	baseVideo = &camera;
	
	return true; 
	
}

bool CameraFirewire::videoSettings(){
	//camera.videoSettings(); 
	return false; 
}

/*
void CameraFirewire :: initControlPanel(ofxAutoControlPanel &gui, float w) { 
	
	gui.addLabel("Firewire camera");
	
	unsigned int min, max; 
	
	
//	gui.addSlider("Shutter", "FW_SHUTTER", getShutter(), 1, 500, true)->setDimensions(400, 10); // actual top limit is 4000
//	
//	gui.addSlider("Brightness", "FW_BRIGHTNESS", getBrightness(), 0, 255, true)->setDimensions(400, 10); ;
//	
//	gui.addSlider("Gain", "FW_GAIN", getGain(), 180, 1023, true)->setDimensions(400, 10); ;
//	
//	gui.addSlider("Gamma", "FW_GAMMA", getGamma(), 10, 22, true)->setDimensions(400, 10); ;	

	
}
*/

int CameraFirewire::getGain() { 
	return camera.getGainRaw(); 
}

void CameraFirewire::setGain(int v) { 
	camera.setGainRaw(v); 
	
	//cout << "gain " << camera.getGainRaw() << "\n"; 
}

int CameraFirewire::getGamma() { 
	return camera.getGammaRaw(); 
}

void CameraFirewire::setGamma(int v) { 
	camera.setGammaRaw(v); 
	
	//cout << "gamma " << camera.getGammaRaw() << "\n"; 
}

int CameraFirewire::getBrightness() { 
	return camera.getBrightnessRaw(); 
}

void CameraFirewire::setBrightness(int v) { 
	camera.setBrightnessRaw(v); 
	
	//cout << "brightness " << camera.getGammaRaw() << "\n"; 
}

int CameraFirewire::getShutter() { 
	return camera.getShutterRaw(); 
}

void CameraFirewire::setShutter(int v) { 
	camera.setShutterRaw(v) ;
	//cout << "shutter " << camera.getShutterRaw()<< "\n";
}
