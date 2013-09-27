//
//  ParticleRendererLaser.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 12/09/2013.
//
//

#pragma once
#include "ParticleRendererShape.h"
#include "LaserManager.h"

class ParticleRendererLaser : public ParticleRendererShape {

		

	virtual void renderParticles(vector <Particle * > particles){
        

		LaserManager& lm = *LaserManager::instance();
	
		for(std::vector<Particle *>::iterator it = particles.begin(); it != particles.end(); ++it) {
			
			Particle& p = **it; // *(particles[i]);
			if((!p.enabled) || (p.size<0.1)) continue;
			
			if(p.size>2) {
				lm.addLaserCircle(p.pos, p.getColour(), p.size);
			} else {
				lm.addLaserDot(p.pos, p.getColour(), 1);
			}
		}
		
    
	}











}; 