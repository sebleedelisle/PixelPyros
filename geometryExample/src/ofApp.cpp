#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	sphere.setMode(OF_PRIMITIVE_TRIANGLES);
	angle = 0;
	sphere2 = ofMesh::icosphere(100,2); 
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	ofSetColor(255);
	
	ofPushMatrix();
	ofTranslate(ofGetWidth()/4,ofGetHeight()/2);
	ofScale(100,100,100);
	ofRotateX((float)ofGetMouseY()/10.0f);
	ofRotateY((float)ofGetMouseX()/10.0f);
	sphere.drawWireframe();
	ofPopMatrix();
	
	ofPushMatrix();
	ofTranslate(ofGetWidth()/4*3,ofGetHeight()/2);

	ofRotateX((float)ofGetMouseY()/10.0f);
	ofRotateY((float)ofGetMouseX()/10.0f);
	sphere2.drawWireframe();
	ofPopMatrix();
	
	angle+=1; 
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