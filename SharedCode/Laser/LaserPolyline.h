//
//  LaserCircle.h
//
//  Created by Seb Lee-Delisle on 01/08/2013.
//
//

#pragma once

#include "LaserShape.h"
#include "ofMain.h"
#include "ColourSystem.h"

class LaserPolyline : public LaserShape{
	
	public :
	
	LaserPolyline(const ofPolyline& sourcepoly, ColourSystem* coloursystem = NULL, float intens = 1){
		
		reversable = false;
		intensity = intens;
		polyline = sourcepoly; // makes a copy
		
		startPos = polyline.getPointAtPercent(0);
		// to avoid a bug in polyline in open polys
		endPos = polyline.getPointAtPercent(1);
		colourSystem = coloursystem;
		previewMesh.setMode(OF_PRIMITIVE_LINES); 
		
		tested = false;

	}

	
	ofColor getColourForPoint(float distance, ofPoint& pos){
		if(colourSystem!=NULL) {
			return colourSystem->getColourForPoint(distance, pos);
		} else {
			return ofColor::white;
		}
		
		
	}
	
	
	~LaserPolyline() {
		// not sure if there's any point clearing the polyline or the
		// previewMesh - they should just get destroyed, right?
		polyline.clear();
		// assumes that this object owns the colourSystem object.
		// Bit nasty.
		if(colourSystem!=NULL) delete colourSystem;
		previewMesh.clear(); 
		
	}
	
	ofPolyline polyline;
	ofMesh previewMesh; 
	float intensity = 1;
	ofFloatColor colour;
	ColourSystem * colourSystem; 
		
};

