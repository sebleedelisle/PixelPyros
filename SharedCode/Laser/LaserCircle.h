//
//  LaserCircle.h
//
//  Created by Seb Lee-Delisle on 01/08/2013.
//
//

#pragma once

#include "LaserShape.h"

class LaserCircle : public LaserShape{
	
	public :
	
	LaserCircle(const ofPoint& position, ofFloatColor& colour, float circleRadius, float circleIntensity = 1){
		set(position, colour, radius, circleIntensity);
	}
	
	void set(const ofPoint& position, ofFloatColor& circleColour, float circleRadius, float circleIntensity = 1) {
		colour = circleColour;
		
		pos = position;
		startPos = pos;
		startPos.y-=radius;
		endPos = startPos;
		
		circleRadius = radius;
		
		intensity = circleIntensity;
		tested = false;
	}
		
	float intensity = 1;
	ofFloatColor colour;
	
	ofPoint pos;
	float radius; 
		
};

