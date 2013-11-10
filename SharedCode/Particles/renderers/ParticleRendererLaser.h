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

		

	virtual void renderParticles(Particle* firstParticle, float scale = 1, float scaleCentreX = 0, float scaleCentreY = 0){
     
		ofVec3f scaleCentre(scaleCentreX, scaleCentreY) ;
		ofVec3f pos;
		
		LaserManager& lm = *LaserManager::instance();
	
		Particle* particle = firstParticle;
		
		while(particle!=NULL) {
			
			Particle& p = *particle;
			particle = particle->next;
			
			if((!p.enabled) || (p.size<0.1)) continue;			
			
			pos = p.pos;
			pos -= scaleCentre;
			pos *= scale;
			pos += scaleCentre;
			
			
			if(p.size * scale>2) {
				lm.addLaserCircle(pos, p.getColour(), p.size * scale);
			} else {
				lm.addLaserDot(pos, p.getColour(), 1);
			}
			
			
		}
		
    
	}











}; 