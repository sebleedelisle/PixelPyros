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
		
		mesh.setMode(OF_PRIMITIVE_LINES);


	}

	virtual void renderParticles(vector <Particle * > particles){
        
        // BASIC TRIANGLE RENDERER
		/*if(smooth)	ofEnableSmoothing();
		else ofDisableSmoothing();*/
	
		mesh.clear();
		
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
			
			
			
		}
		
		mesh.draw();

        
    }
	
	
	ofMesh mesh;
	
	
};