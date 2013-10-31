#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	
	svg.load("logo.svg");
	testpoly.setClosed(false);
	for(int i = 0; i<20; i++) {
		testpoly.addVertex(ofPoint(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())));
	}
	
	
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	
	
	
	ofBackground(0);
	/*
	int pathnum = ofClamp(floor(ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, svg.getNumPath(), true)), 0, svg.getNumPath()-1);
	
	ofPolyline letter = svg.getPathAt(pathnum).getOutline()[0];
	
	ofScale(2,2);
	
	letter.draw();
	letter.simplify();
	
	ofNoFill();
	for(int i = 0; i<letter.getVertices().size(); i++) {
	
		float rot = letter.getAngleAtIndex(i);
		cout << i << " " << rot << endl;
		ofColor c(255,ofMap(abs(rot),0,90,0,255, true),255);
		ofSetColor(c); 
		ofCircle(letter.getVertices()[i], 2);
		
		
		
	}
	
	*/
	
	testpoly.draw();
	ofNoFill();
	ofCircle(testpoly.getPointAtPercent(0), 20);
	ofCircle(testpoly.getPointAtPercent(1), 20);
	ofCircle(testpoly.getPointAtPercent(ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 1)),10);
	float length = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, testpoly.getPerimeter());
	float index = testpoly.getIndexAtLength(length);
	ofDrawBitmapString(ofToString(index), 20,20);
	
	
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}