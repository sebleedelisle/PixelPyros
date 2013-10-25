//
//  Asteroid.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 03/10/2013.
//
//

#include "Asteroid.h"


Asteroid :: Asteroid(float x, float y, float r) {
	reset(x, y, r);
}

void Asteroid :: reset(float x, float y, float r) {

	pos.set(x, y);
	vel.set(3,0);
	float angle = ofRandom(5,30);
	if(ofRandom(1)<0.5) angle = -angle; 
	vel.rotate(angle, ofPoint(0,0,1));
	if(ofRandom(1)<0.5) vel.x*=-1;

	updateSize(r);
	enabled = true; 
}

void Asteroid :: update(float deltaTime, ofRectangle playRect) {
	
	pos+=(vel*50*deltaTime);
	
	if(pos.x - radius>playRect.getRight()) {
		pos.x = playRect.getLeft()-radius;
		if (pos.y>playRect.getTop() + playRect.height*0.7) {
			pos.y = ofRandom(playRect.getTop(), playRect.getTop() + playRect.height/2);
		}
			
	} else if (pos.x+radius<playRect.getLeft()) {
		pos.x = playRect.getRight()+radius;
		if(pos.y>playRect.getTop() + playRect.height*0.7) {
			pos.y = ofRandom(playRect.getTop(), playRect.getTop() + playRect.height/2);
		}
	}
	
	if(pos.y - radius > playRect.getBottom()) {
		pos.y = playRect.getTop()-radius;
	} else if(pos.y + radius < playRect.getTop()) {
		pos.y = ofRandom(playRect.getTop(), playRect.getTop() + playRect.height/2);
		if(vel.x<0) pos.x = playRect.getRight()+radius;
		else pos.x = playRect.getLeft()-radius;
	}
	
}

void Asteroid::draw() {
	
	ofPushMatrix();
	ofTranslate(pos); 
	ofPushStyle();
	ofSetColor(128);
	ofSetLineWidth(1);
	ofNoFill();
	shape.draw();
	ofSetColor(128);
	ofSetLineWidth(3);
	shape.draw();
	
	ofPopStyle();
	ofPopMatrix();
	
}

void Asteroid :: updateSize(float r) {
	radius = r;
	shape.clear();
	shape.setMode(OF_PRIMITIVE_LINE_LOOP); 
	float angle = 0;
	int counter = 0; 
	while(angle<360) {
		ofPoint p(r,0);
		if((counter++)%2 == 0) p.set(ofRandom(r*0.5,r),0);
		p.rotate(angle,ofPoint(0,0,1));
		shape.addVertex(p);
		angle+=ofRandom(10,40);
	}
}