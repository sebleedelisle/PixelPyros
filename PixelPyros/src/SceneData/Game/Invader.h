//
//  Invader.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 28/09/2013.
//
//
#pragma once 

#include "ofMain.h"

class Invader {

	public :
	
	Invader(ofImage* img, int w, int h) {
		
		image = img;
		enabled = true;
		scale = 1;
		counter = 0;
		width = w;
		height = h;
		frame = 0;
		frameCount = floor(image->getWidth()/w);
		
	}
	
	void update() {
		counter++;
		if(counter%5 == 0) {
			pos+=vel;
			frame++;
			if(frame>=frameCount) frame = 0;
		}
		
	}
	
	void draw() {
	
		ofPushStyle();
		ofPushMatrix();
		ofTranslate(pos);
		ofScale(scale, scale);
		ofSetColor(colour); 
		image->drawSubsection(0, 0, width, height, frame*width, 0);
		ofPopMatrix();
		ofPopStyle();
	}

	ofRectangle getRect() {
		return ofRectangle(pos,width*scale, height*scale); 
	}

	ofVec3f pos, vel;
	int scale;
	int counter;
	bool enabled;
	int width, height;
	int frame;
	int frameCount;
	ofColor colour; 

	ofImage * image;


};