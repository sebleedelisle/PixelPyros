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
	
	
	senders.push_back(ofxOscSender());
	//senders.push_back(ofxOscSender());
	//senders.push_back(ofxOscSender());
	
    senders[0].setup("SebsiPad.local", OSC_SENDER_PORT);
    //senders[1].setup("SebsiPhone.local", OSC_SENDER_PORT);
    //senders[2].setup("JIP2.local", OSC_SENDER_PORT);
    
	
}

void OscManager::update ()
{
	while( receiver.hasWaitingMessages() )
    {
        ofxOscMessage msg;
        receiver.getNextMessage(&msg);
        handleOSCMessage(msg);
    }
		
}



void OscManager::handleOSCMessage(ofxOscMessage msg) 
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

void OscManager::sendOSCMessage(string address, float arg )
{
    ofxOscMessage message ;
    message.setAddress(address) ;
    message.addFloatArg(arg) ;
	
	for (int i = 0; i<senders.size(); i++) {
		senders[i].sendMessage(message) ;
	}

}


void OscManager::sendOSCMessage(string address, string arg )
{
    ofxOscMessage message ;
    message.setAddress(address) ;
    message.addStringArg(arg) ;
	
	std::cout << "sending string message " << address << arg << std::endl ;
	
	for (int i = 0; i<senders.size(); i++) {
		senders[i].sendMessage(message) ;
	}
	
}