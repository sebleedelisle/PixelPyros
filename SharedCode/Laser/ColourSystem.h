//
//  ColourSystem.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 29/10/2013.
//
//
#pragma once

class ColourSystem {

	public :
	
	ColourSystem() {};
	
	virtual ofColor getColourForPoint(float unitProgress, ofPoint& pos) {
		return ofColor::white;
	}

};