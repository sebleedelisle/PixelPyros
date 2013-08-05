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
		
	}
	
	void renderParticles(vector <Particle * > particles){
        
        // BASIC TRIANGLE RENDERER
		if(smooth)
			ofEnableSmoothing();
		else
			ofDisableSmoothing();
		
			
		ofEnableBlendMode(OF_BLENDMODE_ADD);
		//		ofEnableAlphaBlending();
		//
		
		ofSetLineWidth(lineWidth);
		ofMesh mesh;
		
		mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
		
		//ofMatrix4x4 mat;
		
		for(std::vector<Particle *>::iterator it = particles.begin(); it != particles.end(); ++it) {
			
			Particle& p = **it; // *(particles[i]);
			if((!p.enabled) && (!drawDisabled))  continue;
			if(drawDisabled && (ofRandom(1)<0.05)) continue;
			
			//int vertexIndex = mesh.getNumVertices();
			
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
		ofDisableBlendMode();
		
		
        
    }
	
	float lineWidth;
	bool smooth;
	bool drawDisabled;
};