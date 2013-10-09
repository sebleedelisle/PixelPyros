//
//  RocketRendererWiggle.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 08/10/2013.
//
//

#include "RocketRendererWiggle.h"

void RocketRendererWiggle :: render(ofVec3f pos, ofVec3f vel, LifeCycle &life){
	float frameTime = 1.0/50.0;
	
	float speed = 30;
	
	
	ofPath laserPath;
	laserPath.setMode(ofPath::COMMANDS);
	laserPath.setStrokeWidth(2);
	laserPath.setPolyWindingMode(OF_POLY_WINDING_POSITIVE);
		
	
	//laserPath.draw(300,300);
	
		
	ofPushStyle();
	ofNoFill();
	ofSetColor(255,0,0);
	
	ofVec3f lateralVector = vel;
	lateralVector.normalize();
	lateralVector.rotate(90,ofVec3f(0,0,1));
	
	int numTrails = 15;
	
	for(int i = 0; i<numTrails; i++) {
		
		float oscillationamount = i*0.2;
		float oscoffset = (life.elapsedTime + (frameTime*i)) * speed;
		//float size = (1 - Cubic::easeOut((float)i/(float)numTrails,0, 1, 1)) * 20;
		float size = ofMap(i,numTrails, 0, 1, 1) ;
		
		ofVec3f lateraloffset = lateralVector * sin(oscoffset) * oscillationamount;
		
		
		//ofCircle(pos - (vel*i*frameTime*1.2) + lateraloffset, (numTrails-i) *0.3);
		laserPath.circle(pos - (vel*i*frameTime*1.5) + lateraloffset, size);
	}
	
	//laserPath.draw(0,0);
	vector<ofPolyline> outlines = laserPath.getOutline();
	
	for(int i = 0; i<outlines.size(); i++) {
		ofPolyline line = outlines[i];
		//line.simplify(5);
		line.draw();
	}

	
	ofPopStyle();
	
}