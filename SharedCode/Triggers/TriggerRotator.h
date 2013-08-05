//
//  TriggerRotator.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 25/08/2012.
//
//

#pragma once
#include "TriggerRocket.h"


class TriggerRotator : public TriggerRocket {

	public :
	TriggerRotator(ParticleSystemManager & psm, float extent = 10, float speed = 2,
		bool rotateonfire = false) : TriggerRocket(psm) {
		
		typeLabel = "TriggerRocket";
		
		rotationExtent = extent;
		rotationSpeed = speed;
		rotateOnFire = rotateonfire;
		minTriggerInterval = 0.1;
		
		rocketCount = 0; 
		
	}
	
	void start() {
		TriggerRocket::start();
		angle = -90;
		displayAngle = -90;

	}
	bool update(float deltaTime) {
		
		
		if(!rotateOnFire) {
			angle = (sin(elapsedTime*rotationSpeed)*rotationExtent)-90;
		}
		
		displayAngle+=((angle-displayAngle)*0.1);
		
		return TriggerRocket::update(deltaTime);
		
	}
	
	void draw() {
		if(!active) return;

		TriggerRocket::draw();
		
		ofPushStyle();
		ofPushMatrix();
		
		ofTranslate(pos);
		ofScale(scale, scale);
		ofRotate(displayAngle);
		ofLine(0,0,20,0); 

		
		ofPopStyle();
		ofPopMatrix();
		
	};
	
	
	bool doTrigger() {
		
		
		if(!TriggerSimple :: doTrigger()) return false;
		if(rocketSettings.size()==0) return false;
		
		RocketSettings & rs = rocketSettings[currentRocketIndex];

		PhysicsObject *rocket = makeNewRocket();
		
		if(rotateOnFire) {
			angle = (sin(rocketCount/2*rotationSpeed)*rotationExtent)-90;
			//cout << "rotateOnFire " << angle << " " << rocketCount << endl;
		}
		
		rocket->vel.set(ofMap(ofRandom(1), 0, 1, rs.startSpeedMin, rs.startSpeedMax),0,0);
		rocket->vel.rotate(0,0, +angle );
		
				
		rocketCount++; 
		return true; 
	}

	virtual TriggerRotator* clone() const{
		//cout << "clone TriggerRotator"<< endl;
		return new TriggerRotator( *this );
	}

	
	float rotationExtent;
	float rotationSpeed;
	float rocketCount;
	bool rotateOnFire;
	float angle;
	float displayAngle; 






};