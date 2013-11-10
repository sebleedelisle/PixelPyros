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

class ParticleRendererGlitchLine : public ParticleRendererBase {
	
public:
	
	ParticleRendererGlitchLine(float linewidth = 1, bool smoothline = false, bool drawdisabled = false) : ParticleRendererBase() {
		lineWidth = linewidth;
		smooth = smoothline;
		drawDisabled = drawdisabled;
		mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
		
	}
	
	virtual void renderParticles(Particle* firstParticle, float scale = 1, float scaleCentreX = 0, float scaleCentreY = 0){
      	ofPushMatrix();
		applyScaleMatrix(scale, scaleCentreX, scaleCentreY);
		
		ofPushStyle();
		
		ofSetLineWidth(lineWidth);
		
		mesh.clear();
		
		Particle* particle = firstParticle;
		
		while(particle!=NULL) {
			
			Particle& p = *particle;
			particle = particle->next;

			if((!p.enabled) && (!drawDisabled))  continue;
			//if(drawDisabled) continue;
			
			mesh.addVertex(p.pos);
			if(p.enabled)
				mesh.addColor(p.getColour());
			else {
				
				ofColor colour(p.getColour());
				colour.setBrightness(20); 
				mesh.addColor(colour);
			}
					
		}
		
		mesh.draw();
		
		ofPopStyle();
		ofPopMatrix(); 
        
    }
	
	ofMesh mesh;
	
	float lineWidth;
	bool smooth;
	bool drawDisabled;
};