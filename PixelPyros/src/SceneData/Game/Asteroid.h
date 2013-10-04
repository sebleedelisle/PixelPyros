//
//  Asteroid.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 03/10/2013.
//
//

#pragma once

#include "ofMain.h"

class Asteroid {

	public :
	
	Asteroid(float x, float y, float radius);
	
	void update(float deltaTime, ofRectangle playRect);
	void draw();
	
	void reset(float x, float y, float radius); 
	
	void updateSize(float newsize);
	
	
	ofPoint pos, vel;
	float radius;
	ofMesh shape;
	bool enabled = true; 


};