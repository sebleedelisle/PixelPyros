//
//  Invader.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 28/09/2013.
//
//
#pragma once 

#include "ofMain.h"
#include "Cubic.h"

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
	
	void update(bool doPositionChange) {
		counter++;
		
		if(delay>0) {
			delay--;
			offset.x = delay; // Cubic::easeOut(delay, 1000, 0, 1000);
			offset.y = -delay*4; // 0;//-delay*2;
			
		} else offset.set(0,0);
		
		if(doPositionChange) {

			pos+=vel;
			frame++;
			if(frame>=frameCount) frame = 0;
		}
		
	}
	
	void draw() {
	
		ofPushStyle();
		ofPushMatrix();
		ofTranslate(pos + offset);
		ofScale(scale, scale);
		ofSetColor(colour); 
		image->drawSubsection(0, 0, width, height, frame*width, 0);
	
		ofPopMatrix();
		ofNoFill();
		//ofRect(getRect());
		ofPopStyle();
		
	}

	ofRectangle getRect() {
		return ofRectangle(pos+offset,width*scale, height*scale);
	}

	ofVec3f pos, vel, offset;
	int scale;
	int counter;
	bool enabled;
	int width, height;
	int frame;
	int frameCount;
	ofColor colour;
	int hue;
	int delay = 0;

	ofImage * image;


};