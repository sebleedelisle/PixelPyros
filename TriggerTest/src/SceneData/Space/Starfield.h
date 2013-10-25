//
//  Starfield.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 22/08/2012.
//
//

#pragma once

#include "constants.h"

class Starfield {
	public : 
	
	Starfield(int numStars = 5000) {
	
		for(int i = 0; i<numStars; i++) {
			stars.push_back(ofVec3f(ofRandom(-200,APP_WIDTH+200), ofRandom(-200,APP_HEIGHT+200), ofRandom(-2000,3000)));
			
			
			
		}
		speed = 300; 
		elapsedTime = 0; 
	}
	
	void update(float deltaTime) {
		
		for(std::vector<ofVec3f>::iterator it = stars.begin(); it != stars.end(); ++it) {
			ofVec3f& s = *it;
			//mesh.addVertex(s);
			//mesh.addColor(ofColor(ofRandom(200,255)));
			s.z+=deltaTime*speed;
			//s.y+=deltaTime*speed*0.1;
			if(s.z>3000) s.z-=5000;
			//s.y+=deltaTime*100;
			if(s.y>200+APP_HEIGHT) s.y-=APP_HEIGHT+400;
			
		}
		elapsedTime+=deltaTime;
		
		
	}
	
	void draw(float brightness = 1) {
		
		ofPushStyle(); 
		ofPushMatrix();
		//ofRotateY(sin(elapsedTime)*5);
		ofEnableBlendMode(OF_BLENDMODE_ADD);
		ofDisableSmoothing();
		ofTranslate(0,-200);
		ofRotateX(15);
		ofSetLineWidth(1);
		
		ofMesh mesh ;
		mesh.setMode(OF_PRIMITIVE_POINTS);

		
		for(std::vector<ofVec3f>::iterator it = stars.begin(); it != stars.end(); ++it) {
			ofVec3f& s = *it;
			mesh.addVertex(s);
			//mesh.addColor(ofColor::white);
			mesh.addColor(ofColor(ofMap(s.z,0,-2000,255,10,true ) * brightness));
			
		
		}
		
		mesh.draw();
		
		/*
		ofMesh mesh2 ;
		mesh2.setMode(OF_PRIMITIVE_LINES);
		
		
		for(int i = 0; i<stars.size(); i+=20) {
			ofVec3f& s = stars[i];
			mesh2.addVertex(s-ofVec3f(-1,-1));
			mesh2.addColor(ofColor(ofMap(s.z,0,-2000,200,10,true )));
			mesh2.addVertex(s-ofVec3f(1,1));
			mesh2.addColor(ofColor(ofMap(s.z,0,-2000,200,10,true )));
			mesh2.addVertex(s-ofVec3f(1,-1));
			mesh2.addColor(ofColor(ofMap(s.z,0,-2000,200,10,true )));
			mesh2.addVertex(s-ofVec3f(-1,1));
			mesh2.addColor(ofColor(ofMap(s.z,0,-2000,200,10,true )));
			
			
		}
		
		mesh2.draw();
*/
		
		ofPopMatrix();
		ofPopStyle();
		
	}
	
	
	
	vector <ofVec3f> stars;
	
	float elapsedTime;
	float speed; 
	
	
	
};