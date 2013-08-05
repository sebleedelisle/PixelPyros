//
//  CanonBaseVideo.cpp
//  MotionPong
//
//  Created by Seb Lee-Delisle on 16/04/2013.
//
//

#include "CanonGrabber.h"


CanonGrabber::CanonGrabber() :
newFrame(false) {
}

ofTexture& CanonGrabber::getTextureReference() {
	return buffer.getTextureReference();
}

void CanonGrabber::setUseTexture(bool useTexture) {
	buffer.setUseTexture(useTexture);
}

unsigned char* CanonGrabber::getPixels() {
	return buffer.getPixels();
}

ofImage& CanonGrabber::getBuffer() {
	return buffer;
}

void CanonGrabber::update() {
	grabFrame();
}

void CanonGrabber::grabFrame() {
	newFrame = grabVideo(buffer);
}

void CanonGrabber::draw(float x, float y) {
	buffer.draw(x, y);
}

void CanonGrabber::draw(float x, float y, float w, float h) {
	buffer.draw(x, y, w, h);
}

float CanonGrabber::getWidth() {
	return Camera::getWidth();
}

float CanonGrabber::getHeight() {
	return Camera::getHeight();
}

bool CanonGrabber::isFrameNew() {
	if(newFrame) {
		newFrame = false;
		return true;
	}
	return false;
}

void CanonGrabber::close() {
	// handled automatically by ~Camera
}

ofPixels& CanonGrabber::getPixelsRef() {
	return buffer.getPixelsRef();
}

