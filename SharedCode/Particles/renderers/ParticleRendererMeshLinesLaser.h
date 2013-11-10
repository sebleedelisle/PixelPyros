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
	
	virtual void renderParticles(Particle* firstParticle, float scale = 1, float scaleCentreX = 0, float scaleCentreY = 0){
       
		
		ofPushMatrix();
		applyScaleMatrix(scale, scaleCentreX, scaleCentreY);
	
		ofVec3f scaleCentre(scaleCentreX, scaleCentreY) ;
		ofVec3f pos1, pos2;
		
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
				pos1 = p.pos;
				pos1 -= scaleCentre;
				pos1 *= scale;
				pos1 += scaleCentre;
				pos2 = particle->pos;
				pos2 -= scaleCentre;
				pos2 *= scale;
				pos2 += scaleCentre;
				lm.addLaserLineEased(pos1, pos2, c);
			}
			
			pnum++;
			
		}
		
		mesh.draw();
		ofPopStyle();
		
		ofPopMatrix();
        
    }
	
	ofMesh mesh;
	float lineWidth;
	float laserThreshold; 
	bool smooth; 
};