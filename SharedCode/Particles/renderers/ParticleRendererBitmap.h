//
//  ParticleBitmapRenderer.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 21/08/2012.
//
//

#pragma once 

#include "ofMain.h"
#include "ParticleRendererBase.h"

class ParticleRendererBitmap : public ParticleRendererBase {
	
	
	public :
	
	// SHOULD AVOID POINTER?
	
	ParticleRendererBitmap(ofImage* img) : ParticleRendererBase(){
		
		image = img;
		
		shape.clear();
		
		shape.push_back(ofVec3f(    -0.5, -0.5 ));
		shape.push_back(ofVec3f(  -0.5,  0.5 ));
		shape.push_back(ofVec3f(  0.5,  -0.5 ));
		shape.push_back(ofVec3f( 0.5,  0.5 ));
		
		texCoords.clear();
		texCoords.push_back(ofVec2f(0,0));
		texCoords.push_back(ofVec2f(0, image->height));
		texCoords.push_back(ofVec2f(image->width, 0));
		texCoords.push_back(ofVec2f(image->width, image->height));

		meshMode  = OF_PRIMITIVE_TRIANGLES;
		
		mesh.setMode(meshMode);
		
	}
	
	virtual void renderParticles(Particle* firstParticle, float scale = 1, float scaleCentreX = 0, float scaleCentreY = 0){
		
		ofPushMatrix();
		applyScaleMatrix(scale, scaleCentreX, scaleCentreY);
		
		// BASIC TRIANGLE RENDERER
		
		ofPushStyle();
		//if(image->type==OF_IMAGE_COLOR_ALPHA) ofEnableAlphaBlending();
		
		
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
				mesh.addTexCoord(texCoords[i]);
				
			}
			
			mesh.addTriangle(vertexIndex, vertexIndex+1, vertexIndex+2);
			mesh.addTriangle(vertexIndex+1, vertexIndex+2, vertexIndex+3);
			
			
			
		}
		image->bind();
		mesh.draw();
		image->unbind(); 
		
		ofPopStyle();
		
		ofPopMatrix(); 
		
        
    }


	vector <ofVec3f> shape;
	vector <ofVec2f> texCoords;
	ofPrimitiveMode meshMode;
	ofImage * image;
	ofMesh mesh;
	





};