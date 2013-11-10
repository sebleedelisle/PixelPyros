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
	
	virtual void renderParticles(Particle* firstParticle, float scale = 1, float scaleCentreX = 0, float scaleCentreY = 0){
     
		
		ofVec3f scaleCentre(scaleCentreX, scaleCentreY) ;
		ofVec3f pos;
		
		LaserManager& lm = *LaserManager::instance();
	
		Particle* particle = firstParticle;
		
		while(particle!=NULL) {
			
			Particle& p = *particle;
			particle = particle->next;
			
			
			float size = p.size*scale;
			
			if((!p.enabled) || (size<0.1)) continue;
			
			pos = p.pos;
			pos-=scaleCentre;
			pos*=scale;
			pos+=scaleCentre;
			
			lm.addLaserSpiral(pos, p.getColour(), (size<spiralThickness) ? 0 : (size-spiralThickness), size);
		}
	}
	
	float spiralThickness; 
}; 