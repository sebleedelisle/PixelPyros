//
//  RocketSettings.h
//  ParticlePlay4
//
//  Created by Seb Lee-Delisle on 01/08/2012.
//  Copyright (c) 2012 seb.ly. All rights reserved.
//

#pragma once


typedef enum {
	ROCKET_MODE_PHYSICS,
	ROCKET_MODE_TARGET
} RocketMode;


class RocketSettings { 

	public:
	
	RocketSettings() { 
		
		startSpeedMin = 100; 
		startSpeedMax = 100; 
		direction = -90; 
		directionVar = 5;
		gravity.set(0,0,0); 
		drag = 1;
		lifeTime = 2;
		timeSpeed = 1;
		mode = ROCKET_MODE_PHYSICS;
		
		
		
	};

	ParticleSystemSettings * addParticleSystemSetting(const ParticleSystemSettings& pss) {
		
		particleSystemSettings.push_back(ParticleSystemSettings(pss));
		
		if(lifeTime <  pss.emitDelay + pss.emitLifeTime) {
			
			lifeTime = pss.emitDelay + pss.emitLifeTime;
			
		}
		
		return &particleSystemSettings.back(); 
		
	};
	
	ParticleSystemSettings* addParticleRenderer(ParticleRendererBase* renderer) {
		ParticleSystemSettings pss;
		pss.renderer = renderer;
		pss.gravity = gravity;
		pss.timeSpeed = timeSpeed;
		pss.emitMode = PARTICLE_EMIT_BURST;
		pss.emitCount = 1;
		pss.drag = drag;
		pss.emitInheritVelocity = 1;
		pss.speedMax = pss.speedMin = 0;
		pss.directionYVar = pss.directionZVar = 0;
		pss.lifeMin = pss.lifeMax = lifeTime;
		
		ParticleSystemSettings * pssref = addParticleSystemSetting(pss);
		return pssref; 

	}
	
	void setLifeTime(float lifetime) {
		
		lifeTime = lifetime;
		// TODO - CHECK THAT IT'S NOT SHORTER THAN ANY PSS!
		for(int i = 0; i<particleSystemSettings.size(); i++) {
			
			ParticleSystemSettings& pss = particleSystemSettings[i];
			
			if(lifeTime <  pss.emitDelay + pss.emitLifeTime) {
				
				lifeTime = pss.emitDelay + pss.emitLifeTime;
				
			}
			
		}
		
	}
	float getLifeTime() {
		
		// TODO - CHECK THAT IT'S NOT SHORTER THAN ANY PSS!
		return lifeTime; 
	}
	
	
	float startSpeedMin; 
	float startSpeedMax; 
	float direction; 
	float directionVar;
	
	float timeSpeed; 
	
	ofVec3f gravity; 
	float	drag;
	
	RocketMode mode; 
	
	ofVec3f targetPos;
	float targetSpeed;
	
	vector <ParticleSystemSettings> particleSystemSettings;

	
	protected :
	float lifeTime;
	

}; 