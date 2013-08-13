//
//  OscManager.h
//  PixelPyros
//
//  Created by Jack Lang on 30/08/2012.
//

#pragma once

#include "ofxOsc.h"

#include "SettingFloat.h"
#include "SettingBool.h"
#include "SettingString.h"

#define OSC_OFF(x) (x == 0)
#define OSC_ON(x) (x == 1.0f	)


class OscManager {
	public :
	
	//SettingsManager *settingsManager ;
	//SceneManager *sceneManager ;
	
	void setup () ;
	void update () ;
	
	void addOscDevice(string address);
	
	void sendOscMessage(string message, float arg );
    void sendOscMessage(string address, string arg );
	
	bool sendNewValue(SettingFloat& settingFloat);
	bool sendNewValue(SettingBool& settingBool);
	
	bool sendNewValue(SettingString& settingString);
	void addSettingFloat(SettingFloat & setting);
	void addSettingBool(SettingBool & setting);
	void addSettingString(SettingString & setting);
	
    void handleOscMessage(ofxOscMessage);
    static const int OSC_RECEIVER_PORT = 1234;
    static const int OSC_SENDER_PORT = 8000;
	
    ofxOscReceiver receiver;
    //ofxOscSender sender;
	
	vector <SettingFloat*> settingFloats;
	vector <SettingBool*> settingBools;
	vector <SettingString*> settingStrings;
	
	vector<ofxOscSender> senders; 
	
} ;