//
//  VelocityModifierSettings.h
//  ParticlePlay5
//
//  Created by Seb Lee-Delisle on 18/08/2012.
//
//


#pragma once

class VelocityModifierSettings{

	public :
	
	VelocityModifierSettings(float minrotation = 0 , float maxrotation = 0) {
		minRotationAroundStartPos = minrotation;
		maxRotationAroundStartPos = maxrotation;
		rotateAxis.set(0,1,0); 
	};
	
	float minRotationAroundStartPos;
	float maxRotationAroundStartPos;
	
	ofVec3f rotateAxis; 

};