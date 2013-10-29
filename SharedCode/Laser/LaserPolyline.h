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
		
	//cout << "LASERPOLYLINE CREATE -----------" << endl;
		reversable = false;

		polyline = sourcepoly; // makes a copy
		
		startPos = polyline.getPointAtPercent(0);
		endPos = polyline.getPointAtPercent(1);
		
		polyline.simplify();
				
		tested = false;
				
	}
	
	~LaserPolyline() {
		polyline.clear();
	}
	
	ofPolyline polyline;
	float intensity = 1;
	ofFloatColor colour;
		
};

