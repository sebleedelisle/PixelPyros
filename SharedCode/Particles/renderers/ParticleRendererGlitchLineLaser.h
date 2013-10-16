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
	
	virtual void renderParticles(Particle* firstParticle){
      
		ofPushStyle();
		
		LaserManager& lm = *LaserManager::instance();
		
		
		Particle* particle = firstParticle;
		Particle* lastParticleRendered = NULL; 
		
		while(particle!=NULL) {
			
			Particle& p = *particle;
			
			if(p.enabled) {
				if(lastParticleRendered!=NULL) {
				
					lm.addLaserLineEased(lastParticleRendered->pos, p.pos, p.getColour());
				
				};
			
				lastParticleRendered = particle;
				
			}
			
			particle = particle->next;
			
				
		}
		
		ofPopStyle();
        
    }
	
	};