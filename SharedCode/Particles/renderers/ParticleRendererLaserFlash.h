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

class ParticleRendererLaserFlash : public ParticleRendererShape {

	public :
	
	ParticleRendererLaserFlash(float spiralthickness = 50){
		spiralThickness = spiralthickness;
	}
	
	virtual void renderParticles(Particle* firstParticle){
     

		LaserManager& lm = *LaserManager::instance();
	
		Particle* particle = firstParticle;
		
		while(particle!=NULL) {
			
			Particle& p = *particle;
			particle = particle->next;
			
			if((!p.enabled) || (p.size<0.1)) continue;			
			
			lm.addLaserSpiral(p.pos, p.getColour(), (p.size<spiralThickness) ? 0 : (p.size-spiralThickness), p.size);
		}
	}
	
	float spiralThickness; 
}; 