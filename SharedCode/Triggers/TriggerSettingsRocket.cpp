//
//  TriggerableRocket.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 01/09/2013.
//
//

#include "TriggerSettingsRocket.h"

TriggerSettingsRocket :: TriggerSettingsRocket() : particleSystemManager(*ParticleSystemManager::instance()) {
	
	//rocketSettings = NULL;

}



void TriggerSettingsRocket ::doTrigger(ofVec3f& pos, float power, float direction){
	
	PhysicsObject *rocket = makeNewRocket(pos);

}



PhysicsObject * TriggerSettingsRocket:: makeNewRocket(ofVec3f& pos) {
	PhysicsObject* rocket = NULL;
	
	if(rocketSettings!=NULL) {
		rocket = particleSystemManager.addRocket(*rocketSettings, pos);
	}

	
	return rocket;
	
}


void TriggerSettingsRocket::draw(float elapsedtime, ofVec3f pos, float radius, ofColor colour, float unitPower, bool active ) {
	
	//elapsedTime+=deltaTime;
	
	ofPushStyle();
	ofNoFill();
	
	ofSetColor(colour);
	if(!active) ofSetColor(ofColor::gray);
	
	ofCircle(pos, radius);
	
	//ofCircle(pos, radius*unitPower);
	
	path.clear();
	path.setFillColor(colour);
	path.setCircleResolution(12);
	path.arc(pos, radius*unitPower, radius*unitPower, -90, -90 + unitPower*360);
	
	
	path.draw();
	
	
	if(!active) {
		
		ofSetColor(ofColor::red);
		ofRect(pos, radius, radius);
		
		
	}
	
	ofPopStyle();
	
}