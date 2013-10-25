//
//  LaserCircle.h
//
//  Created by Seb Lee-Delisle on 01/08/2013.
//
//

#pragma once

#include "LaserShape.h"

class LaserLine : public LaserShape{
	
	public :
	
	LaserLine(const ofPoint& startpos, const ofPoint& endpos, ofFloatColor& col, float lineintensity = 1){
	
		reversable = true; 
		colour = col;
		
		startPos = startpos;
		endPos = endpos;
		
		
		
		
		intensity = lineintensity;
		tested = false;
		
	//cout<<"LINE SET : " << startPos << " " << endPos << " " <<endl;
		
	}
	
			
	float intensity = 1;
	ofFloatColor colour;
		
};

