
#pragma once

#include "ofMain.h"
#include "ParticleREndererShape.h"

class ParticleRendererLowRes : public ParticleRendererShape {
	
public:
	
	ParticleRendererLowRes(float pixelsize = 10, unsigned int bitsperchannel = 1) : ParticleRendererShape(){
		pixelSize = pixelsize;
		
		shape.clear();
		
		shape.push_back(ofVec3f(  0.5, -0.5 ));
		
		
		shape.push_back(ofVec3f(  0.5,  0.5 ));
		shape.push_back(ofVec3f( -0.5, -0.5 ));
		
		shape.push_back(ofVec3f( -0.5, 0.5 ));
		
		mesh.setMode(OF_PRIMITIVE_TRIANGLES);
		
		bitsPerChannel = bitsperchannel;
	
		
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
			
			if((!p.enabled) || (p.size<pixelSize/4)) continue;
		
			
			int vertexIndex = mesh.getNumVertices();
			
			for(int i = 0; i<shape.size(); i++) {
				ofVec3f v = shape[i];
				
				v*=p.size;
				v+=p.pos;
				mesh.addVertex(lowResify(v, shape[i].x<0, shape[i].y<0));
				mesh.addColor(getReducedBitColour(p.getColour()));
				
			}
			
			mesh.addTriangle(vertexIndex, vertexIndex+1, vertexIndex+2);
			mesh.addTriangle(vertexIndex+3, vertexIndex+2, vertexIndex+1);
			
			
		}
		
		mesh.draw();
		ofPopMatrix(); 
        
    }

	ofVec3f lowResify(ofVec3f value, bool roundDownX = true, bool roundDownY = true) {
		
		return ofVec3f(lowResify(value.x, roundDownX),lowResify(value.y, roundDownY),lowResify(value.z));
		
	}
	float lowResify(float value, bool roundDown = true) {
		
		if(roundDown)
			return floor(value/pixelSize)*pixelSize;
		else
			return ceil(value/pixelSize)*pixelSize;
		
		
	}
	
	ofColor getReducedBitColour(ofColor& colour) {
		
			unsigned int r = (unsigned int) colour.r >> (8-bitsPerChannel);
			r = ofMap(r,0,pow(2, (float)bitsPerChannel)-1, 0,255);
			unsigned int g = (unsigned int)colour.g >> (8-bitsPerChannel);
			g = ofMap(g,0,pow(2, (float)bitsPerChannel)-1, 0,255);
			unsigned int b = (unsigned int)colour.b >> (8-bitsPerChannel);
			b = ofMap(b,0,pow(2, (float)bitsPerChannel)-1, 0,255);
			return(ofColor(r, g, b));
		
	}
	
	ofMesh mesh;
	float pixelSize;
	unsigned int bitsPerChannel;
	
	
};