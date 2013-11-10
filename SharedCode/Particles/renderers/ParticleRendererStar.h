//
//  ParticleRendererSquare.h
//  ParticlePlay5
//
//  Created by Seb Lee-Delisle on 18/08/2012.
//
//

#pragma once

#include "ofMain.h"

class ParticleRendererStar : public ParticleRendererBase {
	
public:
	
	ParticleRendererStar(float len=50, float ang=45) : ParticleRendererBase(){
		length = len;
		angle = ang;
		
		mesh.setMode(OF_PRIMITIVE_TRIANGLES);
		
	}
	
	virtual void renderParticles(Particle* firstParticle, float scale = 1, float scaleCentreX = 0, float scaleCentreY = 0){

		
		ofPushMatrix();
		applyScaleMatrix(scale, scaleCentreX, scaleCentreY);
		
		
		mesh.clear();
		Particle* particle = firstParticle;
		
		while(particle!=NULL) {
			
			Particle& p = *particle;
			particle = particle->next;
			
			if((!p.enabled) || (p.size<0.1)) continue;			
			
			ofVec3f p1(0,-1), p2(MIN(p.size*20,length),0), p3(0,1);
			ofVec3f scalar(length/20,p.size);
			p1 *= scalar;
			p2 *= scalar;
			p3 *= scalar;
			
			p1.rotate(0,0,angle);
			p2.rotate(0,0,angle);
			p3.rotate(0,0,angle);

			
			for(int i = 0; i<4; i++) {
			
				mesh.addVertex(p1+p.pos);
			
				mesh.addVertex(p2+p.pos);
			
				mesh.addVertex(p3+p.pos);
				mesh.addColor(p.getColour());
				mesh.addColor(p.getColour());
				mesh.addColor(p.getColour());
				
				p1.rotate(0,0,90);
				p2.rotate(0,0,90);
				p3.rotate(0,0,90);
				
			
				
			}
			
			

			
		}
		
		mesh.draw();
			
		ofPopMatrix(); 
        
    }
	
	ofMesh mesh;
	
	
	float length;
	float angle;
	
	
	
	
};