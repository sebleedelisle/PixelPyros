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
	
	void sendOSCMessage(string message, float arg );
    void sendOSCMessage(string address, string arg );
	
	bool sendNewValue(SettingFloat& settingFloat) {
		//cout << "sending new value " << settingFloat.oscLabel << " " << settingFloat.getUnitValue()<< endl;
		sendOSCMessage(settingFloat.oscLabel, settingFloat.getUnitValue());
		
		
	}
	
	bool sendNewValue(SettingBool& settingBool) {
		//cout << "sending new value " << settingBool.oscLabel << " " << settingBool.getValue()<< endl;
		sendOSCMessage(settingBool.oscLabel, settingBool.getValue());
		
		
	}
	
	bool sendNewValue(SettingString& settingString) {
		//cout << "sending new value " << settingBool.oscLabel << " " << settingBool.getValue()<< endl;
		sendOSCMessage(settingString.oscLabel, settingString.value);
		
		
	}

	void addSettingFloat(SettingFloat & setting) {
		settingFloats.push_back(&setting);
		
	}
	void addSettingBool(SettingBool & setting) {
		settingBools.push_back(&setting);
		
	}
	void addSettingString(SettingString & setting) {
		settingStrings.push_back(&setting);
	}
	
	
    void handleOSCMessage(ofxOscMessage);
    static const int OSC_RECEIVER_PORT = 1234;
    static const int OSC_SENDER_PORT = 8000;
	
    ofxOscReceiver receiver;
    //ofxOscSender sender;
	
	vector <SettingFloat*> settingFloats;
	vector <SettingBool*> settingBools;
	vector <SettingString*> settingStrings;
	
	vector<ofxOscSender> senders; 
	
} ;