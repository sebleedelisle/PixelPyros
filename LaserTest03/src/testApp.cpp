#include "testApp.h"
#include "ofxIldaFrame.h"


//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0);
    //ofEnableSmoothing();
  //	previewPointIndex = 0;
	
}

//--------------------------------------------------------------
void testApp::update(){

	
	



}



/// OK WHAT HAVE I LEARNED?
/*
 
 * it takes a few frames for the laser to switch off and seems to switch off early
 * it turns on actually before it's meant to. Weird.
 * MAYBE it thinks it's further along than it actually is? 
 
 */




//--------------------------------------------------------------
void testApp::draw() {
	
	//laserManager.maxSpeed = ofMap(ofGetMouseX(),0, ofGetWidth(),1,50);
	//laserManager.acceleration = ofMap(ofGetMouseY(),0, ofGetHeight(),0,2);
	
//	float x = 200;
//	float y = 200;
//	float w = 200;
//	float h = 200; 
//	
//	laserManager.addLaserLine(ofPoint(x,y), ofPoint(x+w,y), ofColor::red);
//	laserManager.addLaserLine(ofPoint(x+w,y), ofPoint(x+w,y+h), ofColor::yellow);
//	laserManager.addLaserLine(ofPoint(x+w,y+h), ofPoint(x,y+h), ofColor::green);
//	laserManager.addLaserLine(ofPoint(x,y+h), ofPoint(x,y), ofColor::blue);
	
	laserManager.addLaserRect(ofPoint(200,200),ofPoint(200,200), ofColor::red);
	laserManager.addLaserRect(ofPoint(300,300), ofPoint(50,50), ofColor::cyan);
	
	//laserManager.addLaserRect(ofPoint(ofGetMouseX(),ofGetMouseY()), ofPoint(100,100), ofColor::green);
	
	//drawLine(ofPoint(100,100), ofPoint(300,300));
	//drawLine(ofPoint(300,100), ofPoint(100,300));
	
	
	ofDrawBitmapString("POINTS : "+ofToString(laserManager.ildaPoints.size()), ofPoint(10,10));
	
 	laserManager.update();
}



void testApp::drawLine(ofPoint p1, ofPoint p2) {
	
	/* EQUATIONS
	 
	 distance to reach a particular speed :
	 distance = (speed²) / 2*acceleration
	 
	 distance for time given acceleration :
	 distance = ½acceleration * t²
	 
	 speed at distance for acceleration
	 speed = √(distance * 2*acceleration); 
	 
	 */
	
	
	float maxspeed = ofMap(ofGetMouseX(),0, ofGetWidth(),1,50);
	float acceleration = ofMap(ofGetMouseY(),0, ofGetHeight(),1,30);
	
	float acceleratedistance = (maxspeed*maxspeed) / (2*acceleration);
	float timetogettospeed = maxspeed / acceleration;	
	
	ofPoint u = p2-p1;
	
	
	float totaldistance = u.length();
	
	float constantspeeddistance = totaldistance - (acceleratedistance*2);
	float constantspeedtime = constantspeeddistance/maxspeed;
	
	if(totaldistance<(acceleratedistance*2)) {
		
		constantspeeddistance = 0 ;
		constantspeedtime = 0;
		acceleratedistance = totaldistance/2;
		maxspeed = sqrt( acceleratedistance * 2 * acceleration); 
		timetogettospeed = maxspeed / acceleration;
		
	}
	
	float totaltime = (timetogettospeed*2) + constantspeedtime;
	
	float timeincrement = totaltime / (floor(totaltime));
	
	u.normalize();
	
	float currentdistance;
	currentdistance = 0;
	float t = 0;
	
	while (t <= totaltime + 0.001) {
		
		if(t>totaltime) t = totaltime;
		
		if(t <=timetogettospeed) {
			currentdistance = 0.5 * acceleration * (t*t);
			ofSetColor(0,255,0);
		} else if((t>timetogettospeed) && (t<=timetogettospeed+constantspeedtime)){
			currentdistance = acceleratedistance + ((t-timetogettospeed) * maxspeed);
			ofSetColor(255);
		} else  {
			float t3 = t - (timetogettospeed + constantspeedtime);
			
			currentdistance = (acceleratedistance + constantspeeddistance) + (maxspeed*t3)+(0.5 *(-acceleration) * (t3*t3));
			ofSetColor(255,0,0);
			
		}
		
		
		ofPoint currentpos = (u * currentdistance) + p1;
		
		ofCircle(currentpos, 1);
		
		t+=timeincrement;
	} 
	
	cout << t << " " << timeincrement << " " << totaltime << endl;
	
	//cout << totaldistance << " " << acceleratedistance << " " << constantspeeddistance << endl;
	
}




//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
  
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
 	cout << laserManager.acceleration << " " << laserManager.maxSpeed << endl; 
}
