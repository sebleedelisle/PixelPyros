//
//  CanonGrabber
//  MotionPong
//
//  Created by Seb Lee-Delisle on 16/04/2013.
//
//

#pragma once


#include "Camera.h"


class CanonGrabber : public ofxLibdc::Camera, public ofBaseVideoDraws {
public:
	CanonGrabber();
	ofTexture& getTextureReference();
	void setUseTexture(bool useTexture);
	unsigned char* getPixels();
	ofImage& getBuffer();
	void update();
	void grabFrame();
	void draw(float x, float y);
	void draw(float x, float y, float w, float h);
	float getWidth();
	float getHeight();
	bool isFrameNew();
	void close();
	ofPixels& getPixelsRef();
protected:
	ofImage buffer;
	bool newFrame;
};

