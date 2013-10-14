#include "ofApp.h"

	
//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	//ofSetBackgroundColor(0);
	// we add this listener before setting up so the initial circle resolution is correct

	//ofEnableSmoothing()
		
	gui.setDefaultHeight(18);
	gui.setDefaultWidth(300);
	gui.setDefaultTextPadding(7);
	
	
	gui.setDefaultSpacing(2);
	gui.setDefaultElementSpacing(5);
	gui.setDefaultElementIndentation(1);

	
	//gui.setSpacing
	gui.loadFont("Verdana.ttf", 10, false);
	
	//ofDrawBitmapString("HELLO", 0,0);
	
	
	gui.setup("LaserTestGUI"); // most of the time you don't need a name
	
	//gui.setSize(500,30);
	//gui.setUseTTF(true);
	gui.add(showParticles.setup("Show Particles", true));
	gui.add(showRectangle.setup("Show Rectangle", false));
	gui.add(speed.set( "Speed", 1, 0, 5 ));
	gui.add(numParticles.set( "Num Particles", 40, 1, 300 ));
	
	
	gui.add(color.setup("Particle Colour",ofColor(100,100,140),ofColor(0,0),ofColor(255,255)));
	gui.add(particleFlicker.set("Flicker",0.5,0,1));
	gui.setPosition(0,0);
	gui.add(laserManager.parameters);
	gui.setVisible (true);

	guiVisible = true;
	
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
	
    //ofBackgroundGradient(ofColor::white, ofColor::gray);
	ofBackground(0);
	float deltaTime = ofGetLastFrameTime() * speed;
	
	if(showParticles) {
		elapsedTime+=deltaTime;
		
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
	} else {
		particles.clear();
		elapsedTime = 0;
		particlesCreated = 0;
	}
	
	if(showRectangle) {
		ofColor c = color;
		laserManager.addLaserRect(ofPoint(100,100),ofPoint(ofGetWidth()-200, ofGetHeight()-200), c);
		
	}
 	laserManager.update();

	

	//if( guiVisible ){
		gui.draw();
	//}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if( key == ' ' ){
		guiVisible = !guiVisible;
	}
	if(key == 's') {
		gui.saveToFile("settings.xml");
	}
	if(key == 'l') {
		gui.loadFromFile("settings.xml");
	}
	if(key == 'r'){
	
		laserManager.toggleRegistration();
	}
	if(key == 'p'){
		
		showParticles = !showParticles;
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
