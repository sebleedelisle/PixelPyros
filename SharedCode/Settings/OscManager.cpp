//
//  OscManager.cpp
//  PixelPyros
//
//  Created by Jack Lang on 30/08/2012.
//

#include <iostream>
#include "OscManager.h"

void OscManager::setup ()
{
	receiver.setup(OSC_RECEIVER_PORT);
    std::cout << "listening on port " << OSC_RECEIVER_PORT << std::endl;
	
	addOscDevice("10.0.1.6");
	//senders.push_back(ofxOscSender());
	//senders.push_back(ofxOscSender());
	//senders.push_back(ofxOscSender());
	
    //senders[0].setup("10.0.1.6", OSC_SENDER_PORT);
    //senders[1].setup("Sebs-iPhone4.local", OSC_SENDER_PORT);
    //senders[2].setup("JIP2.local", OSC_SENDER_PORT);
    
	
}

void OscManager::addOscDevice(string address) {
	
	senders.push_back(ofxOscSender());
	senders[senders.size()-1].setup(address, OSC_SENDER_PORT);
	
}

void OscManager::update ()
{
	while( receiver.hasWaitingMessages() )
    {
        ofxOscMessage msg;
        receiver.getNextMessage(&msg);
        handleOscMessage(msg);
    }
		
}

bool OscManager::sendNewValue(SettingFloat& settingFloat) {
	//cout << "sending new value " << settingFloat.oscLabel << " " << settingFloat.getUnitValue()<< endl;
	sendOscMessage(settingFloat.oscLabel, settingFloat.getUnitValue());
	
	
}

bool OscManager::sendNewValue(SettingBool& settingBool) {
	//cout << "sending new value " << settingBool.oscLabel << " " << settingBool.getValue()<< endl;
	sendOscMessage(settingBool.oscLabel, settingBool.getValue());
	
	
}

bool OscManager::sendNewValue(SettingString& settingString) {
	//cout << "sending new value " << settingBool.oscLabel << " " << settingBool.getValue()<< endl;
	sendOscMessage(settingString.oscLabel, settingString.value);
	
	
}

void OscManager::addSettingFloat(SettingFloat & setting) {
	settingFloats.push_back(&setting);
	
}
void OscManager::addSettingBool(SettingBool & setting) {
	settingBools.push_back(&setting);
	
}
void OscManager::addSettingString(SettingString & setting) {
	settingStrings.push_back(&setting);
}



void OscManager::handleOscMessage(ofxOscMessage msg)
{
    string address = msg.getAddress().substr(0, msg.getAddress().find(":"));
    //std::cout << "OSC Message: " << address << std::endl;
    
    std::cout << "OSC Message: " << msg.getAddress() <<" " << msg.getArgAsFloat(0) << std::endl;

	for(int i = 0; i<settingFloats.size(); i++) {
		
		
		SettingFloat * setting = settingFloats[i];
		
		if(msg.getAddress()==setting->oscLabel) {
			
			setting->setFromUnit(msg.getArgAsFloat(0));
			
			cout << "changing  " << setting->oscLabel << " to " << setting->target << endl;
			
		}
	}
	
	for(int i = 0; i<settingBools.size(); i++) {
		
		
		SettingBool * setting = settingBools[i];
		
		if(msg.getAddress()==setting->oscLabel) {
			
			setting->set(msg.getArgAsFloat(0));
			
			cout << "changing  " << setting->oscLabel << " to " << setting->target << endl;
			
		}
	}
	

}

void OscManager::sendOscMessage(string address, float arg )
{
    ofxOscMessage message ;
    message.setAddress(address) ;
    message.addFloatArg(arg) ;
	
	for (int i = 0; i<senders.size(); i++) {
		senders[i].sendMessage(message) ;
	}

}


void OscManager::sendOscMessage(string address, string arg )
{
    ofxOscMessage message ;
    message.setAddress(address) ;
    message.addStringArg(arg) ;
	
	//std::cout << "sending string message " << address << " : " <<arg << std::endl ;
	
	for (int i = 0; i<senders.size(); i++) {
		senders[i].sendMessage(message) ;
	}
	
}