#include "testApp.h"
#include "ofxIldaFrame.h"


//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0);
	//ofSetVerticalSync(false);
	
	ofSetLogLevel(OF_LOG_ERROR);

	
}

//--------------------------------------------------------------
void testApp::update(){

	
	



}



//--------------------------------------------------------------
void testApp::draw() {
	
	//laserManager.maxSpeed = ofMap(ofGetMouseX(),0, ofGetWidth(),1,50);
	//laserManager.acceleration = ofMap(ofGetMouseY(),0, ofGetHeight(),0,2);
	
	float particleFrequency = 0.1;
	//cout << particles.size();
	if((ofGetElapsedTimef() / particleFrequency > particles.size()) && (particles.size()<50)) {
		
		Particle p;
		p.reset();
		particles.push_back(p);
		
	}
	
	for(int i = 0; i<particles.size(); i++) {
		
		Particle& p = particles.at(i);
		p.update();
		p.draw();
		
		laserManager.addLaserDot(p, ofColor::white, ofRandom(p.brightness));
	}
	
 	laserManager.update();
}



//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key==' ') laserManager.showRegistration = !laserManager.showRegistration;
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
  
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
 	cout << laserManager.acceleration << " " << laserManager.maxSpeed << endl; 
}
