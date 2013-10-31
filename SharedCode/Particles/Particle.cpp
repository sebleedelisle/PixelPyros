//
//  Particle.cpp
//  ParticlePlay3
//
//  Created by Seb Lee-Delisle on 31/07/2012.
//  Copyright (c) 2012 seb.ly. All rights reserved.
//

#include "Particle.h"

Particle::Particle() : PhysicsObject() {
	reset(); 
	//renderer = new ParticleRendererBase();
	//colourModifier = new ColourModifier();
	//velocityModifier = new VelocityModifier();
	
}

void Particle::reset() { 
	//life.reset();
	
	PhysicsObject::reset();
	
	sizeStart = 10; 
	sizeEnd = 0; 
	shimmerMin = 0.2;
	
	renderDelay = 0;
	rotateAmount = 0;
	rotateAxis.set(0,1,0);
	
	velocityModifier.reset();
	
	enabled = true;
	startPos = pos;
	
	historySaveFrequency = 30;
	historySaveCount = 0; 
	
	historyPositions.clear();
	historyColours.clear();
	historyCount = 0;
	
	next = NULL;
	previous = NULL;

}


bool Particle :: update(float deltaTime) { 
	if(!enabled) return false;
	
	enabled = PhysicsObject::update(deltaTime);
	
	deltaTime*=timeSpeed;
	
	velocityModifier.update(deltaTime, this, startPos);
		
	// This system is a bit sucky. 
	if(renderDelay>0) {
		life.resetElapsedTime();
		size = 0;
		renderDelay-=deltaTime;
	} else {
		size = ofMap(life.unitLifeProgress, 0, 1, sizeStart, sizeEnd, true);
	}
    
	if(shimmerMin!=1) {
		size = ofMap(ofRandom(1),0,1,size*shimmerMin, size);
	}
    
	colourModifier.update(life.unitLifeProgress);
	
	if(rotateAmount!=0) {
		pos.rotate(rotateAmount*deltaTime, startPos, rotateAxis);
		vel.rotate(rotateAmount*deltaTime, rotateAxis);
	}
	

	if(historyCount>0) {

		while((elapsedTime * historySaveFrequency) > historySaveCount) {
			historySaveCount++;
			if(enabled) {
				historyPositions.push_back(pos);
				historyColours.push_back(getColour());
				
				while(historyPositions.size()>historyCount){
					historyPositions.pop_front();
					historyColours.pop_front();
				}
			}
			else if(historyPositions.size()>0){
				historyPositions.pop_front();
				historyColours.pop_front();
				
			}
		}
	}
	
	if(historyPositions.size()>0) enabled = true;
	return enabled; 
}

ofColor& Particle:: getColour() {
    return colourModifier.colour;

}