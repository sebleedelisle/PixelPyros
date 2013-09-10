//
//  TriggerSettingsRocketRotator.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 10/09/2013.
//
//

#include "TriggerSettingsRocketRotator.h"


TriggerSettingsRocketRotator :: TriggerSettingsRocketRotator(float extent, float speed, bool rotateonfire){
		
	rotationExtent = extent;
	rotationSpeed = speed;
	rotateOnFire = rotateonfire;
		
	rocketCount = 0;

	
	angle = -90;
	displayAngle = -90;
	
}


void TriggerSettingsRocketRotator::draw(float elapsedtime, ofVec3f pos, float radius, ofColor colour, float unitPower, bool active) {
	
	elapsedTime = elapsedtime;
	//cout<< rotateOnFire << " " << elapsedtime << " " << displayAngle << " " << angle << endl;
	TriggerSettingsRocket::draw(elapsedtime, pos, radius, colour, unitPower, active);
	
	if(!rotateOnFire) {
		angle = (sin(elapsedTime*rotationSpeed)*rotationExtent)-90;
		//cout<< sin(elapsedTime*rotationSpeed) << " " << rotationSpeed << endl;
		
	}
	
	displayAngle+=((angle-displayAngle)*0.1);
	
	
	ofPushStyle();
	ofPushMatrix();
	
	ofTranslate(pos);
	//ofScale(scale, scale);
	ofRotate(displayAngle);
	ofLine(0,0,20,0);
	
	
	ofPopStyle();
	ofPopMatrix();
	
};

void TriggerSettingsRocketRotator::doTrigger(ofVec3f& pos, float power, float direction) {
	
	RocketSettings& rs = *rocketSettings;
	
	//if(!TriggerSimple :: doTrigger()) return false;
	//if(rocketSettings.size()==0) return false;
	
	//RocketSettings & rs = rocketSettings[currentRocketIndex];
	
	PhysicsObject *rocket = makeNewRocket(pos);
	
	if(rotateOnFire) {
		angle = (sin(rocketCount/2*rotationSpeed)*rotationExtent)-90;
		//cout << "rotateOnFire " << angle << " " << rocketCount << endl;
	}
	
	rocket->vel.set(ofMap(ofRandom(1), 0, 1, rs.startSpeedMin, rs.startSpeedMax),0,0);
	rocket->vel.rotate(0,0, +angle );
	
	
	rocketCount++;
	
}