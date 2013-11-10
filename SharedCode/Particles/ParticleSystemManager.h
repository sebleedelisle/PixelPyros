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
	
	static ParticleSystemManager * instance();
	static ParticleSystemManager * psm;
	
    ParticleSystemManager();
	void update(float deltaTime);
	void draw();
	void killAllParticles ();
	ParticleSystem * getParticleSystem();
	PhysicsObject * getPhysicsObject() ;
	void killPhysicsObject(PhysicsObject * po, bool killParticles = false);
	
	PhysicsObject * addRocket(RocketSettings& rs, ofVec3f& pos);
	vector <ParticleSystem*> particleSystems; 
	vector <ParticleSystem*> spareParticleSystems;

	vector <PhysicsObject*> physicsObjects;
	vector <PhysicsObject*> sparePhysicsObjects;
    bool killAllParticlesFlag;
    
	ofParameter<bool> killAllParticlesParam;
    
    ofParameterGroup parameters;
	
    int activeParticleCount;
	int activePhysicsObjectCount;
	int activeParticleSystemCount;
	int spareParticleCount;
	int allParticleCount;
	ofParameter<float> particleScale;
	
	SoundPlayer& soundPlayer;


};