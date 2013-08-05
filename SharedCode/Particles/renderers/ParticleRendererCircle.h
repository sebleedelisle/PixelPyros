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
		
		meshMode = OF_PRIMITIVE_LINES;
		
	}
	
	virtual void renderParticles(vector <Particle * > particles){
        
        // BASIC TRIANGLE RENDERER
				ofDisableSmoothing();
		ofEnableBlendMode(OF_BLENDMODE_ADD);
		//		ofEnableAlphaBlending();
		//
		ofSetLineWidth(lineWidth);
		ofMesh mesh;
		
        
		mesh.setMode(fill? OF_PRIMITIVE_TRIANGLES : OF_PRIMITIVE_LINES);
		
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
				
				if((fill) && (i%2==1)) {
					mesh.addVertex(p.pos);
					mesh.addColor(p.getColour());
				}
			}
			
			//mesh.addTriangle(vertexIndex, vertexIndex+1, vertexIndex+2);
			//mesh.addTriangle(vertexIndex+1, vertexIndex+2, vertexIndex+3);
			
			
		}
		
		mesh.draw();
		ofDisableBlendMode();
		
		
        
    }
	
	
	float lineWidth; 
	
	bool fill; 
	
};