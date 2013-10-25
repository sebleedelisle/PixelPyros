//
//  LaserCircle.h
//
//  Created by Seb Lee-Delisle on 01/08/2013.
//
//

#pragma once

#include "LaserShape.h"
#include "ofMain.h"

class LaserPolyline : public LaserShape{
	
	public :
	
	LaserPolyline(const ofPolyline& sourcepoly){
	
		reversable = false;
		//colour = col;
		
		//startPos = sourcepath.;
		//endPos = endpos;
		polyline = sourcepoly;
		
		startPos = polyline.getPointAtPercent(0);
		endPos = polyline.getPointAtPercent(1);
		
		polyline.simplify();
		
		
		//intensity = 1;//lineintensity;
		tested = false;
		
	//cout<<"LINE SET : " << startPos << " " << endPos << " " <<endl;
		
	}
	
	ofPolyline polyline;
	float intensity = 1;
	ofFloatColor colour;
		
};

