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
#include "ColourSystemGradient.h"

class ParticleRendererGlitchPolylineLaser : public ParticleRendererBase {
	
public:

	ParticleRendererGlitchPolylineLaser() : ParticleRendererBase() {
		
		
	}
	
	virtual void renderParticles(Particle* firstParticle){
      
		LaserManager& lm = *LaserManager::instance();
		
		if((!firstParticle ) || (!firstParticle->next)) return;
		
		polyline.clear();
		polyline.setClosed(false);
		ColourSystemGradient * grad = new ColourSystemGradient();
		
		Particle* particle = firstParticle;
		//Particle* lastParticleRendered = NULL;
		
		while(particle!=NULL) {
			
			Particle& p = *particle;
			
			if(p.enabled) {
				polyline.addVertex(p.pos);
				grad.addColourStop(polyline.getPerimiter(), p.getColour();
				
			}
			
			particle = particle->next;
			
		}
		grad.setLength(polyline.getPerimiter());
		
		polyline.simplify();
		lm.addLaserPolyline(polyline, grad);
	        
    }
	
	ofPolyline polyline;
	
};