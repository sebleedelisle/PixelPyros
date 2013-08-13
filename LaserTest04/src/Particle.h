//
//  Star.h
//  ofxIlda example basic
//
//  Created by Seb Lee-Delisle on 01/08/2013.
//
//

#pragma once

class Particle : public ofPoint{
	
	public :
	
	Particle() {
		reset(); 
	};
	
		
	void update() {
		
		float deltaTime = ofGetLastFrameTime()*2;
		//cout << deltaTime << "\n";
		if(delay>0) {
			delay -=deltaTime;
		} else {
			this->operator+=(velocity * deltaTime);
			//velocity*=0.98;
			velocity.y+=deltaTime * 100;
			life+=deltaTime;
			brightness -= 0.2 * deltaTime;
			
			if(life>5) {
				reset();
			}
			
		}
	}

	void draw() {
		ofFill();
		ofSetColor(ofColor::white);
		ofCircle(*this,5*brightness);
		
		
		
	}
	
	void reset() {
		this->set(round(ofRandom(2,8)) * ofGetWidth()/10, ofGetHeight()*0.9);
		velocity.set(0,ofRandom(-300,-320));
		velocity.rotate(ofRandom(-1,1), ofVec3f(0,0,1));
		
		brightness = 1; 
		life = 0;

	}
	
	ofPoint velocity;
	float life = 0;
	float delay = 0;
	float brightness = 1; 

	
};

