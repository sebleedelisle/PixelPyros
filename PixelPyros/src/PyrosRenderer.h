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
	
		edgeBlendImage.allocate(8, 8, OF_IMAGE_COLOR);
		ofPixels& pixels = edgeBlendImage.getPixelsRef();
		for(int x = 0; x<edgeBlendImage.getWidth(); x++) {
			for(int y = 0; y<edgeBlendImage.getHeight(); y++) {
				pixels.setColor(x, y, ofColor(ofMap(x,0,7, 255, 0, true)));
				
			}	
		}
		edgeBlendImage.update();
		
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
	
	void draw(ofFbo &fbo, QuadWarp& warp1, QuadWarp& warp2, int edgeBlendSize ) {

		if(resetFlag) resetDefaults();
		
		float edgeBlendOffset = edgeBlendSize/2; 
		
		float w = fbo.getWidth(), h = fbo.getHeight();
		float hw =  w/2;
		//float hh =  h/2;
		
		ofPushStyle();
		ofEnableBlendMode(OF_BLENDMODE_ADD);
		
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
		
		glTexCoord2f(edgeBlendOffset, 0);
		glVertex2f(0,0);
		
		glTexCoord2f(hw+edgeBlendOffset, 0);
		glVertex2f(hw,0);
		
		glTexCoord2f(hw+edgeBlendOffset, h);
		glVertex2f(hw,h);
		
		glTexCoord2f(edgeBlendOffset, h);
		glVertex2f(0,h);

		glEnd();
		
		
		end();
		
		ofPopMatrix();

		ofPushMatrix();

		begin();
        setUniformTexture("baseTexture", fbo.getTextureReference(), 0);
        //setShaderParameters();
		
		//glPushMatrix();
		warp2.apply(ofRectangle(0,0,hw, h));
		
		
		glBegin(GL_QUADS);
		
		glTexCoord2f(hw-edgeBlendOffset, 0);
		glVertex2f(hw,0);
		
		glTexCoord2f(w-edgeBlendOffset, 0);
		glVertex2f(w,0);
		
		glTexCoord2f(w-edgeBlendOffset, h);
		glVertex2f(w,h);
		
		glTexCoord2f(hw-edgeBlendOffset, h);
		glVertex2f(hw,h);
		
		glEnd();
		
		end();
		
        ofPopMatrix();
		
		ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);

		// EDGE BLEND IMAGE LEFT ------------------------------
		
		int edgeBlendImageWidth = edgeBlendImage.getWidth();
		int edgeBlendImageHeight = edgeBlendImage.getHeight();
		ofPushMatrix();
		
		begin();
        setUniformTexture("baseTexture", edgeBlendImage.getTextureReference(), 0);
		disableShader();
		
		warp1.apply(ofRectangle(0,0,hw, h));
		
		ofSetMinMagFilters(GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_NEAREST);
		
		glBegin(GL_QUADS);
		
		glTexCoord2f(0, 0);
		glVertex2f(hw-edgeBlendSize,0);
		
		glTexCoord2f(edgeBlendImageWidth, 0);
		glVertex2f(hw,0);
		
		glTexCoord2f(edgeBlendImageWidth, edgeBlendImageHeight);
		glVertex2f(hw,h);
		
		glTexCoord2f(0,edgeBlendImageHeight);
		glVertex2f(hw-edgeBlendSize,h);
		
		glEnd();
		
		
		end();
		
		ofPopMatrix();

		
		// EDGE BLEND RIGHT ------------------

		ofPushMatrix();
		
		
		begin();
        setUniformTexture("baseTexture", edgeBlendImage.getTextureReference(), 0);
     
		//glPushMatrix();
		warp2.apply(ofRectangle(0,0,hw, h));
		
		
		glBegin(GL_QUADS);
		
		glTexCoord2f(edgeBlendImageWidth, 0);
		glVertex2f(hw,0);
		
		glTexCoord2f(0, 0);
		glVertex2f(hw+edgeBlendSize,0);
		
		glTexCoord2f(0, edgeBlendImageHeight);
		glVertex2f(hw+edgeBlendSize,h);
		
		glTexCoord2f(edgeBlendImageWidth, edgeBlendImageHeight);
		glVertex2f(hw,h);
		
		glEnd();
				
		end();
		
        ofPopMatrix();
				
		ofPopStyle();
		
	}
    
	virtual void disableShader() {
        setUniform1f("bloom", 0 );
        setUniform1f("gamma", 1 );
        setUniform1f("blackPoint", 0 );
        setUniform1f("whitePoint", 1 );
    }

	bool resetFlag;
    
    ofParameter<float> bloomParam;
    ofParameter<float> gammaParam;
    ofParameter<float> blackPointParam;
    ofParameter<float> whitePointParam;
	ofImage edgeBlendImage; 
    
    ofParameterGroup paramters;
    
private:
    
};

