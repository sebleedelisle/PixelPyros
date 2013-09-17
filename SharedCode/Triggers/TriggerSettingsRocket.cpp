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


void TriggerSettingsRocket::draw(float elapsedtime, ofVec3f pos, ofColor colour, float unitPower, bool active, float scale) {
	
	//elapsedTime+=deltaTime;
	
	ofPushMatrix();
	ofPushStyle();
	
	ofFill();
	ofSetColor(0);
	ofCircle(0,0, radius);
	
	
	ofNoFill();
	ofSetLineWidth(1);
	
	ofSetColor(colour);
	if(!active) ofSetColor(ofColor::gray);
	
	ofTranslate(pos);
	ofScale(scale, scale);
	
	ofCircle(0,0, radius);
	
	
	//ofCircle(pos, radius*unitPower);
	
	path.clear();
	path.setFillColor(colour);
	path.setCircleResolution(12);
	path.arc(0,0, (radius-2)*unitPower, (radius-2)*unitPower, -90, -90 + unitPower*360);
	
	
	path.draw();
	
	
	if(!active) {
		
		ofSetColor(ofColor::red);
		ofRect(0,0, radius, radius);
		
		
	}
	
	ofPopStyle();
	ofPopMatrix();
}