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

class ParticleRendererMeshLinesLaser : public ParticleRendererBase {

	public:
	
	ParticleRendererMeshLinesLaser(float linewidth = 1, float laserthreshold = 0.8) : ParticleRendererBase() {
		mesh.setMode(OF_PRIMITIVE_LINES);
		
		lineWidth = linewidth;
		laserThreshold = laserthreshold;
	}
	
	virtual void renderParticles(Particle* firstParticle){
       
        // BASIC TRIANGLE RENDERER
		LaserManager& lm = *LaserManager::instance();
		
		ofPushStyle();
		ofSetLineWidth(lineWidth);
		
		mesh.clear();

		Particle* particle = firstParticle;
		int pnum = 0; 
		
		while(particle!=NULL) {
			
			Particle& p = *particle;
			particle = particle->next;

			if(!p.enabled)  continue;
			
			//int vertexIndex = mesh.getNumVertices();
		
			
					
			mesh.addVertex(p.pos);
			ofColor c = p.getColour() * ofRandom(p.shimmerMin, 1);
			mesh.addColor(c);
			
			if((pnum%2 == 0) && (particle!=NULL) && (c.getBrightness()> laserThreshold*255.0)) {
				lm.addLaserLineEased(p.pos, particle->pos, c);
			}
			
			pnum++;
			
		}
		
		mesh.draw();
		ofPopStyle();
		
        
    }
	
	ofMesh mesh;
	float lineWidth;
	float laserThreshold; 
	bool smooth; 
};