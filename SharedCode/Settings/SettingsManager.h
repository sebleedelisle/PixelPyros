//
//  SettingsManager.h
//  PixelPyros
//
//  Created by Jack Lang on 30/08/2012.
//


#pragma once

#include "ofxControlPanel.h"
#include "OscManager.h"

#include "SettingFloat.h"
#include "SettingBool.h"
#include "SettingString.h"

class SettingsManager
{
    public:
	
	SettingsManager(); 
    
    void setup (OscManager * osc, ofxControlPanel * gui) ;
    
	void update();
	
	void addSettingFloat(float * valuePointer, string xmlname, string osclabel, float min, float max);
	
	void addSettingBool(bool * valuePointer, string xmlname, string osclabel, bool sendCurrent = false, bool ignorefalse = false);

	void addSettingString(string * valuePointer, string osclabel );
	
	//SettingFloat threshold;
	
	vector <SettingFloat*> settingFloats;
	vector <SettingBool*> settingBools;
	vector <SettingString*> settingString;
	
	OscManager * oscManager;
	ofxControlPanel * controlPanel;
		
	float updateSettingsFreq;
	float lastUpdate; 
	
};
