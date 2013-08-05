//
//  ParticleSystemManager.h
//
//  Created by Seb Lee-Delisle on 03/08/2012.
//  Copyright (c) 2012 seb.ly. All rights reserved.
//

#pragma once

#include "ParticleSystem.h"


// There probably should only be one ParticleSystemManager. It's responsible for
// looking after all the ParticleSystems. Each Particle effect should have its own
// ParticleSystem, which looks after how the particles are emitted.
//
// The ParticleSystemManager is responsible for creating and recycling ParticleSystems,
// as well as updating and rendering each one.
//
// In what appears to be some fairly horrific code architecture, it also looks after
// PhysicsObjects, whose purpose appears to be to control the position of Rockets.


class ParticleSystemManager { 

public:
	
    ParticleSystemManager(SoundPlayer& sp) : soundPlayer(sp) {
    
        activeParticleCount = 0;
		activePhysicsObjectCount = 0; 
        
    }
	
	void update(float deltaTime) {
		
        activeParticleCount  =0 ; 
		
		
		activePhysicsObjectCount = 0;
		
		if ( killAllParticlesFlag )
		{
			killAllParticles () ;
			killAllParticlesFlag = false ;
		}
		
		for(int i = 0; i<particleSystems.size(); i++) { 
			
			ParticleSystem* ps = particleSystems[i]; 
			if(ps->finished) continue; 
			
			
			ps->update(deltaTime);
			
	        activeParticleCount+=ps->activeParticleCount;
			
			if(ps->finished) { 
				spareParticleSystems.push_back(ps); 
			}
			
			
		}
		
		for(int i = 0; i<physicsObjects.size(); i++) {
			
			PhysicsObject* po = physicsObjects[i];
			if(!po->enabled) continue;
			activePhysicsObjectCount++;
			
			po->update(deltaTime);
			
			if(!po->enabled) {
				sparePhysicsObjects.push_back(po);
			}
			
			
		}
		
		
		
	}
	
	void draw() { 
		
		
		for(int i = 0; i<particleSystems.size(); i++) { 
			
			ParticleSystem* ps = particleSystems[i]; 
			if(ps->finished) continue; 
		
			ps->draw(); 
		}

		
	}
	
	void killAllParticles ()
	{
		for(int i = 0; i<particleSystems.size(); i++) { 
			
			ParticleSystem* ps = particleSystems[i]; 
			if(ps->finished) continue; 
			
			ps->life.end () ;
		}

	}
	
	ParticleSystem * getParticleSystem() { 
		
		ParticleSystem * ps; 
		if(spareParticleSystems.size()>0) {
			ps = spareParticleSystems.back(); 
			spareParticleSystems.pop_back();
			ps->reset();
		} else { 
			
			ps = new ParticleSystem(soundPlayer); 
			particleSystems.push_back(ps); 
		
		}
		
		return ps; 
		
				
	}
	
	PhysicsObject * getPhysicsObject() { 
		
		PhysicsObject * po; 
		if(sparePhysicsObjects.size()>0) {
			po = sparePhysicsObjects.back(); 
			sparePhysicsObjects.pop_back(); 
			po->reset(); 
		} else { 
			
			po = new PhysicsObject(); 
			physicsObjects.push_back(po); 
			
		} 
		
		return po; 
		
		
	}
	
	PhysicsObject * addRocket(RocketSettings& rs, ofVec3f& pos) {
		
		PhysicsObject *rocket = getPhysicsObject();
		
		float power = ofRandom(1);
		
		// if it's an ordinary physics object
		if(rs.mode == ROCKET_MODE_PHYSICS) {
			rocket->vel.set(ofMap(power, 0, 1, rs.startSpeedMin, rs.startSpeedMax),0,0);
			rocket->vel.rotate(0,0,ofRandom(rs.direction - rs.directionVar, rs.direction+rs.directionVar));
			rocket->gravity = rs.gravity;
			rocket->drag = rs.drag;
			
		// slightly nasty hack for the rockets that have to end up in a
		// particular place (like the letters) 
		} else if(rs.mode == ROCKET_MODE_TARGET) {
			rocket->drag = 1;
			rocket->gravity.set(0,0,0);
			rocket->vel = (rs.targetPos - pos) / rs.targetSpeed;
			//cout << "rocket vel " << rocket->vel.x << " " << rocket->vel.y << endl;
			
			
		}
		
		
		rocket->pos.set(pos);
		rocket->lastPos.set(pos);
		rocket->life.lifeTime = rs.lifeTime;
		
		for(int i = 0; i<rs.particleSystemSettings.size(); i++) {
			ParticleSystemSettings pss = rs.particleSystemSettings[i];
			
			ParticleSystem* ps = getParticleSystem();
			
			//pss.hueStartMin = pss.hueStartMax = ofRandom(255);
			ps->init(pss);
			ps->attachedPhysicsObject = rocket;
			ps->power = power;
		}
		
		
		
		return rocket; 
		
		
	}

	vector <ParticleSystem *> particleSystems; 
	vector <ParticleSystem *> spareParticleSystems; 

	vector <PhysicsObject *> physicsObjects; 
	vector <PhysicsObject *> sparePhysicsObjects; 

	bool killAllParticlesFlag;
	
    int activeParticleCount;
	int activePhysicsObjectCount;
	
	SoundPlayer& soundPlayer;


};