//
//  ParticleRendererSquare.h
//  ParticlePlay5
//
//  Created by Seb Lee-Delisle on 18/08/2012.
//
//

#pragma once

class ParticleRendererDoubleCircle : public ParticleRendererShape {
	
public:
	
	ParticleRendererDoubleCircle(int numsegments=12, float innercirclesize = 0.3, ofVec3f rot = ofVec3f(0,0,0)) : ParticleRendererShape(){
		
		shape.clear();
		
		
		for(float i = 0; i<=numsegments; i++) {
			
			if(i>0) shape.push_back(ofVec3f( cos(i*(PI*2)/numsegments) , sin(i*(PI*2)/numsegments) ).rotate(rot.x, rot.y, rot.z));
			
			if(i<numsegments)shape.push_back(ofVec3f( cos(i*(PI*2)/numsegments) , sin(i*(PI*2)/numsegments) ).rotate(rot.x, rot.y, rot.z));
			
			
		}
		
		innerCircleSize = innercirclesize;
			
		mesh.setMode(OF_PRIMITIVE_TRIANGLES);
		
		
	}
	
	virtual void renderParticles(Particle* firstParticle, float scale = 1, float scaleCentreX = 0, float scaleCentreY = 0){
		
		ofPushMatrix();
		applyScaleMatrix(scale, scaleCentreX, scaleCentreY);
		
        // BASIC TRIANGLE RENDERER

	       
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
				
				if(i%2==1) {
					mesh.addVertex(p.pos);
					mesh.addColor(p.getColour());
				}
			}
			
			
			for(int i = 0; i<shape.size(); i++) {
				ofVec3f v = shape[i];
				
				v*=p.size*innerCircleSize;
				v+=p.pos;
				mesh.addVertex(v);
				mesh.addColor(p.getColour());
				
				if(i%2==1) {
					mesh.addVertex(p.pos);
					mesh.addColor(p.getColour());
				}
			}

			
			
		
		}
		
		mesh.draw();
		ofPopMatrix(); 
		
        
    }
	
	ofMesh mesh;
	
	float innerCircleSize; 
	
};