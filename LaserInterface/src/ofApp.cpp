#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	etherdream.setup();
	timeSinceLastConnectionAttemptMils = 0; 
	connectToServer();

}

//--------------------------------------------------------------
void ofApp::update(){
	
	if(tcpClient.isConnected()){
		tcpClient.send(" ");
		string receivedString = ""; 
		//if data has been sent lets update our text
		string str;
		do {
			str = tcpClient.receive();
			if( str.length() > 0 ){
				receivedString += str;
				if(str=="---") {
					//cout << receivedString << endl;
	
					points = nextpoints;
					nextpoints.clear();
					
				} else {
					nextpoints.push_back(getPointFromString(str)); 
				}
			}
		} while ((str.length()>0) && (str!="---"));
		//cout << receivedString << endl;
		
	} else {
		//if we are not connected lets try and reconnect every 5 seconds
		timeSinceLastConnectionAttemptMils = ofGetElapsedTimeMillis() - lastConnectionAttemptTimeMils;
		
		if( timeSinceLastConnectionAttemptMils > 1000 ){
			connectToServer();
			lastConnectionAttemptTimeMils = ofGetElapsedTimeMillis();
		}
		
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	if(tcpClient.isConnected()) ofDrawBitmapString("status: type something to send data to port 11999", 15, 55);
	else ofDrawBitmapString("status: server not found. launch server app and check ports!\n\nreconnecting in "+ofToString( (1000 - timeSinceLastConnectionAttemptMils)  )+" mils", 15, 55);
	
	ofSetColor(255);
	ofMesh mesh;
	mesh.setMode(OF_PRIMITIVE_POINTS);
	
	for(int i = 0; i<points.size(); i++) {
		
		ofxIlda::Point& p = points[i];
		ofPoint ofpoint(ofPoint(ofMap(p.x, kIldaMinPoint, kIldaMaxPoint, 0, ofGetWidth(), true),
								ofMap(p.y, kIldaMinPoint, kIldaMaxPoint, 0, ofGetHeight(), true)));
		mesh.addVertex(ofpoint);
		mesh.addColor(ofColor::white);
		
		//cout << ofpoint<< " " ;
	}
	
	mesh.draw();
	
}


ofxIlda::Point ofApp::getPointFromString(string str) {
	
	vector<string> elements = ofSplitString(str, ",");
	if(elements.size()==5) {
		
		int x = atoi( elements[0].c_str());
		int y = atoi( elements[1].c_str());
		int r = atoi( elements[2].c_str());
		int g = atoi( elements[3].c_str());
		int b = atoi( elements[4].c_str());
		
		return ofxIlda::Point(x,y,r,g,b);
	}
	return ofxIlda::Point();
	
}



bool ofApp::connectToServer() {
	return tcpClient.setup("localhost", 11999, true);
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::exit(){
	
	tcpClient.close();
}
