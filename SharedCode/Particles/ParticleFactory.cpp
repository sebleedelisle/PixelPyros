//
//  ParticleFactory.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 10/10/2013.
//
//

#include "ParticleFactory.h"

ParticleFactory * ParticleFactory :: _instance = NULL;

ParticleFactory * ParticleFactory::instance() {
	if(_instance == NULL) {
		_instance = new ParticleFactory();
	}
	return _instance;
}


ParticleFactory :: ParticleFactory() {

	particlesInUse = 0;
	
}


Particle * ParticleFactory :: getParticle() {
	
	Particle * p;
	
	if(recycledParticles.size()>0) {
		p = recycledParticles.back();
		recycledParticles.pop_back();
		p->reset();
	} else {
		p = new Particle();
	}
	

	particlesInUse++;
	
	return p;
	
}

void ParticleFactory:: recycleParticle(Particle * particle) {
	
	// should we do some error checking here?
	
	recycledParticles.push_back(particle);
	particlesInUse --;
	
	
}
