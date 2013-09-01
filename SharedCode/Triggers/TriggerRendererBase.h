//
//  TriggerRendererBase.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 27/08/2013.
//
//

#pragma once
class Trigger;

class TriggerRendererBase {

	float elapsedTime;
	public :
	
	virtual void draw(float elapsedtime, ofVec3f pos, float radius, ofColor colour, float unitPower, bool active ) {

		//elapsedTime+=deltaTime;
		
		ofPushStyle();
		ofNoFill();
		
		ofSetColor(colour);
		if(!active) ofSetColor(ofColor::gray);

		ofCircle(pos, radius);
		
		//ofCircle(pos, radius*unitPower);
		
		path.clear();
		path.setFillColor(colour);
				path.setCircleResolution(12);
		path.arc(pos, radius*unitPower, radius*unitPower, -90, -90 + unitPower*360);
		

		path.draw();

		
		if(!active) {
		
			ofSetColor(ofColor::red);
			ofRect(pos, radius, radius);
			
			
		}
		
		ofPopStyle();
		
	}

	ofPath path;
	

};