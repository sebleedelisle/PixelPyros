//
//  ParticleSystemManager.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 09/09/2013.
//
//

#include "ParticleSystemManager.h"

ParticleSystemManager * ParticleSystemManager :: psm = NULL;
ParticleSystemManager * ParticleSystemManager::instance() {
	if(psm ==NULL) {
		psm = new ParticleSystemManager();
	}
	return psm;
}


ParticleSystemManager :: ParticleSystemManager() : soundPlayer(*SoundPlayer::instance()) {
    
	activeParticleCount = 0;
	activePhysicsObjectCount = 0;
	activeParticleSystemCount = 0; 
	spareParticleCount = 0;
	allParticleCount = 0;

    parameters.setName("Particle Manager");
    parameters.add( killAllParticlesParam.set("KILL ALL PARTICLES",false) );
	killAllParticlesFlag = false;
	
	particleScale = 1;
}



void ParticleSystemManager :: update(float deltaTime) {
	
	activeParticleCount = 0;
	allParticleCount = 0;

	activePhysicsObjectCount = 0;
	activeParticleSystemCount = 0;
	spareParticleCount = 0;
	
	
    /* cause single update delay before setting param back to false */
    if( killAllParticlesFlag ){
        killAllParticlesFlag = killAllParticlesParam = false;
    }
    
	if ( killAllParticlesParam )
	{
		killAllParticles () ;
        killAllParticlesFlag = true;
	}
	
	for(int i = 0; i<particleSystems.size(); i++) {
		
		ParticleSystem* ps = particleSystems[i];
		
		
		if(ps->finished) continue;
		
		ps->update(deltaTime);
		
		activeParticleCount+=ps->activeParticleCount;
		activeParticleSystemCount ++;
		
		if(ps->finished) {
			spareParticleSystems.push_back(ps);
		}
		
		
	}
	
	spareParticleCount = ParticleFactory::instance()->recycledParticles.size();
	allParticleCount = ParticleFactory::instance()->particlesInUse;
	
	for(int i = 0; i<physicsObjects.size(); i++) {
		
		PhysicsObject* po = physicsObjects[i];
		if(!po->isEnabled()) continue;
		activePhysicsObjectCount++;
		
		po->update(deltaTime);
		
		if(!po->isEnabled()) {
			sparePhysicsObjects.push_back(po);
		}
		
		
	}
	
	
	
}


void ParticleSystemManager ::draw() {
	
	
	for(int i = 0; i<particleSystems.size(); i++) {
		
		ParticleSystem* ps = particleSystems[i];
		if(ps->finished) continue;
		ps->draw(particleScale);
	}
	
	/*
	for(int i = 0; i<physicsObjects.size(); i++) {
		
		PhysicsObject* po = physicsObjects[i];
		if(!po->isEnabled()) continue;
		if(po->renderer == NULL) continue;
		
		po->renderer->render(po->pos, po->vel, po->life);
	}
	*/
	
}


void ParticleSystemManager::killPhysicsObject(PhysicsObject * po, bool killParticles){
	
	po->life.end();
	for(int i = 0; i<particleSystems.size(); i++) {
			
		ParticleSystem& ps = *particleSystems[i];
		if(ps.finished) continue; 
		
		if(ps.attachedPhysicsObject == po) {
			ps.life.end();
			if(killParticles) ps.killParticles();
		}
		
	}
	
	
}

void ParticleSystemManager ::killAllParticles ()
{
	for(int i = 0; i<particleSystems.size(); i++) {
		
		ParticleSystem* ps = particleSystems[i];
		if(ps->finished) continue;
		
		ps->life.end () ;
	}
	
}


ParticleSystem * ParticleSystemManager :: getParticleSystem() {
	
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


PhysicsObject * ParticleSystemManager :: getPhysicsObject() {
	
	PhysicsObject * po;
	if(sparePhysicsObjects.size()>0) {
		po = sparePhysicsObjects.back();
		sparePhysicsObjects.pop_back();
		po->reset();
	} else {
		
		po = new PhysicsObject();
		physicsObjects.push_back(po);
		po->reset(); 
	}
	
	return po;
	
	
}


PhysicsObject * ParticleSystemManager ::addRocket(RocketSettings& rs, ofVec3f& pos) {
	
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
	
	rocket->timeSpeed = rs.timeSpeed;
	rocket->pos.set(pos);
	rocket->lastPos.set(pos);
	rocket->life.lifeTime = rs.getLifeTime();
	
	for(int i = 0; i<rs.particleSystemSettings.size(); i++) {
		ParticleSystemSettings pss = rs.particleSystemSettings[i];
		
		ParticleSystem* ps = getParticleSystem();
		
		//pss.hueStartMin = pss.hueStartMax = ofRandom(255);
		ps->init(pss);
		ps->attachedPhysicsObject = rocket;
		ps->power = power;
		ps->scaleCentre = pos;
		
	}
	
	
	
	return rocket;
	
	
}
