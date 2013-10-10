//
//  ParticleSystem.cpp
//  ParticlePlay3
//
//  Created by Seb Lee-Delisle on 31/07/2012.
//  Copyright (c) 2012 seb.ly. All rights reserved.
//

#include "ParticleSystem.h"

ParticleSystem::ParticleSystem (SoundPlayer& sp) : soundPlayer(sp){

	life.lifeTime = 10; 
	life.delay = 0; 
	reset();
	
//	attachedPhysicsObject = NULL;
	
}

void ParticleSystem::reset(){ 
	
	life.reset(); 
	numParticlesCreated = 0; 
	finished = false;
	power = 1;
	attachedPhysicsObject = NULL; 
	
	rotateAmount = 0;
}


bool ParticleSystem::update(float deltaTime) { 
	
	deltaTime*=settings.timeSpeed;
	
	life.update(deltaTime); 
	

	
	if(attachedPhysicsObject!=NULL) { 
		
		pos = attachedPhysicsObject->pos; 
		if(!attachedPhysicsObject->isEnabled()) {
			
			//cout << "WHAT THE ACTUAL? " <<endl;
			
			
		}
		
	}
	
	if(life.active && (life.elapsedTime-deltaTime <= life.delay)){
		
		if(settings.startSound!="") {
			float pan = (pos.x - ofGetWidth()/2)/ (ofGetWidth()/2);
		
			//cout << "pan " << pan << endl;
			float volume = 1;
			if(attachedPhysicsObject!=NULL) {
				//volume = ofMap(attachedPhysicsObject->vel.length(), 200,3000,0,1,true);
				volume = power*0.8+0.2;
				//cout << "volume "<< volume << " " << attachedPhysicsObject->vel.length() << endl;
				
			}
			soundPlayer.playSound(settings.startSound, volume , pan);
		}
	}
	
	
	if(life.active) {
		
		int newparticlecount = 0;
		
		if(settings.emitMode == PARTICLE_EMIT_CONTINUOUS) {
			newparticlecount = (life.elapsedTime-life.delay)*settings.emitCount;
		} else if (settings.emitMode == PARTICLE_EMIT_BURST) {
			newparticlecount = settings.emitCount;
			if(settings.emitShape!=NULL) {
				newparticlecount = settings.emitShape->getNumVertices(); 
			}
			life.end();
		}
		
		while(numParticlesCreated<newparticlecount){
			Particle& p = *addParticle();
			
				
			if(attachedPhysicsObject!=NULL) {
				if(settings.emitMode == PARTICLE_EMIT_CONTINUOUS) {
					p.pos = ((attachedPhysicsObject->pos - attachedPhysicsObject->lastPos) * ofMap(numParticlesCreated/settings.emitCount, life.lastUpdateTime, life.elapsedTimeActual,0,1)) + attachedPhysicsObject->lastPos;
				} else {
					p.pos = attachedPhysicsObject->pos;
				}
			} else {
				p.pos = pos;
			}
		}
	
	}
	
    activeParticleCount = 0; 
	
	for(std::vector<Particle *>::iterator it = particles.begin(); it != particles.end(); ++it) {
		
		Particle& p = **it; // *(particles[i]);
		
		if(!p.enabled) continue;
		p.update(deltaTime); 
		if(!p.enabled) {
			// add to spares... 
			spareParticles.push_back(&p);
		}
		
		activeParticleCount++;
	}
	finished = ((activeParticleCount ==0) && (life.isFinished())); 
	return finished; 
}

bool ParticleSystem::draw() { 
	
	if(settings.renderer!=NULL)
		settings.renderer->renderParticles(particles);
	else 
		defaultRenderer.renderParticles(particles);
	
}

Particle* ParticleSystem :: addParticle() { 
	
	Particle * p ;
	
	if(spareParticles.size() > 0 ){
		p = spareParticles.back(); 
		spareParticles.pop_back();
	} else { 
		
		p = new Particle(); 
	
		particles.push_back(p); 
	}
	
	numParticlesCreated++; 
	initParticle(p);
	return p; 

}

Particle * ParticleSystem::initParticle(Particle * p) { 
	
	
	p->reset(); 
	
	
	p->pos =  pos;
	p->startPos = p->pos;

	
	settings.initVelocity(p->vel, numParticlesCreated);
	
	if(settings.emitSpeedModifier!=1) { 
		p->vel *= ofMap(life.unitLifeProgress, 0, 1, 1, settings.emitSpeedModifier);
	}
	
	if(attachedPhysicsObject!=NULL){
		
		if(settings.emitInheritVelocity!=0) {
			p->vel += (attachedPhysicsObject->vel*settings.emitInheritVelocity);
		}
			
	}
	
	p->drag = settings.drag; 
	p->gravity = settings.gravity; 

	p->life.lifeTime = ofRandom(settings.lifeMin, settings.lifeMax); 
	
	p->sizeStart = ofRandom(settings.sizeStartMin, settings.sizeStartMax); 
	
	if(settings.emitStartSizeModifier!=1) { 
		p->sizeStart *= ofMap(life.unitLifeProgress, 0, 1, 1, settings.emitStartSizeModifier);
	}
	
	p->sizeEnd = p->sizeStart * settings.sizeChangeRatio; 
	
	p->rotateAmount = rotateAmount;
	p->rotateAxis = settings.rotateAxis; 
	
	settings.initColourModifier(p->colourModifier, life);
	p->shimmerMin = settings.shimmerMin; 
	
	float curvedRandom = ofRandom(1);
	curvedRandom*=curvedRandom;
	curvedRandom*=curvedRandom;

	p->renderDelay = ofMap(curvedRandom, 0, 1, settings.renderDelayMin, settings.renderDelayMax);
	p->velocityModifier.reset();
	
	if(settings.velocityModifierSettings!=NULL) {
		p->velocityModifier.init(settings.velocityModifierSettings);
	}
	
	if(settings.renderer!=NULL) {
		p->historyCount = settings.renderer->historyCount;
	}
	
	return p;
	
}

void ParticleSystem :: addParticles(int count) { 
	for(int i =0; i<count; i++) {
		addParticle(); 
	}
}


void ParticleSystem:: init(ParticleSystemSettings& pes) {

	reset(); 
	
	life.delay = pes.emitDelay; 
	life.lifeTime = pes.emitLifeTime; 
	//attachedPhysicsObject = pes.emitAttachedPhysicsObject;
	
	//physics.drag = pes.drag; 
	//physics.gravity = pes.gravity; 
	settings = pes;
	
	rotateAmount = ofRandom(settings.rotateMin, settings.rotateMax);
	
	
	
	
	
}
