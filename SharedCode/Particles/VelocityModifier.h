//
//  VelocityModifier.h
//  ParticlePlay5
//
//  Created by Seb Lee-Delisle on 18/08/2012.
//
//

#pragma once

#include "ofMain.h"
#include "PhysicsObject.h"
#include "VelocityModifierSettings.h"

class VelocityModifier {
	
	public:
	
	VelocityModifier() {
		
		active = false; 
		
	}

	void init(VelocityModifierSettings * settings) {
		rotateAroundStartPos = ofRandom(settings->minRotationAroundStartPos, settings->maxRotationAroundStartPos );
		rotateAxis = settings->rotateAxis;
		active = true;
		
	}
	
	
	void reset() {
		
		rotateAroundStartPos = 0;
		active = false; 
		
	}
	
	void update(float deltaTime, PhysicsObject *p, ofVec3f& startPos) {
		if(!active) return; 
		if(rotateAroundStartPos!=0) {
			
			p->pos.rotate(rotateAroundStartPos*deltaTime, startPos, rotateAxis);
			p->vel.rotate(rotateAroundStartPos*deltaTime, rotateAxis);
			
		}
		
		
	};

	
	float rotateAroundStartPos;
	ofVec3f rotateAxis;
	bool active; 


};