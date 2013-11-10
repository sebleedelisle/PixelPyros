//
//  ParticleRendererShape.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 22/08/2012.
//
//

#pragma once
#include "ParticleRendererBase.h"
#include "ofMain.h"


class ParticleRendererShape : public ParticleRendererBase {
	
public:
	
	ParticleRendererShape() {
		
		shape.clear();
		
		shape.push_back(ofVec3f(    0, -0.5 ));
		shape.push_back(ofVec3f(  -0.5,  0 ));
		shape.push_back(ofVec3f(  0.5,  0 ));
		
		shape.push_back(ofVec3f( 0,  0.5 ));
		
		
		mesh.setMode(OF_PRIMITIVE_TRIANGLES);
		
		
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
			
			if((!p.enabled) || (p.size<0.1)) continue;
			
			int vertexIndex = mesh.getNumVertices();
			
			for(int i = 0; i<shape.size(); i++) {
				ofVec3f v = shape[i];
				
				v*=p.size;
				v+=p.pos;
				mesh.addVertex(v);
				mesh.addColor(p.getColour());
				
			}
			
			mesh.addTriangle(vertexIndex, vertexIndex+1, vertexIndex+2);
			mesh.addTriangle(vertexIndex+1, vertexIndex+2, vertexIndex+3);
			
			
		}
		
		mesh.draw();
		ofPopMatrix(); 
		
    }
	
	ofMesh mesh;
	
	vector <ofVec3f> shape;
	//ofPrimitiveMode meshMode;
	//float lineWidth;
    
	
	
};