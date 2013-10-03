//
//  RectangleUI.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 28/09/2013.
//
//

#include "RectangleUI.h"


void RectangleUI::initUI() {
	visible = true;
	
	ofAddListener(ofEvents().mouseMoved, this, &RectangleUI::mouseMoved);
	ofAddListener(ofEvents().mousePressed, this, &RectangleUI::mousePressed);
	ofAddListener(ofEvents().mouseDragged, this, &RectangleUI::mouseDragged);
	ofAddListener(ofEvents().mouseReleased, this, &RectangleUI::mouseReleased);
	
	mouseOverEdge = -1;
	dragEdge = -1;
	dragSize = 5;

	
}

void RectangleUI:: update(){
	
}
void RectangleUI:: draw(){
	ofPushStyle();
	ofSetLineWidth(1);
	ofSetColor(150); 
	ofRect(*this);
	
	if(mouseOverEdge>-1) {
		drawEdge(mouseOverEdge, ofColor::white);
	}
	if(dragEdge>-1) {
		drawEdge(mouseOverEdge, ofColor::red);
	}
	
	ofPopStyle();
}

void RectangleUI:: mouseMoved(ofMouseEventArgs &e){
	
	mouseOverEdge = getEdgeAtPoint(e.x, e.y);
	
}

void RectangleUI:: mousePressed(ofMouseEventArgs &e){
	dragEdge = getEdgeAtPoint(e.x, e.y); 
	
}
void RectangleUI:: mouseDragged(ofMouseEventArgs &e){
	if(dragEdge == 0) {
		setHeight(getBottom()-e.y);
		setY(e.y); 
	} else if(dragEdge == 1) {
		setWidth(e.x - getLeft());
		
	} else if(dragEdge == 2) {
		setHeight(e.y - getTop());
		
	} else if(dragEdge == 3) {
		setWidth(getRight() - e.x);
		setX(e.x);
		
	}
}
void RectangleUI:: mouseReleased(ofMouseEventArgs &e){
	dragEdge = -1; 
}


int RectangleUI :: getEdgeAtPoint(float px, float py) {

	if((px>getLeft()) && (px<getRight()) && (abs(py-getTop())<dragSize)) {
		return 0;
	} else if((px>getLeft()) && (px<getRight()) && (abs(py-getBottom())<dragSize)) {
		return 2;
	} else if((py>getTop()) && (py<getBottom()) && (abs(px-getLeft())<dragSize)) {
		return 3;
	} else if((py>getTop()) && (py<getBottom()) && (abs(px-getRight())<dragSize)) {
		return 1;
	}
	
	return -1;

}

void RectangleUI::drawEdge(int edge, ofColor colour){

	ofSetColor(colour);
	
	if(edge == 0) {
		ofLine(x, y, getRight(), y);
	} else if(edge==1) {
		ofLine(getRight(), y, getRight(), getBottom());
	} else if(edge == 2) {
		ofLine(x, getBottom(), getRight(), getBottom());
	} else if(edge==3) {
		ofLine(x, y, x, getBottom());
	}


}