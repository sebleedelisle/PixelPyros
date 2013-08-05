//
//  SettingsManager.cpp
//  PixelPyros
//
//  Created by Jack Lang on 30/08/2012.
//


#include "SettingsManager.h"

SettingsManager::SettingsManager() {
	
	oscManager = NULL;
	controlPanel = NULL; 
	
}

void SettingsManager::setup (OscManager * osc, ofxControlPanel * gui) {
		
	oscManager = osc;
	controlPanel = gui;
	updateSettingsFreq = 2;
	
	lastUpdate = ofGetElapsedTimef(); 
}


void SettingsManager::update() {

	bool resendAllValues = false;
	
	if(ofGetElapsedTimef() - lastUpdate > updateSettingsFreq) {
		
		resendAllValues = true;
		lastUpdate = ofGetElapsedTimef(); 
		oscManager->sendOSCMessage("/PixelPyros/Monitor/value", ofGetFrameRate() ) ;
	}
	
	
	for(int i = 0; i<settingFloats.size(); i++) {
		
		SettingFloat* setting = settingFloats[i];
		
		if(setting->checkChanged()) {
			//cout << "value changed " << endl;
			oscManager->sendNewValue(*setting);
			controlPanel->setValueF(setting->xmlLabel, setting->value);
			controlPanel->saveSettings();
			
		} else if(resendAllValues) {
			oscManager->sendNewValue(*setting);
			
		}
	}
	
	
	for(int i = 0; i<settingBools.size(); i++) {
		
		SettingBool* setting = settingBools[i];
		
		if(setting->checkChanged()) {
			//cout << "value changed " << endl;
			oscManager->sendNewValue(*setting);
			controlPanel->setValueB(setting->xmlLabel, setting->value);
			
			controlPanel->saveSettings();
			
			
		} else if(resendAllValues) {
			oscManager->sendNewValue(*setting);
			
		}
	}
	
	for(int i = 0; i<settingString.size(); i++) {
		
		SettingString* setting = settingString[i];
		
		if(setting->checkChanged()) {
			//cout << "value changed " << endl;
			oscManager->sendNewValue(*setting);
			
		} else if(resendAllValues) {
			oscManager->sendNewValue(*setting);
			
		}
	}
}


void SettingsManager::addSettingFloat(float * valuePointer, string xmlname, string osclabel, float min, float max ) {
	
	SettingFloat* settingFloat = new SettingFloat(valuePointer, xmlname, osclabel, min, max);
	
	//threshold = SettingFloat(targetThreshold, "THRESHOLD", "/PixelPyros/Setup/Threshold/x", 0, 255);
	oscManager->addSettingFloat(*settingFloat);
	settingFloats.push_back(settingFloat);
	
}


void SettingsManager::addSettingBool(bool * valuePointer, string xmlname, string osclabel, bool sendCurrent, bool ignorefalse) {
	
	SettingBool* setting = new SettingBool(valuePointer, xmlname, osclabel, ignorefalse);
	
	//threshold = SettingFloat(targetThreshold, "THRESHOLD", "/PixelPyros/Setup/Threshold/x", 0, 255);
	oscManager->addSettingBool(*setting);
	settingBools.push_back(setting);
	if(sendCurrent) setting->value = !*setting->target; 
	
}

void SettingsManager::addSettingString(string * valuePointer, string osclabel ) {
	
	SettingString* setting = new SettingString(valuePointer, osclabel);
	
	//threshold = SettingFloat(targetThreshold, "THRESHOLD", "/PixelPyros/Setup/Threshold/x", 0, 255);
	oscManager->addSettingString(*setting);
	settingString.push_back(setting);
	
}
