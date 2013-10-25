//
//  LaserCircle.h
//
//  Created by Seb Lee-Delisle on 01/08/2013.
//
//

#pragma once

#include "LaserShape.h"

class LaserCircle : public LaserShape{
	
	public :
	
	LaserCircle(const ofPoint& position, ofFloatColor& colour, float circleRadius, float circleIntensity = 1, float overlap = 0){
		reversable = true; 
		set(position, colour, circleRadius, circleIntensity, overlap);
	}
	
	void set(const ofPoint& position, ofFloatColor& circleColour, float circleRadius, float circleIntensity = 1, float overlap = 0) {
		colour = circleColour;
		
		radius = circleRadius;
		
		pos = position;
		
		if(overlap>0) {
			
			float circumference = PI*2*radius;
			overlapDistance = overlap; 
			overlapAngle = overlap / circumference * 360;
			
			startPos.set(0,-radius);
			endPos = startPos;
			startPos.rotate(-overlapAngle/2, ofPoint(0,0,1));
			startPos+=pos;
			endPos.rotate(overlapAngle/2, ofPoint(0,0,1));
			endPos+=pos;
			
			
		} else {
			
			startPos = pos;
			startPos.y-=radius;
			
			endPos = startPos;
			
		}
		
		
		
		//cout<<"CIRCLE SET : " << pos << " " << startPos << " " << endPos << " " << radius<< endl;
		
		
		intensity = circleIntensity;
		tested = false;
	}
//	
//	void renderPreview() {
//			
//		ofSetColor(colour);
//		ofSetLineWidth(2);
//		if(radius<10) ofNoFill();
//		else ofFill();
//		
//		ofCircle(pos, radius);
//		ofColor dimColour = colour;
//		dimColour.r*=0.5;
//		dimColour.g*=0.5;
//		dimColour.b*=0.5;
//		
//		if(radius<20) ofNoFill();
//		else ofFill();
//		
//		ofSetColor(dimColour);
//		ofSetLineWidth(4);
//		ofCircle(pos, radius);
//		
//		dimColour.r*=0.3;
//		dimColour.g*=0.3;
//		dimColour.b*=0.3;
//		
//		if(radius<30) ofNoFill();
//		else ofFill();
//		
//		ofSetColor(dimColour);
//		ofSetLineWidth(8);
//		ofCircle(pos, radius);
//		
//		
//		
//		
//	}
//		
	float intensity = 1;
	float overlapAngle = 0;
	float overlapDistance = 0; 
	ofFloatColor colour;
	
	ofPoint pos;
	float radius; 
		
};

