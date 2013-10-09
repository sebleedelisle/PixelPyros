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
	
	virtual void renderParticles(vector <Particle * > particles){
        

		LaserManager& lm = *LaserManager::instance();
		
	
		for(int i=0; i<particles.size(); i++) {
			
			Particle& p = *particles[i]; // *(particles[i]);
			if((!p.enabled) || (p.size<0.1)) continue;
			
			
			lm.addLaserCircle(p.pos, p.getColour(), p.size);
			
			for(int j = 0; j<p.historyPositions.size()-1; j++) {
				
				lm.addLaserLineEased(p.historyPositions[j], p.historyPositions[j+1], p.getColour());
				
			}
			
		}
		
    
	}











}; 