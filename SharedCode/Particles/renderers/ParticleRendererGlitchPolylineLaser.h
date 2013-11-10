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
	
	virtual void renderParticles(Particle* firstParticle, float scale = 1, float scaleCentreX = 0, float scaleCentreY = 0){
      
		ofVec3f scaleCentre(scaleCentreX, scaleCentreY) ;
		ofVec3f pos;
		
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
				pos = p.pos;
				pos -= scaleCentre;
				pos *= scale;
				pos += scaleCentre;
				
				polyline.addVertex(pos);
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