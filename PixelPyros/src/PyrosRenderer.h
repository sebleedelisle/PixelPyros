//
//  PyrosRenderer.h
//  PixelPyros
//
//  Created by Paul King on 30/08/2012.
//

#pragma once

#include "ofShader.h"
#include "ofFbo.h"
#include "QuadWarp.h"
class PyrosRenderer : public ofShader {
    
public:
    
    PyrosRenderer() : ofShader() {
        
        paramters.setName("Levels");
        paramters.add( bloomParam.set("bloom", 0.3, 0, 3 ) );
        paramters.add( gammaParam.set("gamma", 1.2, 0, 10 ) );
        paramters.add( blackPointParam.set("black point", 0, 0, 1 ) );
        paramters.add( whitePointParam.set("white point", 1, 0, 1 ) );
        
		resetDefaults();
		resetFlag = false;
    }
    
    PyrosRenderer(string filename) : ofShader() {
        load(filename);
    }
    
	
	void resetDefaults() {
        
		blackPointParam = 0;
		whitePointParam = 1;
		gammaParam = 1.2;
		bloomParam = 0.3;
		resetFlag = false;
		
	}
	
    virtual void setShaderParameters() {
        setUniform1f("bloom", bloomParam.get() );
        setUniform1f("gamma", gammaParam.get() );
        setUniform1f("blackPoint", blackPointParam.get() );
        setUniform1f("whitePoint", whitePointParam.get() );
    }
    
	// would be nice to make this a little more flexible, right now it is hard coded for
	// two projectors
	
    //void draw(ofFbo &fbo, vector<ofVec3f> & warpPoints1, vector<ofVec3f> & warpPoints2 ) {
	
	void draw(ofFbo &fbo, QuadWarp& warp1, QuadWarp& warp2 ) {

		if(resetFlag) resetDefaults();
		
		float w = fbo.getWidth(), h = fbo.getHeight();
		float hw =  w/2;
		float hh =  h/2;
		
		
		ofPushMatrix();
		
			
		begin();
        setUniformTexture("baseTexture", fbo.getTextureReference(), 0);
        setShaderParameters();
		
		// I think the warp rendering can be moved into
		// QuadWarp, right? The co-ordinates are the
		// QuadWarp's source co-ordinates as far as I can
		// tell. 
		
		warp1.apply(ofRectangle(0,0,hw, h));
		
		ofSetMinMagFilters(GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_NEAREST);
		//ofSetMinMagFilters(GL_, GL_NEAREST);
		
		glBegin(GL_QUADS);
		
		glTexCoord2f(0, 0);
		glVertex2f(0,0);
		
		glTexCoord2f(hw, 0);
		glVertex2f(hw,0);
		
		glTexCoord2f(hw, h);
		glVertex2f(hw,h);
		
		glTexCoord2f(0, h);
		glVertex2f(0,h);
		
		
		glEnd();
		
		
		end();
		
		ofPopMatrix();
		
		ofPushMatrix();
		
		
		begin();
        setUniformTexture("baseTexture", fbo.getTextureReference(), 0);
        setShaderParameters();
		
		
		
		glPushMatrix();
		warp2.apply(ofRectangle(0,0,hw, h));
		
		
		glBegin(GL_QUADS);
		
		glTexCoord2f(hw, 0);
		glVertex2f(hw,0);
		//glVertex2f(0,0);
		
		glTexCoord2f(w, 0);
		glVertex2f(w,0);
		//glVertex2f(hw,0);
		
		glTexCoord2f(w, h);
		glVertex2f(w,h);
		//glVertex2f(hw,h);
		
		glTexCoord2f(hw, h);
		glVertex2f(hw,h);
		//glVertex2f(0,h);
		
		
		glEnd();
		glPopMatrix();
		
		
		end();
		
        ofPopMatrix();
		

			
	}
	
	bool resetFlag; 
    
    ofParameter<float> bloomParam;
    ofParameter<float> gammaParam;
    ofParameter<float> blackPointParam;
    ofParameter<float> whitePointParam;
    
    ofParameterGroup paramters;
    
private:
    
};

