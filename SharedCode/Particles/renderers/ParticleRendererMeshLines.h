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

class ParticleRendererMeshLines : public ParticleRendererBase {

	public:
	
	ParticleRendererMeshLines(float linewidth = 1) : ParticleRendererBase() {
		mesh.setMode(OF_PRIMITIVE_LINES);
		
		lineWidth = linewidth; 
	}
	
	virtual void renderParticles(Particle* firstParticle, float scale = 1, float scaleCentreX = 0, float scaleCentreY = 0){
       
		ofPushMatrix();
		applyScaleMatrix(scale, scaleCentreX, scaleCentreY);
		
        // BASIC TRIANGLE RENDERER

		ofPushStyle();
		ofSetLineWidth(lineWidth);
		
		mesh.clear();

		Particle* particle = firstParticle;
		
		while(particle!=NULL) {
			
			Particle& p = *particle;
			particle = particle->next;

			if(!p.enabled)  continue;
			
			//int vertexIndex = mesh.getNumVertices();
		
			
					
			mesh.addVertex(p.pos);
			mesh.addColor(p.getColour() * ofRandom(p.shimmerMin, 1));
				
			
			
			
		}
		
		mesh.draw();
		ofPopStyle();
		ofPopMatrix(); 
        
    }
	
	ofMesh mesh;
	float lineWidth;
	bool smooth; 
};