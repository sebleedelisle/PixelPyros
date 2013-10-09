//
//  PhysicsObject.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 08/10/2013.
//
//

#include "PhysicsObject.h" 

PhysicsObject::PhysicsObject() {
	reset();
	
	dragApplyFrequency = 30;
	pos.set(0,0,0);
	lastPos.set(0,0,0);
	vel.set(0,0,0);
	drag = 1;
	gravity.set(0,0,0);
	velScalar.set(1,1,1);
	
	timeSpeed =1;
	
}

void PhysicsObject::reset() {
	dragApplyCount = 0;
	elapsedTime = 0;
	enabled = true;
	
	dragApplyFrequency = 30;
	pos.set(0,0,0);
	lastPos.set(0,0,0);
	vel.set(0,0,0);
	drag = 1;
	gravity.set(0,0,0);
	velScalar.set(1,1,1);
	
	timeSpeed =1;
	life.reset();
}

bool PhysicsObject::update(float deltaTime) {
	
	deltaTime*=timeSpeed;
	
	life.update(deltaTime);
	
	lastPos = pos;
	vel+=gravity*deltaTime;
	pos+=vel*deltaTime*velScalar;
	elapsedTime+=deltaTime;
	
	while((elapsedTime * dragApplyFrequency) > dragApplyCount) {
		vel*=drag;
		dragApplyCount++;
		
		// how to make velocity rotate!
		//vel.rotate(cos(dragApplyCount*0.9) *5 ,ofVec3f(0,0,1));

	}
	
	if(life.isFinished()) enabled = false;
	
	return enabled;
}

bool PhysicsObject::isEnabled(){
	return enabled;
}

