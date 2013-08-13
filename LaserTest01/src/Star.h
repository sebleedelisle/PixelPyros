//
//  Star.h
//  ofxIlda example basic
//
//  Created by Seb Lee-Delisle on 01/08/2013.
//
//

#pragma once

class Star : public ofPoint{
	
	public :
	
	Star() {
		reset(); 
	};
	
		
	void update() {
		
		float deltaTime = ofGetLastFrameTime();
		//cout << deltaTime << "\n";
		if(delay>0) {
			delay -=deltaTime;
		} else {
			this->operator+=(velocity * deltaTime);
			//velocity*=0.98;
			velocity.y+=deltaTime * 300;
			life+=deltaTime;
			brightness -= 0.5 * deltaTime;
			
			if(life>2) {
				reset();
			}
			
		}
	}

	
	void reset() {
		this->set(ofGetWidth()/2, ofGetHeight()/2);
		velocity.set(0,ofRandom(-200,-400));
		velocity.rotate(ofRandom(-20,20), ofVec3f(0,0,1));
		
		brightness = 1; 
		life = 0;

	}
	
	ofPoint velocity;
	float life = 0;
	float delay = 0;
	float brightness = 1; 

	
};

