//
//  TriggerSettingsAsteroids.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 04/10/2013.
//
//

#pragma once
#include "TriggerSettingsRocket.h"

class TriggerSettingsAsteroids : public TriggerSettingsRocket {

	void draw(float elapsedtime, ofVec3f pos, float unitPower, bool active, float scale, float angle) {
		
		//elapsedTime+=deltaTime;
		
		ofColor colour = getColour();
		
		ofPushMatrix();
		ofPushStyle();
		ofDisableBlendMode();
		
		ofTranslate(pos);
		ofScale(scale, scale);
		ofRotate(angle);
		
		ofFill();
		ofSetColor(0);
		//ofCircle(0,0, radius);
		ofTriangle(0, -radius, radius, radius, -radius, radius);
		
		ofNoFill();
		ofSetLineWidth(1);
		
		ofSetColor(colour);
		if(!active) ofSetColor(ofColor::gray);
		
		
		ofTriangle(0, -radius*1.2, radius, radius*1.2, -radius, radius*1.2);
		
		ofTranslate(0,radius*1.2);
		ofScale(unitPower,unitPower);
		ofFill();
		ofTriangle(0, -radius*2.4, radius, 0, -radius, 0);

		
		//path.clear();
		//path.setFillColor(colour);
		
		//path.moveTo(
		
		//path.setCircleResolution(12);
		//path.arc(0,0, (radius-2)*unitPower, (radius-2)*unitPower, -90, -90 + unitPower*360);
		
		
		//path.draw();
		
		/*
		 if(!active) {
		 
		 ofSetColor(ofColor::red);
		 ofRect(0,0, radius, radius);
		 
		 
		 }*/
//		if((rotateOnFire) || (rotationSpeed!=0)) {
//			ofRotate(angle);
//			ofLine(0,0,0,-20);
//		}
		
		ofPopStyle();
		ofPopMatrix();
	}


};