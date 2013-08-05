//
//  Pattern.h
//  ParticlePlay5
//
//  Created by Seb Lee-Delisle on 20/08/2012.
//
//

#pragma once

#include "TriggerRocket.h"

class TriggerPattern  {

	
	public :
	
	template <typename T>
	T* addTrigger(T& trigger, float verticalPos = 0, float verticalPosVariation = 0, float horizSpacing = 1){
		
		
		triggers.push_back(new T(trigger));
		verticalPositions.push_back(verticalPos);
		verticalVariations.push_back(verticalPosVariation);
		horizSpacings.push_back(horizSpacing); 
				
	}

	vector <TriggerBase* > triggers;
	vector <float> verticalPositions;
	vector <float> verticalVariations;
	vector <float> horizSpacings;


};