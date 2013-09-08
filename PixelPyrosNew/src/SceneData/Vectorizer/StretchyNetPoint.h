//
//  StretchyNetPoint.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 22/08/2012.
//
//

#pragma once
#include "ofMain.h"

class StretchyNetPoint : public ofVec3f{

	public : 
	StretchyNetPoint(float x, float y, float z) {
		//pos.set(x+20,y+20);
		//set(pos);
		
		set(x,y, z);
		target.set(x,y, z);
		speed = 0.1;
		dampening = 0.8;
	}

	bool update() {
		
		vel*=dampening;
		diff = target - *this;
		diff*=speed; 
		vel+=diff;
		*this+=vel;
		//set(pos);
		
	}

	//ofVec3f pos;
	ofVec3f target;
	ofVec3f vel; 
	ofVec3f diff;
	float speed;
	float dampening;

};