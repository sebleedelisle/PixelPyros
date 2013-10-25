//
//  TriggerSettingsAsteroids.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 04/10/2013.
//
//

#pragma once
#include "TriggerSettingsRocket.h"

class TriggerSettingsInvaders : public TriggerSettingsRocket {

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
		//ofRect(-radius*1.2, -radius, radius*2.4, radius*2);
		ofRect(-radius, -radius*0.4, radius*2, radius*1.2);
		
		ofNoFill();
		ofSetLineWidth(2);
		
		
		ofSetColor(colour);
		if(!active) ofSetColor(ofColor::gray);
		
		ofRect(-radius, -radius*0.4, radius*2, radius*1.2);
		ofLine(0,-radius, 0,-radius*0.2);
		
		//ofTriangle(0, -radius*1.2, radius, radius*1.2, -radius, radius*1.2);
		
		ofTranslate(0,radius*0.8);
		ofScale(1,-unitPower);
		ofFill();
		//ofTriangle(0, -radius*2.4, radius, 0, -radius, 0);
		ofRect(-radius, 0, radius*2, radius*1.2);
		//ofRect(-radius*1.2, 0, radius*2.4, radius*1.8);
		
		
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