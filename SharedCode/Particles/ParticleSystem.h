//
//  ParticleSystem.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 30/07/2012.
//  Copyright (c) 2012 seb.ly. All rights reserved.
//


#pragma once


#include "Particle.h"
#include "ParticleSystemSettings.h"
#include "ParticleRendererBase.h"
#include "LifeCycle.h"
#include "SoundPlayer.h"
#include "RocketSettings.h"
#include "ParticleFactory.h"

class ParticleSystem { 

	public : 
	
	ParticleSystem(SoundPlayer& soundPlayer);
	
	void reset();
	void init(ParticleSystemSettings& pes);
	
	bool update(float deltaTime) ;
	
	void draw(float scale);
	
	void addParticles(int count);
	void killParticles(); 
	
	Particle * addParticle() ;
	Particle * removeParticle(Particle * p); 
	Particle * initParticle(Particle * p);
	Particle * getLastParticle(); 
	
	Particle * firstParticle;
	Particle * lastParticle;
	
	ofVec3f pos ;
	ofVec3f scaleCentre; 
	int numParticlesCreated; 
	
	bool finished; 
	
	LifeCycle life; 
	
	ParticleSystemSettings settings;
	
	PhysicsObject * attachedPhysicsObject; 
	
	int activeParticleCount;
	
	//string startSound;
	SoundPlayer& soundPlayer;
	
	float power;
	
	float rotateAmount;
		
	ParticleRendererShape defaultRenderer; 
	

}; 

