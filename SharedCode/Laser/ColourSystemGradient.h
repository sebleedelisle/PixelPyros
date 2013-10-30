//
//  ColourSystemGradient.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 29/10/2013.
//
//

#pragma once

#include "ColourSystem.h"
#include "ColourStop.h"

class ColourSystemGradient : public ColourSystem {
	
	public:
	
	ColourSystemGradient(){};
	
	ofColor getColourForPoint(float unitProgress, ofPoint& ignored) {
		
		if(colourStops.size() == 0) return ofColor::red;
		
		int index = 0;
		
		ofColor returnColour;
		
		
		while((index<colourStops.size() && (colourStops[index].position<unitProgress))){
			returnColour = colourStops[index].colour;
			index++;
		}
		
		return returnColour;
			
	}
	
	void addColourStop(ofColor c, float pos) {
		colourStops.push_back(ColourStop(c, pos));
		sort(colourStops.begin(), colourStops.end());
	}
	
	// remaps the vector by dividing every position by the total
	// length - a bit of a bodge - should only be called once.
	void setLength(float length) {
		
		for(int i = 0; i<colourStops.size(); i++) {
			colourStops[i].position/=length;
		}
	}
	
	vector<ColourStop> colourStops;


};