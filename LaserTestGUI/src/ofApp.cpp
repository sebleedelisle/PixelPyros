#include "ofApp.h"

	
//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);

	// we add this listener before setting up so the initial circle resolution is correct
	//circleResolution.addListener(this, &ofApp::circleResolutionChanged);
	//ringButton.addListener(this,&ofApp::ringButtonPressed);

	gui.setup("LaserTestGUI"); // most of the time you don't need a name
	
	gui.add(showParticles.setup("showParticles", true));
	gui.add(numParticles.setup( "numParticles", 40, 1, 300 ));
	gui.add(speed.set( "speed", 1, 0, 5 ));

	gui.add(laserManager.intensity.set("intensity", 1, 0, 1));
	gui.add(laserManager.colourChangeDelay.set("colour change offset", -6, -15, 15));
	
	
	gui.add(laserManager.showMovePoints.set("show move points", false));
	gui.add(laserManager.moveSpeed.set("move speed", 3,0.01,10));
	gui.add(laserManager.movePointsPadding.set("move points padding", 0,0,20));

	gui.add(laserManager.dotPreBlank.set("dot pre blank", 3, 0, 20));
	gui.add(laserManager.dotPostBlank.set("dot post blank", 3, 0, 20));
	gui.add(laserManager.dotMaxPoints.set("dot max points", 7, 0, 100));
	
	//gui.add(center.setup("center",ofVec2f(ofGetWidth()*.5,ofGetHeight()*.5),ofVec2f(0,0),ofVec2f(ofGetWidth(),ofGetHeight())));
	
	gui.add(color.setup("color",ofColor(100,100,140),ofColor(0,0),ofColor(255,255)));
	gui.add(particleFlicker.set("flicker",0.5,0,1));
	
	//gui.add(circleResolution.setup("circle res", 5, 3, 90));
	//gui.add(twoCircles.setup("two circles"));
	//gui.add(ringButton.setup("ring"));
	//gui.add(screenSize.setup("screen size", ""));

	bHide = true;
	elapsedTime = 0; 

	gui.loadFromFile("settings.xml");
	particlesCreated = 0; 

}




//--------------------------------------------------------------
void ofApp::exit(){
	//ringButton.removeListener(this,&ofApp::ringButtonPressed);
	gui.saveToFile("settings.xml");

}

//--------------------------------------------------------------
void ofApp::circleResolutionChanged(int & circleResolution){
	ofSetCircleResolution(circleResolution);
}

//--------------------------------------------------------------
void ofApp::ringButtonPressed(){
	//ring.play();
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	
    ofBackgroundGradient(ofColor::white, ofColor::gray);
	
	float deltaTime = ofGetLastFrameTime() * speed;
	elapsedTime+=deltaTime; 
	
	if(showParticles) {
		float particleFrequency = 5.0f/(float)numParticles;
		//cout << particles.size();
		if((elapsedTime / particleFrequency > particlesCreated)) {
			
			Particle p;
			p.reset();
			particles.push_back(p);
			particlesCreated++;
			
		}
		
		while(particles.size()>numParticles) {
			particles.pop_front();
		}
		
		for(int i = 0; i<particles.size(); i++) {
			
			Particle& p = particles.at(i);
			p.update(deltaTime);
			p.draw();
			ofColor c = color;
			laserManager.addLaserDot(p, c, ofRandom(1-particleFlicker, 1) *p.brightness);
		}
	}
 	laserManager.update();

	
	
	// auto draw?
	// should the gui control hiding?
	if( bHide ){
		gui.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if( key == 'h' ){
		bHide = !bHide;
	}
	if(key == 's') {
		gui.saveToFile("settings.xml");
	}
	if(key == 'l') {
		gui.loadFromFile("settings.xml");
	}
	if(key == ' '){
	
		laserManager.toggleRegistration();
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
    //screenSize = ofToString(w) + "x" + ofToString(h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	
}
