//
//  RectangleUI.h
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 28/09/2013.
//
//

#pragma once 
#include "ofMain.h"

class RectangleUI : public ofRectangle {

	public:
	
	void initUI(ofRectangle maxrect);
	
	void update();
	void draw();
	
	void mouseMoved(ofMouseEventArgs &e);
	void mousePressed(ofMouseEventArgs &e);
	void mouseDragged(ofMouseEventArgs &e);
	void mouseReleased(ofMouseEventArgs &e);
	
	int getEdgeAtPoint(float px, float py);
	void drawEdge(int edge, ofColor colour);

	bool visible;
	
	int mouseOverEdge;
	int dragEdge;
	
	float dragSize; 
	
	ofRectangle maxRect;
}; 