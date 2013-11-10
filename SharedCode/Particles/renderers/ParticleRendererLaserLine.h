//
//  ParticleRendererLine.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 23/08/2012.
//
//
#pragma once
#include "ParticleRendererBase.h"
#include "LaserManager.h"
#include "ColourSystemGradient.h"
#include "ofMain.h"

class ParticleRendererLaserLine : public ParticleRendererBase {

	public:
	
	ParticleRendererLaserLine(int historycount = 10) : ParticleRendererBase() {
		historyCount = historycount;
	}
	
	virtual void renderParticles(Particle* firstParticle, float scale = 1, float scaleCentreX = 0, float scaleCentreY = 0){
       
		ofVec3f scaleCentre(scaleCentreX, scaleCentreY) ;
		ofVec3f pos;
		
		polyline.setClosed(false);
		LaserManager& lm = *LaserManager::instance();
		
		
		Particle* particle = firstParticle;
		
		while(particle!=NULL) {
			
			polyline.clear();
			ColourSystemGradient* grad = new ColourSystemGradient(); 
			
			Particle& p = *particle;
			particle = particle->next;

			if(!p.enabled)  continue;
			
			int size = p.historyPositions.size();
			
		
			ofColor colour = p.getColour();//	
			for(int i =0; i<size; i++) {
				pos = p.historyPositions[i];
				pos -= scaleCentre;
				pos *= scale;
				pos += scaleCentre;
				
				grad->addColourStop(p.historyColours[(size-1)-i], polyline.getPerimeter());
				polyline.addVertex(pos);
				
			}
			grad->setLength(polyline.getPerimeter());
			polyline.simplify();
			
			lm.addLaserPolyline(polyline, grad);
			
		}
		
		
		
		
        
    }
	
	ofPolyline polyline;

};