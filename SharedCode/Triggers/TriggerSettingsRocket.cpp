//
//  TriggerableRocket.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 01/09/2013.
//
//

#include "TriggerSettingsRocket.h"

TriggerSettingsRocket :: TriggerSettingsRocket() : particleSystemManager(*ParticleSystemManager::instance()) {
	
	rocketSettings = NULL;
	
	rotationExtent = 0;
	rotationSpeed = 0;
	rotateOnFire = false;
	
	
}



void TriggerSettingsRocket ::doTrigger(ofVec3f& pos, float power, float direction){
	
	PhysicsObject* rocket = NULL;
	
	if(rocketSettings!=NULL) {
		rocket = particleSystemManager.addRocket(*rocketSettings, pos);

		rocket->vel.rotate(0,0, direction );
		
	}
	



}



void TriggerSettingsRocket::draw(float elapsedtime, ofVec3f pos, float unitPower, bool active, float scale, float angle) {
	
	//elapsedTime+=deltaTime;
	
	ofColor colour = getColour(); 
	
	ofPushMatrix();
	ofPushStyle();
	ofDisableBlendMode();
	
	ofTranslate(pos);
	ofScale(scale, scale);
	
	ofFill();
	ofSetColor(0);
	ofCircle(0,0, radius);
	
	
	ofNoFill();
	ofSetLineWidth(1);
	
	ofSetColor(colour);
	if(!active) ofSetColor(ofColor::gray);
	
	
	ofCircle(0,0, radius);
	
	
	//ofCircle(pos, radius*unitPower);
	
	path.clear();
	path.setFillColor(colour);
	path.setCircleResolution(12);
	path.arc(0,0, (radius-2)*unitPower, (radius-2)*unitPower, -90, -90 + unitPower*360);
	
	
	path.draw();
	
	/*
	if(!active) {
		
		ofSetColor(ofColor::red);
		ofRect(0,0, radius, radius);
		
		
	}*/
	if((rotateOnFire) || (rotationSpeed!=0)) {
		ofRotate(angle);
		ofLine(0,0,0,-20);
	}
	
	ofPopStyle();
	ofPopMatrix();
}

ofColor TriggerSettingsRocket::getColour() {
	ofColor c = ofColor::white;
	c.setSaturation(saturation);

	c.setHue(hue);
	return c; 

}