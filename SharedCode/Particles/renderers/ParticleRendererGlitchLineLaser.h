//
//  ParticleRendererLine.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 23/08/2012.
//
//
#pragma once
#include "ParticleRendererBase.h"
#include "ofMain.h"
#include "LaserManager.h"

class ParticleRendererGlitchLineLaser : public ParticleRendererBase {
	
public:

	ParticleRendererGlitchLineLaser() : ParticleRendererBase() {
		
		
	}
	
	virtual void renderParticles(Particle* firstParticle, float scale = 1, float scaleCentreX = 0, float scaleCentreY = 0){
      
		// TODO ADD SCALING
		
		LaserManager& lm = *LaserManager::instance();
		
		if((!firstParticle ) || (!firstParticle->next)) return;
		
		ofVec3f scaleCentre(scaleCentreX, scaleCentreY);
		
		ofVec3f pos1;
		ofVec3f pos2;
		
		Particle* particle = firstParticle;
		Particle* lastParticleRendered = NULL;
		
		while(particle!=NULL) {
			
			Particle& p = *particle;
			
			if(p.enabled) {
				
				if(lastParticleRendered!=NULL) {
				
					pos1 = lastParticleRendered->pos;
					pos2 = p.pos;
					
					pos1 -= scaleCentre;
					pos1 *= scale;
					pos1 += scaleCentre;
					pos2 -= scaleCentre;
					pos2 *= scale;
					pos2 += scaleCentre;
					
					lm.addLaserLineEased(pos1, pos2, p.getColour());
				
				};
			
				lastParticleRendered = particle;
				
			}
			
			particle = particle->next;
			
				
		}
		
       
    }
	
		
};