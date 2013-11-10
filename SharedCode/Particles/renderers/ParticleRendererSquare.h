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

	virtual void renderParticles(Particle* firstParticle, float scale = 1, float scaleCentreX = 0, float scaleCentreY = 0){
		
        // BASIC TRIANGLE RENDERER
		
		ofPushMatrix();
		applyScaleMatrix(scale, scaleCentreX, scaleCentreY);
		
		mesh.clear();
		
		Particle* particle = firstParticle;
		
		while(particle!=NULL) {
			
			Particle& p = *particle;
			particle = particle->next;
			
			if((!p.enabled) || (p.size<1)) continue;
			
			for(int i = 0; i<shape.size(); i++) {
				ofVec3f v = shape[i];
				
				v*=p.size;
				v+=p.pos;
				mesh.addVertex(v);
				mesh.addColor(p.getColour());
				
			}
			
			
			
		}
		
		mesh.draw();

        ofPopMatrix(); 
    }
	
	
	ofMesh mesh;
	
	
};