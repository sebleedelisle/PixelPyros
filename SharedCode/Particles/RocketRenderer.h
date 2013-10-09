//
//  RocketRenderer.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 08/10/2013.
//
//

#pragma once

#include "ofMain.h"

class RocketRenderer {
	public :
	
	
	virtual void render(ofVec3f pos, ofVec3f vel, LifeCycle& life) {
		
		ofPushStyle();
		ofNoFill();
		ofSetColor(255);
		ofCircle(pos, 10 * (1-life.getProgress()));
		ofPopStyle();
		
	};
	
	
};