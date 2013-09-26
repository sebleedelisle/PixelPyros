//
//  LaserDot.h
//
//  Created by Seb Lee-Delisle on 01/08/2013.
//
//

#pragma once

#include "LaserShape.h"

class LaserDot : public LaserShape{
	
	public :
	
	LaserDot(const ofPoint& dotPosition, ofFloatColor& dotColour, float dotIntensity = 1){
		set(dotPosition, dotColour, dotIntensity);
	}
	
	/*
	LaserDot(const ofPoint& dotPosition, ofFloatColor& dotColour, float dotIntensity = 1) : LaserShape(dotPosition,dotPosition){
		set(dotPosition, dotColour, dotIntensity);
	}*/

	void set(const ofPoint& dotPosition, ofFloatColor& dotColour, float dotIntensity = 1) {
		colour = dotColour;
		startPos.set(dotPosition);
		endPos.set(dotPosition);
		intensity = dotIntensity; 
		tested = false;
	}
		
	float intensity = 1;
	ofFloatColor colour;
		
};

