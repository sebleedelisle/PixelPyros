//
//  ParticleFactory.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 10/10/2013.
//
//

#include "ofMain.h"
#include "Particle.h"

class ParticleFactory {

	public :
	static ParticleFactory * instance();
	
	
	ParticleFactory();
	
	Particle* getParticle();
	
	void recycleParticle(Particle* particle);

	
	vector<Particle*> recycledParticles;	
	int particlesInUse;

	
	private:
	static ParticleFactory * _instance;
	
	

};