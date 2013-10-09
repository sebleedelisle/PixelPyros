//
//  LifeCycle.h
//  ParticlePlay3
//
//  Created by Seb Lee-Delisle on 31/07/2012.
//  Copyright (c) 2012 seb.ly. All rights reserved.
//

#pragma once

class LifeCycle { 
	
	public : 
	
	LifeCycle() { 
		
		lifeTime = 1; 
		delay = 0; 
		reset(); 
		
	};
	
	void reset() { 
		
		lastUpdateTime = 0; 
		elapsedTime = 0; 
		active = false; 
		
	};
	
	bool update(float deltaTime) { 
		lastUpdateTime = elapsedTimeActual; 
		
		elapsedTime +=deltaTime; 
		
		if((elapsedTime>delay) && (elapsedTime<delay+lifeTime)) { 
			active = true; 
		} else { 
			active = false; 
		}
		
		unitLifeProgress = ofMap(elapsedTime, delay, delay+lifeTime, 0,1,true); 
		elapsedTimeActual = elapsedTime - delay;
		
		return active; 
	};
	
	bool isFinished() { 
		
		return (elapsedTime>delay+lifeTime); 
			
	}
	
	void end() {
		elapsedTime = delay+lifeTime;
	}
	void resetElapsedTime() {
		unitLifeProgress = 0;
		elapsedTimeActual = 0;
		elapsedTime = 0; 
		
	}
	
	float getProgress() {
		return ofMap(elapsedTime, delay, delay+lifeTime, 0, 1, true); 
		
	}
	
	
	bool active; 
	float lifeTime; 
	float elapsedTime; 
	// time since started
	float elapsedTimeActual; 
	float lastUpdateTime; 
	float unitLifeProgress; 
	float delay; 
	
}; 

