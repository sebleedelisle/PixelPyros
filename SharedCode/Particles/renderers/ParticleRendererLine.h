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

class ParticleRendererLine : public ParticleRendererBase {

	public:
	
	ParticleRendererLine(float linewidth = 1, bool smoothlines = false, int historycount = 10) : ParticleRendererBase() {
		lineWidth = linewidth;
		smooth = smoothlines; 
		mesh.setMode(OF_PRIMITIVE_LINES);
		historyCount = historycount;
	}
	
	virtual void renderParticles(Particle* firstParticle, float scale = 1, float scaleCentreX = 0, float scaleCentreY = 0){
       
		
		ofPushMatrix();
		applyScaleMatrix(scale, scaleCentreX, scaleCentreY);
		
		
        // BASIC TRIANGLE RENDERER
		/*
		if(smooth) ofEnableSmoothing();
		else ofDisableSmoothing();
		*/
		ofPushStyle();
		ofSetLineWidth(lineWidth);
		
		mesh.clear();
				
		//ofMatrix4x4 mat;
		
		
		Particle* particle = firstParticle;
		
		while(particle!=NULL) {
			
			Particle& p = *particle;
			particle = particle->next;

			if(!p.enabled)  continue;
			
			//int vertexIndex = mesh.getNumVertices();
		
			
			int size = p.historyPositions.size();
			
			// for soft tips to the line
			float brightness = 1;

			//ofColor colour = p.getColour();//
			//ofColor colour = p.historyColours[size-1];
			
			for(int i =0; i<size-1; i++) {
				
				//colour.setBrightness(brightness*255*ofRandom(p.shimmerMin, 1));
				mesh.addVertex(p.historyPositions[i]);
				mesh.addColor(p.historyColours[(size-1)-i]);
				
				mesh.addVertex(p.historyPositions[i+1]);
				mesh.addColor(p.historyColours[(size-1)-(i+1)]);
				//brightness+=0.5;
				//if(brightness>1) brightness = 1;

			}
			
//			mesh.addVertex(p.historyPositions[size-1]);
//			mesh.addColor(p.getColour());
//			
//			mesh.addVertex(p.pos);
//			mesh.addColor(p.getColour());
//		
			//mesh.addVertex(p.pos-(p.vel*0.1));
			//mesh.addColor(ofColor::black);
			
			
		}
		
		mesh.draw();
		ofPopStyle();
		ofPopMatrix(); 
        
    }
	
	ofMesh mesh;
	float lineWidth;
	bool smooth; 
};