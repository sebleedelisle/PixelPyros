//
//  TriggerSettingsRocketRotator.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 10/09/2013.
//
//

/*
#include "TriggerSettingsRocketRotator.h"


TriggerSettingsRocketRotator :: TriggerSettingsRocketRotator(float extent, float speed, bool rotateonfire){
		
	rotationExtent = extent;
	rotationSpeed = speed;
	rotateOnFire = rotateonfire;
		
	rocketCount = 0;

	
		
}


void TriggerSettingsRocketRotator::draw(float elapsedtime, ofVec3f pos, float unitPower, bool active, float scale) {
	
	elapsedTime = elapsedtime;

	TriggerSettingsRocket::draw(elapsedtime, pos, unitPower, active, scale);
	
	if(!rotateOnFire) {
//		angle = (sin(elapsedTime*rotationSpeed)*rotationExtent)-90;
	}
	
//	displayAngle+=((angle-displayAngle)*0.1);
	
	
	ofPushStyle();
	ofPushMatrix();
	ofSetColor(getColour());

	ofTranslate(pos);
	//ofScale(scale, scale);
//	ofRotate(displayAngle);
	ofLine(0,0,20,0);
	
	
	ofPopStyle();
	ofPopMatrix();
	
};

void TriggerSettingsRocketRotator::doTrigger(ofVec3f& pos, float power, float direction) {
	
	RocketSettings& rs = *rocketSettings;
	
	PhysicsObject *rocket = NULL;//makeNewRocket(pos);
	
	if(rotateOnFire) {
//		angle = (sin(rocketCount/2*rotationSpeed)*rotationExtent)-90;
	}
	
	rocket->vel.set(ofMap(ofRandom(1), 0, 1, rs.startSpeedMin, rs.startSpeedMax),0,0);
//	rocket->vel.rotate(0,0, +angle );
	
	
	rocketCount++;
	
}

*/