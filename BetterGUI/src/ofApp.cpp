#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
    
    gui.setDefaultHeight(32);
	gui.setDefaultWidth(400);
	gui.setDefaultTextPadding(10);
    gui.useFrameBuffer(true);
	
	gui.setDefaultSpacing(2);
	gui.setDefaultElementSpacing(5);
	gui.setDefaultElementIndentation(1);

	gui.loadFont("Verdana.ttf", 12, false);
    gui.setup("BetterGUI Test"); // most of the time you don't need a name

    gui.add(toggleDemo.setup("Toggle Button", true));
    gui.add(sliderDemo.setup("Slider Demo",0.5,0,1));
	gui.add(intSliderDemo.setup("Integer Slider Demo", 0, 128, 255));
    gui.add(colorSliderDemo.setup("Color Demo", ofColor::black, ofColor::black, ofColor::white));
    gui.add(buttonDemo.setup("Butto Demo"));
    gui.add(labelDemo.setup("Label Demo","label text"));
    
}


//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	if(!guiHide)
		gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key==' ') {
		guiHide = !guiHide;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
