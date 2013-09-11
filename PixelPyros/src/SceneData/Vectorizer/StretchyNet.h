//
//  StretchyNet.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 22/08/2012.
//
//

#pragma once 

#include "StretchyNetPoint.h"
#include "ofMain.h"
#include "PhysicsObject.h"
#include "ParticleSystemManager.h"

class StretchyNet {

	public :
	StretchyNet(){
		
		updateCount = 0;
		elapsedTime = 0;
		brightness =0.5 ;
	}

	void init(ofRectangle boundsrect, float colwidth =30, int rowheight = 30) {
		
		bounds = boundsrect; 
		points.clear();
		
		int numcols = floor(bounds.width/colwidth);
		if(numcols%2==0) numcols++; 
		int numrows = floor(bounds.height/rowheight);
		float xspacing = bounds.width/numcols;
		float yspacing = bounds.height/numrows;
		float zspacing = -80;
		
		numcols++;
		numrows++; 
		
		int vertexNumber = 0; 
		
		for(int z = 0; z<1; z++ ) {
			for(int y = 0; y<numrows; y++) {
				for(int x = 0; x<numcols; x++) {
				
					
					points.push_back(StretchyNetPoint(x*xspacing, y*yspacing, (z*zspacing) + 150));
					
					StretchyNetPoint& p = points.back();
					p.rotate(10, ofVec3f(0,bounds.height*0.9,0), ofVec3f(1,0,0));
					p.target.set(p);
					
					if(y<numrows-1) {
						indices.push_back(vertexNumber);
						indices.push_back(vertexNumber+numcols); 
						
					}
					
					if(x<numcols-1) {
						indices.push_back(vertexNumber);
						indices.push_back(vertexNumber+1);

						
					}
					
					vertexNumber++;
				}
				
			}
		}
		
		
	}
	void update(float deltaTime, ParticleSystemManager& psm) {
		elapsedTime+=deltaTime;
		
		vector <PhysicsObject*> & physicsObjects = psm.physicsObjects;
		
		
		float area = 150;
		float bendiness = 20;
		
		int expectedNumUpdates = elapsedTime*50;
		
		while(updateCount < expectedNumUpdates) {
			
			for(std::vector<StretchyNetPoint>::iterator it = points.begin(); it != points.end(); ++it) {
				StretchyNetPoint& p = *it;
				
				p.update();
				
				for(std::vector<PhysicsObject*>::iterator it2 = physicsObjects.begin(); it2 != physicsObjects.end(); ++it2) {
					PhysicsObject* po = *it2;
					if((!po->enabled) || (!po->life.active)) continue;
					
					float distsquared = po->pos.distanceSquared(p);
					if(distsquared<(area*area)){
						float dist = sqrt(distsquared);
						float power = (area-dist)/area * bendiness;
						p +=  (power*((p-po->pos)/dist));
						
						
						
					}
				
				
				}
				
				
			}
			
			updateCount++;
			
		}
		
	}
	
	void draw() {
		
		ofPushMatrix();
		ofTranslate(bounds.width/2,bounds.height/2);
		ofRotateY(sin(elapsedTime/3)*3);
		ofRotateX(cos(elapsedTime/3)*3);
		
		ofTranslate(-bounds.width/2,-bounds.height/2);
		
		ofSetLineWidth(1);
		//ofEnableSmoothing();
		ofMesh mesh;
		mesh.setMode(OF_PRIMITIVE_LINES);
		
		
		for(std::vector<StretchyNetPoint>::iterator it = points.begin(); it != points.end(); ++it) {
			
			mesh.addVertex(*it);
			float strength = ofMap(it->vel.lengthSquared(),0,20*20,0.05,0.8,true) * brightness;
			mesh.addColor(ofColor(strength*180,strength*255,(strength*255) + 0));
		}
		
		mesh.addIndices(indices);
		//ofEnableBlendMode(OF_BLENDMODE_ADD);
		
		mesh.draw();
		//ofDisableBlendMode();
		
		ofPopMatrix();
	}

	int updateCount;
	float elapsedTime;
	vector <StretchyNetPoint> points;
	vector <unsigned int> indices;
	ofRectangle bounds;
	
	float brightness; 
					
};