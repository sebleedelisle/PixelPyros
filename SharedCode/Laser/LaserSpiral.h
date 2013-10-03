//
//  LaserSpiral.h
//
//  Created by Seb Lee-Delisle on 01/08/2013.
//
//

#pragma once

#include "LaserShape.h"

class LaserSpiral : public LaserShape{
	
	public :
	
	LaserSpiral(const ofPoint& position, ofFloatColor& col, float rad1,float rad2, float fadeoutpoint = 1,  float intens = 1){
		pos = position;
		colour = col;
		radius1 = rad1;
		radius2 = rad2; 
		intensity = intens;
		fadeOutPoint = fadeoutpoint; 
		
		tested = false;
		
		startPos.set(rad1, 0);
		endPos.set(rad2, 0);
		
		startPos+=pos;
		endPos+=pos; 
		
	}
			
	float intensity = 1;
	ofFloatColor colour;
	
	ofPoint pos;
	float radius1;
	float radius2;
	float fadeOutPoint;
		
};

