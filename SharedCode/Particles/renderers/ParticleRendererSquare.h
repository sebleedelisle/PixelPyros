//
//  ParticleRendererSquare.h
//  ParticlePlay5
//
//  Created by Seb Lee-Delisle on 18/08/2012.
//
//

#pragma once
#include "ParticleRendererShape.h"

class ParticleRendererSquare : public ParticleRendererShape {

public:

	ParticleRendererSquare(float linewidth = 1, bool smoothlines = false) : ParticleRendererShape(){
		shape.clear();
		
		shape.push_back(ofVec3f( -0.5, 0, -0.5 ));
		shape.push_back(ofVec3f(  0.5, 0, -0.5 ));
		
		shape.push_back(ofVec3f(  0.5, 0, -0.5 ));
		shape.push_back(ofVec3f(  0.5, 0, 0.5 ));
		
		shape.push_back(ofVec3f(  0.5, 0, 0.5 ));
		shape.push_back(ofVec3f( -0.5, 0, 0.5 ));
		
		shape.push_back(ofVec3f( -0.5, 0, 0.5 ));
		shape.push_back(ofVec3f( -0.5, 0, -0.5 ));
		
		meshMode = OF_PRIMITIVE_LINES;
		
		lineWidth = linewidth;
		smooth = smoothlines;

	}

	virtual void renderParticles(vector <Particle * > particles){
        
        // BASIC TRIANGLE RENDERER
		if(smooth)	ofEnableSmoothing();
		else ofDisableSmoothing();
		ofEnableBlendMode(OF_BLENDMODE_ADD);
		
		ofSetLineWidth(lineWidth);
		ofMesh mesh;
		
        
		mesh.setMode(meshMode);
		
		//ofMatrix4x4 mat;
		
		for(std::vector<Particle *>::iterator it = particles.begin(); it != particles.end(); ++it) {
			
			Particle& p = **it; // *(particles[i]);
			if((!p.enabled) || (p.size<1)) continue;
			
			int vertexIndex = mesh.getNumVertices();
			
			for(int i = 0; i<shape.size(); i++) {
				ofVec3f v = shape[i];
				
				v*=p.size;
				v+=p.pos;
				mesh.addVertex(v);
				mesh.addColor(p.getColour());
				
			}
			
			//mesh.addTriangle(vertexIndex, vertexIndex+1, vertexIndex+2);
			//mesh.addTriangle(vertexIndex+1, vertexIndex+2, vertexIndex+3);
			
			
		}
		
		mesh.draw();
		ofDisableBlendMode();
		
		
        
    }
	

	bool smooth;
	float lineWidth; 
	
	
};