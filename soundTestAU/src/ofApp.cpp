#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){


	
	source1.setFile("../../../../../Music/02 In Motion.aif");
	
	mixer.setInputBusCount(3);
	source1.connectTo(mixer, 0);

	
	
	mixer.connectTo(output);
	
	output.listOutputDevices();
	output.start();

	source1.play();
	playing = true;

}

//--------------------------------------------------------------
void ofApp::update(){
	if(playing) timeStamp = source1.getCurrentTimestamp();
	cout << timeStamp.mHostTime << " " << timeStamp.mWordClockTime << endl;
}

//--------------------------------------------------------------
void ofApp::draw(){

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
	
	if(playing) {
		timeStamp = source1.getCurrentTimestamp();
	source1.stop();
	} else {
		uint64_t time = (uint64_t) timeStamp.mSampleTime;
		source1.play();
		
		cout << time << " " << timeStamp.mHostTime << " " << timeStamp.mWordClockTime << endl;
	}
	playing = !playing;
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