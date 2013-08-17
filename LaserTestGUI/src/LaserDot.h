//
//  LaserDot.h
//
//  Created by Seb Lee-Delisle on 01/08/2013.
//
//

#pragma once

class LaserDot : public ofPoint{
	
	public :
	
	LaserDot(const ofPoint& dotPosition, ofFloatColor& dotColour, float dotIntensity = 1) {
		set(dotPosition, dotColour, dotIntensity);
		
	}
	void set(const ofPoint& dotPosition, ofFloatColor& dotColour, float dotIntensity = 1) {
		
		colour = dotColour;
		ofPoint::set(dotPosition);
		intensity = dotIntensity; 
		tested = false;
	}
		
	float intensity = 1;
	ofFloatColor colour;
	bool tested = false;

	
};

