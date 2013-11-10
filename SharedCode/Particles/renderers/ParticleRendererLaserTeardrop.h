//
//  ParticleRendererLaser.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 12/09/2013.
//
//

#pragma once
#include "ParticleRendererBase.h"
#include "LaserManager.h"

class ParticleRendererLaserTeardrop : public ParticleRendererBase {

	public:
	ParticleRendererLaserTeardrop() : ParticleRendererBase() {
		historyCount = 20;
	}
	
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
			
			lm.addLaserCircle(pos, p.getColour(), p.size * scale);
			
			// Need to replace this with a polyline really....
			/*
			for(int j = 0; j< (int)p.historyPositions.size()-1; j++) {
				
				lm.addLaserLineEased(p.historyPositions[j], p.historyPositions[j+1], p.getColour());
				
			} */
			
			

		}
		
    
	}











}; 