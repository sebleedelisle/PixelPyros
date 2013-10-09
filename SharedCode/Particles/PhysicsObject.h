//
//  Physics.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 30/07/2012.
//  Copyright (c) 2012 seb.ly. All rights reserved.
//
#pragma once
#include "ofMain.h"
#include "LifeCycle.h"

class PhysicsObject { 

	public : 
	
	PhysicsObject();
	
	virtual void reset();
	
	virtual bool update(float deltaTime);
	
	bool isEnabled(); 
	
	ofVec3f pos; 
	ofVec3f lastPos; 
	ofVec3f vel;
	
	ofVec3f velScalar;

	float timeSpeed; 
	
	float drag; 
	ofVec3f	gravity; 
	
	LifeCycle life;
	
	
	int dragApplyCount;
	float dragApplyFrequency; 
	float elapsedTime;
	

	
	protected:
	
	bool enabled;
	
	
};