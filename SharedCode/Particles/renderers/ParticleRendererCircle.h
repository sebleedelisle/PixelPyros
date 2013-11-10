//
//  ParticleRendererSquare.h
//  ParticlePlay5
//
//  Created by Seb Lee-Delisle on 18/08/2012.
//
//

#pragma once

class ParticleRendererCircle : public ParticleRendererShape {
	
public:
	
	ParticleRendererCircle(int numsegments=12, bool fillcircle=true, float linewidth = 1, ofVec3f rot = ofVec3f(0,0,0)) : ParticleRendererShape(){
		
		shape.clear();
		
		fill = fillcircle;
		
		for(float i = 0; i<=numsegments; i++) {
			
			if(i>0) shape.push_back(ofVec3f( cos(i*(PI*2)/numsegments) , sin(i*(PI*2)/numsegments) ).rotate(rot.x, rot.y, rot.z));
			
			if(i<numsegments)shape.push_back(ofVec3f( cos(i*(PI*2)/numsegments) , sin(i*(PI*2)/numsegments) ).rotate(rot.x, rot.y, rot.z));
			
			
		}
		
		lineWidth = linewidth; 
		
		
		mesh.setMode(fill? OF_PRIMITIVE_TRIANGLES : OF_PRIMITIVE_LINES);
		
		
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
				
				if((fill) && (i%2==1)) {
					mesh.addVertex(p.pos);
					mesh.addColor(p.getColour());
				}
			}
			
			

		}
		
		mesh.draw();
		
		ofPopMatrix(); 
		
        
    }
	
	ofMesh mesh;
	
		
	bool fill;
	float lineWidth; 
	
};